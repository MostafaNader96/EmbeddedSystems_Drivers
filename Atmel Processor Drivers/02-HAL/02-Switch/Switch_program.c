#include "std_types.h"
#include "bits.h"
#include "DIO_interface.h"
#include "Switch_interface.h"
#include "Switch_private.h"
#include "Switch_config.h"


u8 SwitchState  (void)
{
	u8 result;
	result=(GetPinVal(Switch_Port,Switch_Pin));
	
	#if RELEASE_STATE==0
		return result;
	#else
		return result^1;
	#endif
}
