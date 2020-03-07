#include <stdio.h>

#define Pin0 0
#define Pin1 1
#define Pin2 1
#define Pin3 0

#define PORTA_Dir 					Conc(Pin0,Pin1,Pin2,Pin3)
#define Conc(b0,b1,b2,b3)			Conc_helper(b0,b1,b2,b3)
#define Conc_helper(b0,b1,b2,b3)	0b##b3##b2##b1##b0

void main()
{
	
	int PORTA= PORTA_Dir;
	
	
}