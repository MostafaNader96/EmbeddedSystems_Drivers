#define TASKNUMBERS	  3
#define RUNNING   	  1U
#define SUSPENDED     2U


typedef struct
{
	void(*Taskhandler)(void);
	u32 Periodicity;			//In Ticks
	u32 FirstDelay;
	u8  State;
}Task;



void RTOS_StartOS(void);
void RTOS_SuspendTask(u8 TaskID);
void RTOS_ResumeTask(u8 TaskID);
void scheduler(void);
void RTOS_CreateTask(u8 Priority,u32 Periodicity,void(*handler)(void), u32 FirstDelay,u8 State);

