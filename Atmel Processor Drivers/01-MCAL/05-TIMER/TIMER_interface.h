#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void Timer0_voidInit(void);
ErrorStatus Timer0_voidSetCallBack(void(*Copy_pvCallBackPtr)(void));

#endif
