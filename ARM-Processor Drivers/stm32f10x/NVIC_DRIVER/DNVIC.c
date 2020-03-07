/*
 * DNVIC.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Ahmed Qandeel
 */

#include "DNVIC.h"


#define NVIC_BASE_ADDRESS  (( NVIC_t*) 0XE000E100)
#define SCB_AIRCR *((volatile uint_32t*) 0XE000ED0C)
#define NVIC_IPR    (( Prior_t*) 0XE000E400)


#define PASSWORD_MASK  0X05FA0000

typedef struct
{
	uint_32t ISER[8];
	uint_32t Reserved[24];
	uint_32t ICER[8];
	uint_32t Reserved1[24];
	uint_32t ISPR[8];
	uint_32t Reserved2[24];
	uint_32t ICPR[8];
	uint_32t Reserved3[24];
	uint_32t IABR[8];
}NVIC_t;

typedef struct
{
	uint_8t IPR[240];
}Prior_t;



NVIC_t   *NV=NVIC_BASE_ADDRESS;
Prior_t  *Prior_Arr=NVIC_IPR;

uint_8t NVIC_EnableIRQ(uint_8t IRQn)
{
	if( IRQn<240)
	{
    NV->ICPR[IRQn/32]=1<<IRQn%32;
    NV->ISER[IRQn/32]=1<<IRQn%32;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}


uint_8t NVIC_DisableIRQ(uint_8t IRQn)
{
	if( IRQn<240)
	{

    NV->ICER[IRQn/32]= 1<<IRQn%32;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t NVIC_SetPendingIRQ (uint_8t IRQn)
{
	if( IRQn<240)
	{
    NV->ISPR[IRQn/32] = 1<<IRQn%32;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t NVIC_ClearPendingIRQ (uint_8t IRQn)
{
	if( IRQn<240)
	{
    NV->ICPR[IRQn/32] = 1<<IRQn%32;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t NVIC_GetPendingIRQ (uint_8t IRQn, uint_8t *Val)
{
	if( IRQn<240)
	{
		*Val= (NV->ICPR[IRQn/32] >> IRQn%32) & 1 ;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t NVIC_GetActive (uint_8t IRQn, uint_8t *Val)
{
	if( IRQn<240)
	{
		*Val= (NV->IABR[IRQn/32] >> IRQn%32) & 1 ;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

uint_8t NVIC_SetPriorityGrouping(uint_32t priority_grouping)
{
	if(priority_grouping==ALL_PREEMPTION || priority_grouping==THREE_PREEMPTION_ONE_SUBGROUP || priority_grouping==TWO_PREEMPTION_TWO_SUBGROUP || priority_grouping==ONE_PREEMPTION_THREE_SUBGROUP || priority_grouping==ALL_SUBGROUP )
	{
		SCB_AIRCR=priority_grouping|PASSWORD_MASK;
	}
	else
	{
		return NOT_OK;
	}
	return OK;

}

uint_8t NVIC_SetPriority (uint_8t IRQn, uint_8t priority)
{
	if( IRQn<240)
	{
		if(priority<16)
		{
			Prior_Arr->IPR[IRQn] = priority<<4 ;
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

uint_8t NVIC_GetPriority (uint_8t IRQn, uint_8t *priority)
{
	if( IRQn<240)
	{

		*priority=Prior_Arr->IPR[IRQn]>>4 ;
	}
	else
	{
		return NOT_OK;
	}
	return OK;
}

