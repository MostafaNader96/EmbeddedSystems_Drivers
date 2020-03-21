#include "std_types.h"
#include "bits.h"
#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

static u16 * ADC_pu16Result=NULL;
static void (*ADC_pvCallBackNotification)(void)=NULL;
static u8 ADC_u8State=ADC_IDLE;

static u8 ADC_ChannelIndex=0;
static u8 ADC_ChainLength;
static u8 * ADC_ChannelArr;
static u8 ADC_ISRSTATE;

void ADC_voidInit(void)
{
	/* 8 bits Mode, AVCC ref voltage, Polling(not interrupt) */

	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);	//AVCC REFERENCE VOLTAGE

	CLR_BIT(ADMUX,ADMUX_ADLAR);	//RIGHT ADJUST MODE FOR 10 BITS

	SET_BIT(ADCSRA,ADCSRA_ADEN);	//ENABLE ADC

	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);	//PRESCALER 128
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
}


ErrorStatus ADC_u8GetChannelReadingSynchronous(u8 Channel,u16 * Copy_pu16ADCResult)
{
	u32 Local_32TimeOutCounter=0;
	u8 Local_u8ErrorSatus=ERROR_OK;

	if(Channel>31 || Copy_pu16ADCResult==NULL)
	{
		Local_u8ErrorSatus=ERROR_NOK;
	}
	else
	{
		ADMUX&=0b11100000;
		ADMUX|=Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*pull on conversion complete flag till the flag is risen or timeout passes*/
		while((!(GET_BIT(ADCSRA,4))) && (Local_32TimeOutCounter < ADC_u32_TIMEOUTCOUNTS))
		{
			Local_32TimeOutCounter++;
		}

		/*Check for the reason the loop is broken*/
		if(Local_32TimeOutCounter==ADC_u32_TIMEOUTCOUNTS)
		{
			/*Loop is broken beacuse timeout passed*/
			Local_u8ErrorSatus=ERROR_TIMEOUT;
		}
		else
		{
			/*Loop is broken because conversion complete flag is raised*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);
			*Copy_pu16ADCResult =ADC;
		}

	}
	return Local_u8ErrorSatus;
}


ErrorStatus ADC_u8GetChannelReadingAsynchronous(u8 Channel,u16 * Copy_pu16ADCResult,void (*Copy_pvCallBackNotification)(void))
{
	u8 Local_u8ErrorStatus=ERROR_OK;
	if(Copy_pu16ADCResult == NULL || Copy_pvCallBackNotification == NULL || Channel>31)
	{
		Local_u8ErrorStatus=ERROR_NOK;
	}
	else
	{
		if(ADC_u8State==ADC_BUSY)
		{
			/*ADC busy with previous conversion*/
			Local_u8ErrorStatus=ERROR_BUSY;
		}
		else
		{
			ADC_u8State=ADC_BUSY;
			ADC_ISRSTATE=ADC_SINGLE_CHANNEL_STATE;

			/*Initialize the required objects*/
			ADC_pu16Result=Copy_pu16ADCResult;
			ADC_pvCallBackNotification=Copy_pvCallBackNotification;

			ADMUX&=0b11100000;
			ADMUX|=Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC complete interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	return Local_u8ErrorStatus;
}


ErrorStatus ADC_u8ChainInit(ADCChain_t* Copy_Chain,u8* Copy_pu8ChannelArr,u8 Copy_ChainLength )
{
	u8 Local_u8ErrorState=ERROR_OK;

	if(Copy_pu8ChannelArr==NULL)
	{
		Local_u8ErrorState=ERROR_NOK;
	}
	else
	{
		Copy_Chain->ChannelArr=Copy_pu8ChannelArr;
		Copy_Chain->ChainLength=Copy_ChainLength;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartChainConversion(ADCChain_t Copy_Chain,u16 *Copy_pu16Result,void (*Copy_pvCallBackNotification)(void))
{
	u8 Local_u8ErrorStatus=ERROR_OK;

	if(Copy_Chain.ChannelArr==NULL || Copy_pu16Result==NULL || Copy_pvCallBackNotification==NULL)
	{
		Local_u8ErrorStatus=ERROR_NOK;
	}
	else
	{
		if(ADC_u8State==ADC_BUSY)
		{
			Local_u8ErrorStatus=ERROR_BUSY;
		}
		else
		{
			/*make adc busy*/
			ADC_u8State=ADC_BUSY;
			ADC_ISRSTATE=ADC_STATE_CHAIN;
			/*initialize required object*/
			ADC_pu16Result=Copy_pu16Result;
			ADC_pvCallBackNotification=Copy_pvCallBackNotification;

			ADC_ChainLength=Copy_Chain.ChainLength;
			ADC_ChannelArr=Copy_Chain.ChannelArr;
			ADC_ChannelIndex=0;

			/*set first channel*/
			ADMUX &=0b11100000;
			ADMUX|=Copy_Chain.ChannelArr[0];

			/*start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ENABLE conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);

		}
	}

	return Local_u8ErrorStatus;
}


/*ADC Conversion Complete ISR*/
void __vector_16(void)
{
	if(ADC_ISRSTATE==ADC_SINGLE_CHANNEL_STATE)
	{
		*ADC_pu16Result=ADC;

		/*make adc state idle*/
		ADC_u8State=ADC_IDLE;

		/*DISABLE interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);

		/*invoke the call back notification function*/
		ADC_pvCallBackNotification();
	}
	else if(ADC_ISRSTATE==ADC_STATE_CHAIN)
	{
		ADC_pu16Result[ADC_ChannelIndex]=ADC;
		ADC_ChannelIndex++;
		if(ADC_ChannelIndex==ADC_ChainLength)
		{
			/*make adc idle*/
			ADC_u8State=ADC_IDLE;

			/*DISABLE interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/*invoke notification*/
			ADC_pvCallBackNotification();

		}
		else
		{
			/*set rquired channel*/
			ADMUX&=0b11100000;
			ADMUX|=ADC_ChannelArr[ADC_ChannelIndex];

			/*START conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
	else
	{
		asm("NOP");
	}
}
