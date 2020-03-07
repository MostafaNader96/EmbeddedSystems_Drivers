#include "DRCC.h"

#define RCC_BASE_ADDRESS 0X40021000

#define RCC_CR          *((uint_32t *)(RCC_BASE_ADDRESS + 0X00))
#define RCC_CFGR        *((uint_32t *)(RCC_BASE_ADDRESS + 0X04))
#define RCC_CIR         *((uint_32t *)(RCC_BASE_ADDRESS + 0X08))
#define RCC_APB2RSTR    *((uint_32t *)(RCC_BASE_ADDRESS + 0X0C))
#define RCC_APB1RSTR    *((uint_32t *)(RCC_BASE_ADDRESS + 0X10))
#define RCC_AHBENR      *((uint_32t *)(RCC_BASE_ADDRESS + 0X14))
#define RCC_APB2ENR     *((uint_32t *)(RCC_BASE_ADDRESS + 0X18))
#define RCC_APB1ENR     *((uint_32t *)(RCC_BASE_ADDRESS + 0X1C))
#define RCC_BDCR        *((uint_32t *)(RCC_BASE_ADDRESS + 0X20))
#define RCC_CSR         *((uint_32t *)(RCC_BASE_ADDRESS + 0X24))



#define PLLRDY_MASK 	0x02000000
#define HSERDY_MASK 	0x00020000
#define HSIRDY_MASK 	0x00000002

#define HSI_SRC_MASK 	0x00000000
#define HSE_SRC_MASK 	0x00000004
#define PLL_SRC_MASK 	0x00000008

#define AHB_PRESCALE_CLR  0xFFFFFF0F
#define APB1_PRESCALE_CLR 0xFFFFF8FF
#define APB2_PRESCALE_CLR 0xFFFFC7FF

#define PLL_CONFIG_CLR 0xFFC0FFFF
#define SYS_CLK_CLR 0xfffffffc

uint_8t RCC_SetClkStatus (uint_32t clk,uint_8t status)
{
	if ((clk>>28)==1)
	{
		switch (status)
		{
		case ON:
			RCC_CR|=clk;
			break;
		case OFF:
			RCC_CR&=~clk;
			break;
		}
		return OK;
	}
	else
	{
		return NOT_OK;
	}
}

uint_8t RCC_SetSystemClk (uint_32t clk)
{
	if ((clk>>29)==1)
	{
		uint_32t local_temp =RCC_CFGR;
		if (clk==HSI_SYS)
		{
			if (!(RCC_CR&HSIRDY_MASK))
			{
				return NOT_OK;
			}
		}
		else if (clk==HSE_SYS)
		{
			if (!(RCC_CR&HSERDY_MASK))
			{
				return NOT_OK;
			}

		}
		else if (clk==PLL_SYS)
		{
			if (!(RCC_CR&PLLRDY_MASK))
			{
				return NOT_OK;
			}

		}
		else
		{
			return NOT_OK;
		}
		local_temp&= SYS_CLK_CLR;
		local_temp|=clk;
		RCC_CFGR=local_temp;

		return OK;
	}
	else
	{
		return NOT_OK;
	}
}

uint_8t RCC_SetPLLConfig (uint_32t src, uint_8t MULL)
{

	if((src>>30)==1)
	{
		uint_32t local_temp=RCC_CFGR;
		local_temp&=PLL_CONFIG_CLR;
		local_temp|=src;
		local_temp|=MULL<<18;
		RCC_CFGR=local_temp;
		return OK;
	}
	else
		return NOT_OK;
}

uint_8t RCC_SetPriephralStatus (uint_32t priephral,uint_8t Status)
{
	if ((priephral>>31)==1) /*AHB shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_AHBENR|=priephral;
			break;
		case OFF :
			RCC_AHBENR&=~priephral;
			break;
		}
		return OK;
	}
	else if ((priephral>>30)==1) /*APB1 shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_APB1ENR|=priephral;
			break;
		case OFF :
			RCC_APB1ENR&=~priephral;
			break;
		}
		return OK;
	}
	else if ((priephral>>29)==1) /*APB2 shafra*/
	{
		switch (Status)
		{
		case ON :
			RCC_APB2ENR|=priephral;
			break;
		case OFF :
			RCC_APB2ENR&=~priephral;
			break;
		}
		return OK;
	}
	else
	{
		return NOT_OK;
	}

}
uint_8t RCC_SetBusPrescale (uint_32t Bus,uint_8t Prescale)
{
	uint_32t local_temp=RCC_CFGR;
	if ((Bus>>27)==1)
	{
		switch (Bus)
		{
		case AHB_PRESCALER:
			local_temp&=AHB_PRESCALE_CLR;
			local_temp|=Prescale<<4;
			RCC_CFGR=local_temp;
			break;
		case APB1_PRESCALER:
			local_temp&=APB1_PRESCALE_CLR;
			local_temp|=Prescale<<8;
			RCC_CFGR=local_temp;
			break;
		case APB2_PRESCALER:
			local_temp&=APB2_PRESCALE_CLR;
			local_temp|=Prescale<<11;
			RCC_CFGR=local_temp;
			break;
		}
		return OK;
	}
	else
	{
		return NOT_OK;
	}
}
