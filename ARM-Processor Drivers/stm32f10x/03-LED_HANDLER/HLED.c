#include "DGPIO.h"
#include "HLED.h"
#include "HLED_config.h"

extern HLED_map LED[LED_NUM];
extern GPIO_t LED_Init[LED_NUM];

void HLED_Init(void)
{
	uint_8t CountLed;
	for(CountLed=0;CountLed<LED_NUM;CountLed++)
	{
		GPIO_Config(&LED_Init[CountLed]);
	}
}

void HLED_SetLedState(uint_8t Led_Number,uint_8t Led_State)
{
	switch(Led_State)
	{
		case SET:
		GPIO_Writee(LED[Led_Number].Led_Port, LED[Led_Number].Led_Pin , LED[Led_Number].Led_ON);
		break;
		
		case CLEAR:
		GPIO_Writee(LED[Led_Number].Led_Port, LED[Led_Number].Led_Pin , (LED[Led_Number].Led_ON ^ 0x1));
		break;			
	}
}
