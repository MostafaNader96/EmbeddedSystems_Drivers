#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define EXTI_U8_INT0			0
#define EXTI_U8_INT1			1
#define EXTI_U8_INT2			2

#define EXTI_U8_LOW_LEVEL		0
#define EXTI_U8_ON_CHANGE		1
#define EXTI_U8_FALLING_EDGE	2
#define EXTI_U8_RISING_ENGE		3

void EXTI_voidInit(void);
ErrorStatus EXTI_errEnable(u8 Copy_u8IntIdx);
ErrorStatus EXTI_errDisable(u8 Copy_u8IntIdx);
ErrorStatus EXTI_errSetSense(u8 Copy_u8IntIdx,u8 Copy_u8SenseLevel);
ErrorStatus EXTI_errSetCallBack(u8 Copy_u8IntIdx, void (*Copy_pvCallBack)(void));

#endif

