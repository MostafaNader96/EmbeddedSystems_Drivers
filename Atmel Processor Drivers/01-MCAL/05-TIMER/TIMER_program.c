#include "std_types.h"
#include "bits.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"

static void (*TIMER0_pvCallBack)(void)=NULL;

void Timer0_voidInit(void)
{
	/*Normal Mode*/
	CLR_BIT(TCCR0,TIMER0_WGM00);
	CLR_BIT(TCCR0,TIMER0_WGM01);
	/*Prescaler 64*/
	CLR_BIT(TCCR0,TIMER0_CS02) ;
	SET_BIT(TCCR0,TIMER0_CS01) ;
	SET_BIT(TCCR0,TIMER0_CS00) ;
	/*OverFlow Interrupt*/
	SET_BIT(TIMSK,TIMER0_TOIE0);
	/*Counter 8-bit Register Initialization*/
	TCNT0=6;
}

void Timer0_voidSetTimerPreload(u8 Copy_u8TimerPreload)
{
	TCNT0=Copy_u8TimerPreload;
}


ErrorStatus Timer0_voidSetCallBack(void(*Copy_pvCallBackPtr)(void))
{
	if(Copy_pvCallBackPtr!=NULL)
		TIMER0_pvCallBack=Copy_pvCallBackPtr;
	else
		return ERROR_NOK;

	return ERROR_OK;
}


void __vector_11(void)
{
	if(TIMER0_pvCallBack!=NULL)
	{
		TIMER0_pvCallBack();
	}
}


