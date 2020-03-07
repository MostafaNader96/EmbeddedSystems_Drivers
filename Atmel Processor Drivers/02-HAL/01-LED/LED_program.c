#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"


void SetLedOn  (void)
{
	SetPinValue(LED_Port,LED_Pin,LED_Mode);
}

void SetLedOff (void)
{	
	SetPinValue(LED_Port,LED_Pin,LED_Mode^0x01);
}
