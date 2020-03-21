#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

void __vector_16(void) __attribute__((signal));

#define ADC_IDLE	0
#define ADC_BUSY	1

#define ADC_STATE_CHAIN 			1
#define ADC_SINGLE_CHANNEL_STATE	0

#define ADMUX_REFS0		6
#define ADMUX_REFS1		7
#define ADMUX_ADLAR		5

#define ADCSRA_ADEN		7
#define ADCSRA_ADSC		6
#define ADCSRA_ADIF		4
#define ADCSRA_ADIE		3
#define ADCSRA_ADPS2	2
#define ADCSRA_ADPS1	1
#define ADCSRA_ADPS0	0

#endif
