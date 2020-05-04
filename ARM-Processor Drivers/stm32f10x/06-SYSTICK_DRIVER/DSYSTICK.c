#include "DSYSTICK.h"
#include "DSYSTICK_config.h"

#define STK_CTRL		 *((volatile uint_32t*)0xE000E010)
#define STK_LOAD		 *((volatile uint_32t*)0xE000E014)
#define STK_VAL			 *((volatile uint_32t*)0xE000E018)

#define SYSTICK_ENABLE   0x00000001
#define SYSTICK_DISABLE  0xFFFFFFFE

systickcbf_t APPcbf ;

uint_8t SYSTICK_Init (void)
{
	STK_CTRL |= SYSTICK_CLK_SRC | SYSTICK_TICK_INT;
	return OK;
}

uint_8t SYSTICK_Start (void)
{
	STK_CTRL |= SYSTICK_ENABLE;
	return OK;
}

uint_8t SYSTICK_Stop (void)
{
	STK_CTRL &= SYSTICK_DISABLE;
	return OK;
}

uint_8t SYSTICK_SetCallback (systickcbf_t cbf)
{
	if(cbf)
	{
		APPcbf = cbf;
		return OK;
	}
	else
	{
		return NOT_OK;
	}
}

uint_8t SYSTICK_SetTime (uint_32t Timeus,uint_32t Clk)
{
	if (STK_CTRL & SYSTICK_CLK_AHB)
	{
		STK_LOAD=(Timeus * Clk)/1000000;
	}
	else if (!(STK_CTRL & SYSTICK_CLK_AHB))
	{
		STK_LOAD=((uint_64t)Timeus * (uint_64t)Clk)/8000000ULL;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

void SysTick_Handler(void)
{
	if (APPcbf)
	{
		APPcbf();
	}
	else
	{
		asm ("NOP");
	}
}
