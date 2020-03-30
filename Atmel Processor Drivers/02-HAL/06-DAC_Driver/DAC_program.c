#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "DAC_config.h"
#include "DAC_interface.h"

void DAC_voidSetAnalogVolt(u16 Copy_u16AnalogmV)
{
	u8 Local_u8DigitalValue;
	u8 Local_u8BitValue;

	Local_u8DigitalValue=((u32)(Copy_u16AnalogmV*255UL)/(DAC_U16_REFERENCE_VOLTAGE));

	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,0);
	DIO_SetPinValue(DAC_U8_BIT0_PORT,DAC_U8_BIT0_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,1);
	DIO_SetPinValue(DAC_U8_BIT1_PORT,DAC_U8_BIT1_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,2);
	DIO_SetPinValue(DAC_U8_BIT2_PORT,DAC_U8_BIT2_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,3);
	DIO_SetPinValue(DAC_U8_BIT3_PORT,DAC_U8_BIT3_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,4);
	DIO_SetPinValue(DAC_U8_BIT4_PORT,DAC_U8_BIT4_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,5);
	DIO_SetPinValue(DAC_U8_BIT5_PORT,DAC_U8_BIT5_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,6);
	DIO_SetPinValue(DAC_U8_BIT6_PORT,DAC_U8_BIT6_PIN,Local_u8BitValue);
	Local_u8BitValue=GET_BIT(Local_u8DigitalValue,7);
	DIO_SetPinValue(DAC_U8_BIT7_PORT,DAC_U8_BIT7_PIN,Local_u8BitValue);
}

