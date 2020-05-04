#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

/*OPTIONS: DIABLED , EVEN , ODD*/
#define UART_u8_PARITY	 	UART_PARITY_DISABLED

/*OPTIONS: 4800 , 9600 , 115200*/
#define UART_u8_BAUD_RATE	UART_BAUD_9600

/*OPTIONS: 1BIT, 2BIT*/
#define UART_u8_STOP_BITS	UART_STOP_1_BIT

/*OPTIONS: 8M , 12M , 16M*/
#define UART_u8_SYS_FREQ	UART_SYS_FREQ_8M

#define TIMEOUT_THRESHOLD	10000UL

#endif