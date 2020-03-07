#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "SevenSegment_config.h"
#include "SevenSegment_interface.h"
#include "SevenSegment_private.h"

u8 SEVENSEG_EnablePorts[2]={SEVENSEG_PINCOM1_PORT,SEVENSEG_PINCOM2_PORT};
u8 SEVENSEG_EnablePINS[2]= {SEVENSEG_PINCOM1_NUMBER,SEVENSEG_PINCOM2_NUMBER};



void SEVENSEG_SetNumber(u8 number)
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

	}

	switch(Mode)
	{
	case 1:
		SetPinValue(SEVENSEG_PINA_PORT,SEVENSEG_PINA_NUMBER,GET_BIT(result,0));
		SetPinValue(SEVENSEG_PINB_PORT,SEVENSEG_PINB_NUMBER,GET_BIT(result,1));
		SetPinValue(SEVENSEG_PINC_PORT,SEVENSEG_PINC_NUMBER,GET_BIT(result,2));
		SetPinValue(SEVENSEG_PIND_PORT,SEVENSEG_PIND_NUMBER,GET_BIT(result,3));
		SetPinValue(SEVENSEG_PINE_PORT,SEVENSEG_PINE_NUMBER,GET_BIT(result,4));
		SetPinValue(SEVENSEG_PINF_PORT,SEVENSEG_PINF_NUMBER,GET_BIT(result,5));
		SetPinValue(SEVENSEG_PING_PORT,SEVENSEG_PING_NUMBER,GET_BIT(result,6));
		SetPinValue(SEVENSEG_PINH_PORT,SEVENSEG_PINH_NUMBER,GET_BIT(result,7));
		break;
	case 0:
		result=~result;
		SetPinValue(SEVENSEG_PINA_PORT,SEVENSEG_PINA_NUMBER,GET_BIT(result,0));
		SetPinValue(SEVENSEG_PINB_PORT,SEVENSEG_PINB_NUMBER,GET_BIT(result,1));
		SetPinValue(SEVENSEG_PINC_PORT,SEVENSEG_PINC_NUMBER,GET_BIT(result,2));
		SetPinValue(SEVENSEG_PIND_PORT,SEVENSEG_PIND_NUMBER,GET_BIT(result,3));
		SetPinValue(SEVENSEG_PINE_PORT,SEVENSEG_PINE_NUMBER,GET_BIT(result,4));
		SetPinValue(SEVENSEG_PINF_PORT,SEVENSEG_PINF_NUMBER,GET_BIT(result,5));
		SetPinValue(SEVENSEG_PING_PORT,SEVENSEG_PING_NUMBER,GET_BIT(result,6));
		SetPinValue(SEVENSEG_PINH_PORT,SEVENSEG_PINH_NUMBER,GET_BIT(result,7));
		break;
	}





}
void SEVENSEG_Enable(u8 SEVENSEGNumber)
{
	
	SetPinValue(SEVENSEG_EnablePorts[SEVENSEGNumber],SEVENSEG_EnablePINS[SEVENSEGNumber],Mode);

}
void SEVENSEG_Disable(u8 SEVENSEGNumber)
{
	SetPinValue(SEVENSEG_EnablePorts[SEVENSEGNumber],SEVENSEG_EnablePINS[SEVENSEGNumber],Mode^0x01);
}
