#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

	

void ADC_voidInit(void)
{
	/* 8 bits Mode, AVCC ref voltage, Polling(not interrupt) */
	
	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);	//AVCC REFERENCE VOLTAGE
	
	SET_BIT(ADMUX,5);	//LEFT ADJUST MODE FOR 8 BITS
	
	SET_BIT(ADCSRA,7);	//ENABLE ADC
	
	SET_BIT(ADCSRA,2);	
	SET_BIT(ADCSRA,1);	//PRESCALER 128	
	SET_BIT(ADCSRA,0);	
}


u8 ADC_u8GetChannelReading(u8 Channel)
{
	ADMUX&=0b11100000;
	ADMUX|=Channel;
	
	/*Start Conversion*/
	SET_BIT(ADCSRA,6);	
	while(!(GET_BIT(ADCSRA,4)));
	
	SET_BIT(ADCSRA,4);
	
	return ADCH;
	
}