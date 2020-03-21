#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX	 *((u8*)0x27)
#define ADCSRA 	 *((u8*)0x26)
#define ADC 	 *((volatile u16*)0x24)

#endif
