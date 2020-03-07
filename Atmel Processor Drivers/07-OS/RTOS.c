/*
 * RTOS.c
 *
 *  Created on: Feb 10, 2020
 *      Author: MOSTAFA
 */
#include "std_types.h"
#include "bits.h"
#include "RTOS.h"


Task SystemTasks[TASKNUMBERS];


void RTOS_StartOS(void)
{
	STK_voidSetCallBack(scheduler);
	STK_voidSrart();
	STK_voidSrart1(500000);
}


void RTOS_SuspendTask(u8 TaskID)
{
	SystemTasks[TaskID].State=SUSPENDED;
}

void RTOS_ResumeTask(u8 TaskID)
{
	SystemTasks[TaskID].State=RUNNING;
}

void scheduler(void)
{

	u8 i;
	for(i=0;i<TASKNUMBERS;i++)
	{

		if(SystemTasks[i].State==RUNNING)
		{
			if(SystemTasks[i].FirstDelay==0)
			{
				SystemTasks[i].FirstDelay=SystemTasks[i].Periodicity-1;
				SystemTasks[i].Taskhandler();
			}
			else
			{
				SystemTasks[i].FirstDelay--;
			}
		}
		else
		{
			/*Task Suspended*/

		}

	}

}




void RTOS_CreateTask(u8 Priority,u32 Periodicity,void(*handler)(void), u32 FirstDelay,u8 State)
{
	if(SystemTasks[Priority].Periodicity==0)
	{
	SystemTasks[Priority].Periodicity=Periodicity;
	SystemTasks[Priority].Taskhandler=handler;
	SystemTasks[Priority].FirstDelay=FirstDelay;
	SystemTasks[Priority].State=State;
	}

}
