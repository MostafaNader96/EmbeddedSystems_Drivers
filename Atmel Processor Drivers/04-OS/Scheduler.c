/*
 * Scheduler.c
 *
 *  Created on: Feb 10, 2020
 *      Author: MOSTAFA
 */

#include "../../Library/std_types.h"
#include "../Scheduler/Scheduler.h"
#include "../TIMER/TIMER_interface.h"

static void Scheduler(void);

Task SystemTasks[TASKNUMBERS];

void Timer_CallBack(void);

void Scheduler_StartOS(void)
{

	Timer0_voidSetCallBack(&Timer_CallBack);

	Timer0_voidInit();

	Timer0_SetTimeus(250);

}


void Scheduler_SuspendTask(u8 TaskID)
{
	SystemTasks[TaskID].State=SUSPENDED;
}

void Scheduler_ResumeTask(u8 TaskID)
{
	SystemTasks[TaskID].State=RUNNING;
}

static void Scheduler(void)
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




void Scheduler_CreateTask(u8 Priority,u32 Periodicity,void(*handler)(void), u32 FirstDelay,u8 State)
{
	if(SystemTasks[Priority].Periodicity==0)
	{
	SystemTasks[Priority].Periodicity=Periodicity;
	SystemTasks[Priority].Taskhandler=handler;
	SystemTasks[Priority].FirstDelay=FirstDelay;
	SystemTasks[Priority].State=State;
	}

}


void Timer_CallBack(void)
{
	static u8 counter;
	counter++;

	if(4==counter)
	{
		counter=0;
		Scheduler();
	}
}
