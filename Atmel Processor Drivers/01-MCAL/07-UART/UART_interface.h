/*author : mostafa nader*/
/*date : 9 mar 2020*/
/*version : v01*/


#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

#include "std_types.h"

void UART_voidInitialize(void);
u8 UART_voidTransmitDataSynch (u8 Copy_u8Data);
void UART_voidTransmitDataAsynch(u8 Copy_u8Data,void(*copy_ptr)(void));

u8 UART_u8ReceiveSynch(u8 * Copy_pu8Data);
void UART_u8ReceiveAsynch(void(*Copy_ptr)(u8));

u8 UART_TX_SetCallBack(void (*Copy_pvCallBack)(void));
u8 UART_RX_SetCallBack(void (*Copy_pvCallBack)(void));




#endif
