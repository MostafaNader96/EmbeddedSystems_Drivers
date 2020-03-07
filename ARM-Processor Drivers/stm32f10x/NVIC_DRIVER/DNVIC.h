/*
 * DNVIC.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Ahmed Qandeel
 */

#ifndef DNVIC_H_
#define DNVIC_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK		0
#define NOT_OK 	1

#define ALL_PREEMPTION						0X00000300
#define THREE_PREEMPTION_ONE_SUBGROUP		0X00000400
#define TWO_PREEMPTION_TWO_SUBGROUP			0X00000500
#define ONE_PREEMPTION_THREE_SUBGROUP		0X00000600
#define ALL_SUBGROUP						0X00000700



uint_8t NVIC_EnableIRQ(uint_8t IRQn);
uint_8t NVIC_DisableIRQ(uint_8t IRQn);
uint_8t NVIC_SetPendingIRQ (uint_8t IRQn);
uint_8t NVIC_ClearPendingIRQ (uint_8t IRQn);
uint_8t NVIC_GetPendingIRQ (uint_8t IRQn, uint_8t *Val);
uint_8t NVIC_GetActive (uint_8t IRQn, uint_8t *Val);
uint_8t NVIC_SetPriorityGrouping(uint_32t priority_grouping);
uint_8t NVIC_SetPriority (uint_8t IRQn, uint_8t priority);
uint_8t NVIC_GetPriority (uint_8t IRQn, uint_8t *priority);


#endif /* DNVIC_H_ */
