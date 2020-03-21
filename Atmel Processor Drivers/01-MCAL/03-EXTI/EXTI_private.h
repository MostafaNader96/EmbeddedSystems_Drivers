#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#define ENABLED  		1
#define DISABLED 		2

#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#define GICR_INT1		7
#define GICR_INT0		6
#define GICR_INT2		5

#define MCUCR_ISC00 	0
#define MCUCR_ISC01 	1
#define MCUCR_ISC10 	2
#define MCUCR_ISC11 	3

#define MCUCSR_ISC2 	6

void __vector_1 (void) __attribute__((signal));
void __vector_2 (void) __attribute__((signal));
void __vector_3 (void) __attribute__((signal));


#endif
