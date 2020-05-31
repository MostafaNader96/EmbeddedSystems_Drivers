#include "std_types.h"
#include "bits.h"
#include "Delay_ms.h"
#include "CLCD_private.h"
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"

/*Description: This API Initializes the LCD*/
void CLCD_voidInitialize(void)
{
	Delay_ms(40);
#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE
	DIO_SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	DIO_SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);

	CLCD_voidSetHalfDataPort(FUNCTION_SET_4BIT_ONE);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(FUNCTION_SET_4BIT_TWO);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(FUNCTION_SET_4BIT_THREE);
	CLCD_voidSetEnablePulse();

#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	CLCD_voidWriteCmd(FUNCTION_SET);
#else
#error "WRONG DATA LENGTH CHOICE"

#endif
	CLCD_voidWriteCmd(DISPLAY_ON_OFF);
	CLCD_voidWriteCmd(DISPLAY_CLEAR);
	Delay_ms(2);
}

/*Description: This API Shall display the data sent on the LCD*/
void CLCD_voidWriteData(u8 Copy_u8Data)
{
	DIO_SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,1);
	DIO_SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE
	/*Set higher order 4bits of the command*/
	CLCD_voidSetHalfDataPort(Copy_u8Data>>4);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(Copy_u8Data);
	CLCD_voidSetEnablePulse();
#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	CLCD_voidSetDataPort(Copy_u8Data);
	CLCD_voidSetEnablePulse();
#else
#error "WRONG DATA LENGTH CHOICE"
#endif
}

/*Description: This API Sends a specific command to the LCD*/
void CLCD_voidWriteCmd(u8 Copy_u8Cmd)
{
	DIO_SetPinValue(CLCD_u8_RS_PORT,CLCD_u8_RS_PIN,0);
	DIO_SetPinValue(CLCD_u8_RW_PORT,CLCD_u8_RW_PIN,0);
#if CLCD_u8_DATA_LENGTH==FOUR_BITS_MODE

	/*Set higher order 4bits of the command*/
	CLCD_voidSetHalfDataPort(Copy_u8Cmd>>4);
	CLCD_voidSetEnablePulse();
	CLCD_voidSetHalfDataPort(Copy_u8Cmd);
	CLCD_voidSetEnablePulse();
#elif CLCD_u8_DATA_LENGTH==EIGHT_BITS_MODE
	CLCD_voidSetDataPort(Copy_u8Cmd);
	CLCD_voidSetEnablePulse();
#else
#error "WRONG DATA LENGTH CHOICE"
#endif
}

/*Description: This API Shall display the data string sent on the LCD*/
void CLCD_voidWriteString(const char* Copy_pchString)
{
	for(u8 i=0;Copy_pchString[i]>0;i++)
	{
		CLCD_voidWriteData(Copy_pchString[i]);
	}
}

/*Description: This API Shall Go to a certain location on the LCD*/
void CLCD_voidGoToXYPos(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8DDRamAdd;
	if(Copy_u8YPos==CLCD_u8_LINE_ONE)
	{
		Local_u8DDRamAdd=Copy_u8XPos;
	}
	else if(Copy_u8YPos==CLCD_u8_LINE_TWO)
	{
		Local_u8DDRamAdd=Copy_u8XPos+CLCD_u8_LINE_TWO_ADD_OFFSET;
	}
	else
	{
		asm("NOP");
	}
	CLCD_voidWriteCmd(Local_u8DDRamAdd | CLCD_u8_SET_DDRAM_ADD_COMM);
}

void CLCD_WriteNumber(u32 Copy_u8Num)
{
	u8 arr[10];
	u8 i=0,j;

	while(Copy_u8Num>=0)
	{
		arr[i]=(Copy_u8Num%10);
		Copy_u8Num=Copy_u8Num/10;
		i++;
		if(Copy_u8Num==0)
			break;
	}

	for(j=i-1; j>=0; j--)
	{
		CLCD_voidWriteData(arr[j]+48);
		if(j==0)
			break;
	}
}


static void CLCD_voidSetEnablePulse(void)
{
	DIO_SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,1);
	Delay_ms(1);
	DIO_SetPinValue(CLCD_u8_E_PORT,CLCD_u8_E_PIN,0);
}

static void CLCD_voidSetHalfDataPort(u8 Copy_u8Data)
{
	u8 Local_u8BitVal;

	Local_u8BitVal=GET_BIT(Copy_u8Data,0);
	DIO_SetPinValue(CLCD_u8_D0_PORT,CLCD_u8_D4_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,1);
	DIO_SetPinValue(CLCD_u8_D1_PORT,CLCD_u8_D5_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,2);
	DIO_SetPinValue(CLCD_u8_D2_PORT,CLCD_u8_D6_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,3);
	DIO_SetPinValue(CLCD_u8_D3_PORT,CLCD_u8_D7_PIN,Local_u8BitVal);
}

static void CLCD_voidSetDataPort(u8 Copy_u8Data)
{
	u8 Local_u8BitVal;

	Local_u8BitVal=GET_BIT(Copy_u8Data,0);
	DIO_SetPinValue(CLCD_u8_D0_PORT,CLCD_u8_D0_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,1);
	DIO_SetPinValue(CLCD_u8_D1_PORT,CLCD_u8_D1_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,2);
	DIO_SetPinValue(CLCD_u8_D2_PORT,CLCD_u8_D2_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,3);
	DIO_SetPinValue(CLCD_u8_D3_PORT,CLCD_u8_D3_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,4);
	DIO_SetPinValue(CLCD_u8_D4_PORT,CLCD_u8_D4_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,5);
	DIO_SetPinValue(CLCD_u8_D5_PORT,CLCD_u8_D5_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,6);
	DIO_SetPinValue(CLCD_u8_D6_PORT,CLCD_u8_D6_PIN,Local_u8BitVal);
	Local_u8BitVal=GET_BIT(Copy_u8Data,7);
	DIO_SetPinValue(CLCD_u8_D7_PORT,CLCD_u8_D7_PIN,Local_u8BitVal);
}



