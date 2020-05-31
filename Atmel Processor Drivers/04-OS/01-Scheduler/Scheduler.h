#ifndef SCHEDULER_H_
#define SCEDULER_H_

#define TICKTIME	  1		//IN ms
#define TASKNUMBERS	  2

#define RUNNING   	  1U
#define SUSPENDED     2U


typedef struct
{
	void(*Taskhandler)(void);
	u32	Periodicity;
	u32 FirstDelay;
	u8  State;
}Task;



void Scheduler_StartOS(void);
void Scheduler_SuspendTask(u8 TaskID);
void Scheduler_ResumeTask(u8 TaskID);
void Scheduler_CreateTask(u8 Priority,u32 Periodicity,void(*handler)(void), u32 FirstDelay,u8 State);

#endif

