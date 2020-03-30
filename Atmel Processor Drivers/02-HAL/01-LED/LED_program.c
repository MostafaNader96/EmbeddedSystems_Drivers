#include "std_types.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"


void LED_SetLedOn(void)
{
	DIO_SetPinValue(LED_Port,LED_Pin,LED_Mode);
}

void LED_SetLedOff(void)
{	
	DIO_SetPinValue(LED_Port,LED_Pin,LED_Mode^0x01);
}
