#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct
{
	u8* ChannelArr;
	u8 ChainLength;
}ADCChain_t;

void ADC_voidInit(void);
ErrorStatus ADC_u8GetChannelReadingSynchronous(u8 Channel,u16 * Copy_pu16ADCResult);
ErrorStatus ADC_u8GetChannelReadingAsynchronous(u8 Channel,u16 * Copy_pu16ADCResult,void (*Copy_pvCallBackNotification)(void));
ErrorStatus ADC_u8ChainInit(ADCChain_t* Copy_Chain,u8* Copy_pu8ChannelArr,u8 Copy_ChainLength );
ErrorStatus ADC_u8StartChainConversion(ADCChain_t Copy_Chain,u16 *Copy_pu16Result,void (*Copy_pvCallBackNotification)(void));

#endif
