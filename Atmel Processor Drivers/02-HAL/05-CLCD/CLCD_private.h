#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

#define FUNCTION_SET 			0b00111000
#define DISPLAY_ON_OFF 			0b00001100
#define DISPLAY_CLEAR 			0b00000001

#define FUNCTION_SET_4BIT_ONE 			0b0010
#define FUNCTION_SET_4BIT_TWO 			0b0010
#define FUNCTION_SET_4BIT_THREE 		0b1000


#define CLCD_u8_LINE_TWO_ADD_OFFSET 0x40
#define CLCD_u8_SET_DDRAM_ADD_COMM	0x80
#define FOUR_BITS_MODE				0
#define EIGHT_BITS_MODE				1

static void CLCD_voidSetEnablePulse(void);
static void CLCD_voidSetHalfDataPort(u8 Copy_u8Data);
static void CLCD_voidSetDataPort(u8 Copy_u8Data);

#endif
