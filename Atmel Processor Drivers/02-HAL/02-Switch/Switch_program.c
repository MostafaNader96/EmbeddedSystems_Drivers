#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "Switch_interface.h"
#include "Switch_private.h"
#include "Switch_config.h"

void SWITCH_SwitchState(u8 *Data)
{
	DIO_GetPinValue(Switch_Port,Switch_Pin,Data);
	
	#if RELEASE_STATE==PULL_UP_RESISTOR
		 *Data=*Data^0x01;
	#endif
}
