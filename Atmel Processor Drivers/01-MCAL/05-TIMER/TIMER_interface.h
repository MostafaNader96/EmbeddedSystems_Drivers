#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void Timer0_voidInit(void);
void Timer0_voidSetTimerPreload(u8 Copy_u8TimerPreload);
ErrorStatus Timer0_voidSetCallBack(void(*Copy_pvCallBackPtr)(void));

#endif
