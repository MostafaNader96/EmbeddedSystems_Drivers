#include "std_types.h"
#include "bits.h"
#include "EXTI_register.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"

static void (*EXTI_pvCallBack[3])(void)={NULL,NULL,NULL};

void EXTI_voidInit(void)
{
#if EXTI_U8_INT0_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif EXTI_U8_INT0_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error "Wrong EXTI_U8_INT0_CONTROL Configuration"
#endif

#if EXTI_U8_INT1_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif EXTI_U8_INT1_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error "Wrong EXTI_U8_INT1_CONTROL Configuration"
#endif

#if EXTI_U8_INT2_CONTROL == ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif EXTI_U8_INT2_CONTROL == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error "Wrong EXTI_U8_INT2_CONTROL Configuration"
#endif

#if EXTI_U8_INT0_SENSE ==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE ==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE ==FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_U8_INT0_SENSE ==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error "Wrong EXTI_U8_INT0_SENSE Configuration"
#endif

#if EXTI_U8_INT1_SENSE ==LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE ==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE ==FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#elif EXTI_U8_INT1_SENSE ==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
#else
#error "Wrong EXTI_U8_INT1_SENSE Configuration"
#endif


#if EXTI_U8_INT2_SENSE ==FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);
#elif EXTI_U8_INT2_SENSE ==RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error "Wrong EXTI_U8_INT2_SENSE Configuration"
#endif
}

ErrorStatus EXTI_errEnable(u8 Copy_u8IntIdx)
{
	ErrorStatus LocalError=ERROR_OK;
	switch(Copy_u8IntIdx)
	{
	case EXTI_U8_INT0: SET_BIT(GICR,GICR_INT0); break;
	case EXTI_U8_INT1: SET_BIT(GICR,GICR_INT1); break;
	case EXTI_U8_INT2: SET_BIT(GICR,GICR_INT2); break;
	default: LocalError=ERROR_NOK;				break;
	}
	return LocalError;
}

ErrorStatus EXTI_errDisable(u8 Copy_u8IntIdx)
{
	ErrorStatus LocalError=ERROR_OK;
	switch(Copy_u8IntIdx)
	{
	case EXTI_U8_INT0: CLR_BIT(GICR,GICR_INT0); break;
	case EXTI_U8_INT1: CLR_BIT(GICR,GICR_INT1); break;
	case EXTI_U8_INT2: CLR_BIT(GICR,GICR_INT2); break;
	default: LocalError=ERROR_NOK;					break;
	}
	return LocalError;
}

ErrorStatus EXTI_errSetSense(u8 Copy_u8IntIdx,u8 Copy_u8SenseLevel)
{
	ErrorStatus LocalError=ERROR_OK;
	switch(Copy_u8IntIdx)
	{
	case EXTI_U8_INT0:
		if(Copy_u8SenseLevel==EXTI_U8_LOW_LEVEL)
		{
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_ON_CHANGE)
		{
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_FALLING_EDGE)
		{
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_RISING_ENGE)
		{
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
		}
		else LocalError=ERROR_NOK;
		break;
	case EXTI_U8_INT1:
		if(Copy_u8SenseLevel==EXTI_U8_LOW_LEVEL)
		{
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_ON_CHANGE)
		{
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_FALLING_EDGE)
		{
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_RISING_ENGE)
		{
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
		}
		else LocalError=ERROR_NOK;
		break;
	case EXTI_U8_INT2:
		if(Copy_u8SenseLevel==EXTI_U8_FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
		}
		else if(Copy_u8SenseLevel==EXTI_U8_RISING_ENGE)
		{
			SET_BIT(MCUCSR,MCUCSR_ISC2);
		}
		else LocalError=ERROR_NOK;
		break;
	default: LocalError=ERROR_NOK;		break;

	}

	return LocalError;
}

ErrorStatus EXTI_errSetCallBack(u8 Copy_u8IntIdx, void (*Copy_pvCallBack)(void))
{
	ErrorStatus LocalError=ERROR_OK;
	if((Copy_pvCallBack != NULL))
	{
		if(Copy_u8IntIdx<3)
		{
			EXTI_pvCallBack[Copy_u8IntIdx]=Copy_pvCallBack;
		}
		else
			LocalError=ERROR_NOK;
	}
	else
	{
		LocalError=ERROR_NOK;
	}

	return LocalError;
}

/*ISR INT0*/
void __vector_1(void)
{
	if(EXTI_pvCallBack[0]!=NULL)
	{
		EXTI_pvCallBack[0]();
	}
}

/*ISR INT1*/
void __vector_2(void)
{
	if(EXTI_pvCallBack[1]!=NULL)
	{
		EXTI_pvCallBack[1]();
	}
}

/*ISR INT2*/
void __vector_3(void)
{
	if(EXTI_pvCallBack[2]!=NULL)
	{
		EXTI_pvCallBack[2]();
	}
}

