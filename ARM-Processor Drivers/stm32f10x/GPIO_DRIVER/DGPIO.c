#include "DGPIO.h"


#define GPIO_CONFIG_MASK	0x0000000f
#define PULL_UP_MODE    	0X0C
#define PULL_DOWN_MODE  	0X08


uint_8t GPIO_Config(GPIO_t *Pins)
{
	uint_8t   local_counter , local_temp = 0;
	uint_64t  local_config = 0;
	uint_16t  local_pin = 0;
	
	local_config  = Pins-> Mode;
	local_config |= Pins-> Speed;
	local_pin = Pins-> local_pin ;

	for(local_counter=0 ; local_counter < 16 ; local_counter++)
	{
		local_temp = local_pin &1;
		if (local_temp)
		{
			local_temp = GPIO_CONFIG_MASK & local_config ;
			if (local_temp != PULL_UP_MODE && local_temp != PULL_DOWN_MODE)
			{
				Pins -> Port -> CR  &= ~ ((uint_64t)GPIO_CONFIG_MASK<<local_counter*4);
				Pins -> Port -> CR  |= ((uint_64t)local_temp<<local_counter*4) ;
			}
			else if(local_temp == PULL_UP_MODE || local_temp == PULL_DOWN_MODE)
			{
				Pins -> Port -> CR  &= ~ ((uint_64t)GPIO_CONFIG_MASK<<local_counter*4);
				Pins -> Port -> CR  |= ((uint_64t)PULL_DOWN_MODE<<local_counter*4) ;
				if(local_temp==PULL_DOWN_MODE)
				{
					Pins->Port->ODR &=(uint_32t) ~(1<<local_counter);
				}
				else if(local_temp==PULL_UP_MODE)
				{
					Pins->Port->ODR |= (uint_32t)(1<<local_counter);
				}
				else
				{
					return NOT_OK;
				}
			}
			else
			{
				return NOT_OK;
			}
		}
		local_config=local_config>>4;
		local_pin=local_pin>>1;
	}
	return OK;
}



uint_8t GPIO_Writee(Port_t *Port, uint_16t Pins ,uint_8t State)
{
	if (State ==SET)
	{
		Port->BSRR= (uint_32t) Pins;
	}
	else if (State ==CLEAR)
	{
		Port->BRR=(uint_32t)Pins;
	}
	else
	{
		return NOT_OK;
	}
return OK;
}

uint_8t GPIO_ReadPort(Port_t *Port,uint_16t *Value)
{
	if (Port == PORT_A ||Port == PORT_B||Port == PORT_C||Port == PORT_D||Port == PORT_E||Port == PORT_F||Port == PORT_G)
	{
		*Value=(uint_16t)Port->IDR;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t GPIO_ReadPin(Port_t *Port,uint_16t Pin,uint_8t *Value)
{
	if (Port == PORT_A ||Port == PORT_B||Port == PORT_C||Port == PORT_D||Port == PORT_E||Port == PORT_F||Port == PORT_G)
	{
		if (Pin==PIN_0 ||Pin==PIN_1 ||Pin==PIN_2 ||Pin==PIN_3 ||Pin==PIN_4 ||Pin==PIN_5 ||Pin==PIN_6 ||Pin==PIN_7 ||Pin==PIN_8 ||Pin==PIN_9 ||Pin==PIN_10 ||Pin==PIN_11 ||Pin==PIN_12 ||Pin==PIN_13 ||Pin==PIN_14 ||Pin==PIN_15)
		{
			if (((uint_16t)Port->IDR)&Pin)
			{
				*Value=1;
			}
			else
			{
				*Value=0;
			}
		}
		else
		{
			return NOT_OK;
		}
	}
	else
	{
		return NOT_OK;
	}
return OK;
}



