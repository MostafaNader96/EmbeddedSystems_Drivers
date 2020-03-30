#ifndef SEVENSEGMENT_INTERFACE_H_
#define SEVENSEGMENT_INTERFACE_H_

#define SEVEN_SEGMENT_1		0
#define SEVEN_SEGMENT_2		1

u8 SEVENSEG_SetNumber(u8 number);
void SEVENSEG_Enable(u8 SEVENSEGNumber);
void SEVENSEG_Disable(u8 SEVENSEGNumber);

#endif
