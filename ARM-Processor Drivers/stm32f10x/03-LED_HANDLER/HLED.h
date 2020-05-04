#ifndef HLED_H_
#define HLED_H_

#define LED_1	0
#define LED_2	1

#define LED_NUM	2

#define	SETT	1
#define	RESET	0

void HLED_Init(void);
void HLED_SetLedState(uint_8t Led_Number,uint_8t Led_State);

#endif