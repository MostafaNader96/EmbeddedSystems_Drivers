#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "SevenSegment_config.h"
#include "SevenSegment_interface.h"
#include "SevenSegment_private.h"

u8 SEVENSEG_EnablePorts[2]={SEVENSEG_PINCOM1_PORT,SEVENSEG_PINCOM2_PORT};
u8 SEVENSEG_EnablePINS[2]= {SEVENSEG_PINCOM1_NUMBER,SEVENSEG_PINCOM2_NUMBER};

u8 SEVENSEG_SetNumber(u8 number)
{
	u8 result;
	switch(number)
	{
	case 0:
		result=ZERO;
		break;
	case 1:
		result=ONE;
		break;
	case 2:
		result=TWO;
		break;
	case 3:
		result=THREE;
		break;
	case 4:
		result=FOUR;
		break;
	case 5:
		result=FIVE;
		break;
	case 6:
		result=SIX;
		break;
	case 7:
		result=SEVEN;
		break;
	case 8:
		result=EIGHT;
		break;
	case 9:
		result=NINE;
		break;
	default: return ERROR_NOK;

	}

	switch(MODE)
	{
	case COMMON_ANODE:
		DIO_SetPinValue(SEVENSEG_PINA_PORT,SEVENSEG_PINA_NUMBER,GET_BIT(result,0));
		DIO_SetPinValue(SEVENSEG_PINB_PORT,SEVENSEG_PINB_NUMBER,GET_BIT(result,1));
		DIO_SetPinValue(SEVENSEG_PINC_PORT,SEVENSEG_PINC_NUMBER,GET_BIT(result,2));
		DIO_SetPinValue(SEVENSEG_PIND_PORT,SEVENSEG_PIND_NUMBER,GET_BIT(result,3));
		DIO_SetPinValue(SEVENSEG_PINE_PORT,SEVENSEG_PINE_NUMBER,GET_BIT(result,4));
		DIO_SetPinValue(SEVENSEG_PINF_PORT,SEVENSEG_PINF_NUMBER,GET_BIT(result,5));
		DIO_SetPinValue(SEVENSEG_PING_PORT,SEVENSEG_PING_NUMBER,GET_BIT(result,6));
		DIO_SetPinValue(SEVENSEG_PINH_PORT,SEVENSEG_PINH_NUMBER,GET_BIT(result,7));
		break;
	case COMMON_CATHODE:
		result=~result;
		DIO_SetPinValue(SEVENSEG_PINA_PORT,SEVENSEG_PINA_NUMBER,GET_BIT(result,0));
		DIO_SetPinValue(SEVENSEG_PINB_PORT,SEVENSEG_PINB_NUMBER,GET_BIT(result,1));
		DIO_SetPinValue(SEVENSEG_PINC_PORT,SEVENSEG_PINC_NUMBER,GET_BIT(result,2));
		DIO_SetPinValue(SEVENSEG_PIND_PORT,SEVENSEG_PIND_NUMBER,GET_BIT(result,3));
		DIO_SetPinValue(SEVENSEG_PINE_PORT,SEVENSEG_PINE_NUMBER,GET_BIT(result,4));
		DIO_SetPinValue(SEVENSEG_PINF_PORT,SEVENSEG_PINF_NUMBER,GET_BIT(result,5));
		DIO_SetPinValue(SEVENSEG_PING_PORT,SEVENSEG_PING_NUMBER,GET_BIT(result,6));
		DIO_SetPinValue(SEVENSEG_PINH_PORT,SEVENSEG_PINH_NUMBER,GET_BIT(result,7));
		break;
	default: return ERROR_NOK;
	}
	return ERROR_OK;
}

void SEVENSEG_Enable(u8 SEVENSEGMENT_Number)
{
	DIO_SetPinValue(SEVENSEG_EnablePorts[SEVENSEGMENT_Number],SEVENSEG_EnablePINS[SEVENSEGMENT_Number],MODE);
}

void SEVENSEG_Disable(u8 SEVENSEGMENT_Number)
{
	DIO_SetPinValue(SEVENSEG_EnablePorts[SEVENSEGMENT_Number],SEVENSEG_EnablePINS[SEVENSEGMENT_Number],MODE^0x01);
}
