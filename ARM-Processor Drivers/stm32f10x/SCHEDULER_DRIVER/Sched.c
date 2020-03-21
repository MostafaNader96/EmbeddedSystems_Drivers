#include "DRCC.h"
#include "DSYSTICK.h"
#include "Sched.h"
#include "Sched_config.h"

#define TASK_READY 		1
#define TASK_SUSPEND 	2

typedef struct
{
	TaskBaseInfo_t * TaskInfo;
	uint_32t state;
	uint_32t PeriodTicks;
	uint_32t TicksToExec;
}systask_t;

uint_32t OSFlag;
systask_t SysTask [MAX_TASKS];
uint_8t idx;
extern  TaskBaseInfo_t SysTask_info [MAX_TASKS];

static void Sched_SetOSFlag (void)
{
	OSFlag++;
}

static void Sched(void)
{
	for (idx=0;idx<MAX_TASKS;idx++)
	{
		if (SysTask[idx].TicksToExec==0 && SysTask[idx].state==TASK_READY)
		{
			SysTask[idx].TaskInfo->AppTask->Runnable();
			SysTask[idx].TicksToExec=SysTask[idx].PeriodTicks;
		}
		SysTask[idx].TicksToExec--;
	}
}

uint_8t Sched_Init(void)
{
	uint_8t local_count;
	uint_8t localError;
	uint_32t BusFreq;
	localError=RCC_GetBusClock(AHB_BUS,&BusFreq);
	if (!localError)
	{
		asm("NOP");
	}
	else
	{
		localError=NOT_OK;
	}
	
	SYSTICK_Init();
	SYSTICK_SetCallback(&Sched_SetOSFlag);
	SYSTICK_SetTime(SCHED_TICK_mSEC*1000,BusFreq);
	
	for (local_count=0;local_count<MAX_TASKS;local_count++)
	{
		SysTask[local_count].TaskInfo=&SysTask_info[local_count];
		SysTask[local_count].state=TASK_READY;
		SysTask[local_count].PeriodTicks=(SysTask[local_count].TaskInfo->AppTask->periodicity)/SCHED_TICK_mSEC;
		SysTask[local_count].TicksToExec=(SysTask[local_count].TaskInfo->FirstDelay)/SCHED_TICK_mSEC;
	}
	return localError;
}

uint_8t Sched_Start(void)
{
	SYSTICK_Start();
	while (1)
	{
		if (OSFlag)
		{
			OSFlag--;
			Sched();
		}
	}
}

void Sched_Suspend(void)
{
	SysTask[idx].state=TASK_SUSPEND;
}

