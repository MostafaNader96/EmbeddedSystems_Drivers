#include "std_types.h"
#include "DIO_interface.h"
#include "KeyPad_config.h"
#include "KeyPad_interface.h"

u8 KEYPAD_GetPressedKey(void)
{
	
	u8 Keypad_RowsPort[KEYPAD_ROWS_NUMBER]=KEYPAD_ROWS_PORT;
	u8 Keypad_ColumnsPort[KEYPAD_COLUMNS_NUMBER]=KEYPAD_COLUMNS_PORT;
	u8 Keypad_RowsPin[KEYPAD_ROWS_NUMBER]=KEYPAD_ROWS_PIN;
	u8 Keypad_ColumnsPin[KEYPAD_COLUMNS_NUMBER]=KEYPAD_COLUMNS_PIN;
	u8 Keypad_Keys[KEYPAD_ROWS_NUMBER][KEYPAD_COLUMNS_NUMBER]=KEYPAD_KEYS;
	
	u8 RowIdx,ColIdx,PinState,PressedKey=KEYPAD_DEFAULT;
	
	for(RowIdx=0;RowIdx<KEYPAD_ROWS_NUMBER;RowIdx++)
	{
		/*Activate the current row*/
		DIO_SetPinValue(Keypad_RowsPort[RowIdx],Keypad_RowsPin[RowIdx],0);
		
		/*Check columns if pressed*/
		for(ColIdx=0;ColIdx<KEYPAD_COLUMNS_NUMBER;ColIdx++)
		{
			DIO_GetPinValue(Keypad_ColumnsPort[ColIdx],Keypad_ColumnsPin[ColIdx],&PinState);
			
			/*Check if the key is pressed*/
			if(!PinState)
			{
				PressedKey=Keypad_Keys[RowIdx][ColIdx];
				
				/*Busy waiting until the key is released*/
				while(!PinState)
				{
					DIO_GetPinValue(Keypad_ColumnsPort[ColIdx],Keypad_ColumnsPin[ColIdx],&PinState);
				}
				return PressedKey;
			}
				
			
		}
		/*Deactivate the current row*/
			DIO_SetPinValue(Keypad_RowsPort[RowIdx],Keypad_RowsPin[RowIdx],1);

	}
	return PressedKey;
}
