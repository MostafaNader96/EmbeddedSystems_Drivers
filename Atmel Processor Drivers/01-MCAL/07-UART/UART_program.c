#include"bits.h"

#include "UART_interface.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"



void(*EndOfTransmitcb)(void);
void(*EndOfreceivecb)(u8);
void (*UART_TX_pvCallBack)(void);
void (*UART_RX_pvCallBack)(void);


const u8 BaudRateValue[3][3]=
{
		/*4800  9600 115200*/
		{0x67,  0x33, 0x03},		/*8M  */
		{154,    77,    6 },		/*12M */
		{0xcf,  0x67, 0x08}			/*16M */
};


void UART_voidTransmitDataAsynch(u8 Copy_u8Data,void(*copy_ptr)(void))
{
	/*enable TX interrupt*/
	SET_BIT(UCSRB,6);

	UDR_T=Copy_u8Data;

	EndOfTransmitcb=copy_ptr;

}

void UART_voidInitialize(void)
{
	/*U2X =0*/
	CLR_BIT(UCSRA,1);

	/*assign baud rate*/
	UBRRL=BaudRateValue[UART_u8_SYS_FREQ][UART_u8_BAUD_RATE];

	UCSRB=0b00011000;	/*interrupts disabled , TX,RX Enabled , Character size 8bit */

/*   	   ACCESS	    PARITY BITS			 # OF STOP BITS		  CHARACTER */
/*	      THIS REG													SIZE=8  */
	UCSRC= (1<<7) | (UART_u8_PARITY<<4) | (UART_u8_STOP_BITS<<3) | (3<<1) ;

	
}
u8 UART_voidTransmitDataSynch (u8 Copy_u8Data)
{
	u32 Timout=0;
	u8 Error_Status=ERROR_OK;
	UDR_T = Copy_u8Data;

	while(GET_BIT(UCSRA,6)==0 && Timout<TIMEOUT_THRESHOLD)
	{
		Timout++;
	}

	if(Timout>=TIMEOUT_THRESHOLD)
	{
		Error_Status=ERROR_TIMEOUT;
	}
	else
	{
		SET_BIT(UCSRA,6);
	}
	return Error_Status;

}


u8 UART_u8ReceiveSynch(u8 * Copy_pu8Data)
{
	u32 Timout=0;
	u8 Error_Status=ERROR_OK;


	while(GET_BIT(UCSRA,7)==0 && Timout<TIMEOUT_THRESHOLD)
	{
		Timout++;
	}

	if(Timout>=TIMEOUT_THRESHOLD)
	{
		Error_Status=ERROR_TIMEOUT;
	}
	else
	{
		*Copy_pu8Data=UDR_R;
	}
	return Error_Status;

}

void UART_u8ReceiveAsynch(void(*Copy_ptr)(u8))
{
	/*check if there is data to receive*/
	if(GET_BIT(UCSRA,7)==1)
	{
		Copy_ptr(UDR_T);

	}

	/*nothing to receive */
	else
	{
		/*enable RX interrupt*/
		SET_BIT(UCSRB,7);
	}

	/*save callback in global variable*/
	EndOfreceivecb=Copy_ptr;
}

u8 UART_TX_SetCallBack(void (*Copy_pvCallBack)(void))
{
	u8 LocalError=ERROR_OK;
	if((Copy_pvCallBack != NULL))
	{

		UART_TX_pvCallBack=Copy_pvCallBack;

	}
	else
	{
		LocalError=ERROR_NOK;
	}

	return LocalError;
}


u8 UART_RX_SetCallBack(void (*Copy_pvCallBack)(void))
{
	u8 LocalError=ERROR_OK;
	if((Copy_pvCallBack != NULL))
	{

		UART_RX_pvCallBack=Copy_pvCallBack;

	}
	else
	{
		LocalError=ERROR_NOK;
	}

	return LocalError;
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)			/*RX*/
{
	if(UART_RX_pvCallBack!=NULL)
	{
		UART_RX_pvCallBack();
	}
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)			/*TX*/
{
	if(UART_TX_pvCallBack!=NULL)
	{
		CLR_BIT(UCSRB,6);
		UART_TX_pvCallBack();
		EndOfTransmitcb();
	}
}



