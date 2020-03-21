#ifndef DRCC_H_
#define DRCC_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK 								0
#define NOT_OK 							1

#define ON 								1
#define OFF 							0

#define HSI_FREQ						8000000
#define HSE_FREQ						8000000

#define HSI_ENABLE 						0x10000001
#define HSE_ENABLE 						0x10010000
#define PLL_ENABLE 						0x11000000

#define HSI_SYS    						0x20000000
#define HSE_SYS    						0x20000001
#define PLL_SYS    						0x20000002

#define PLL_INPUT_CLOCK_X_2   			0
#define PLL_INPUT_CLOCK_X_3   			1
#define PLL_INPUT_CLOCK_X_4   			2
#define PLL_INPUT_CLOCK_X_5   			3
#define PLL_INPUT_CLOCK_X_6   			4
#define PLL_INPUT_CLOCK_X_7   			5
#define PLL_INPUT_CLOCK_X_8   			6
#define PLL_INPUT_CLOCK_X_9   			7
#define PLL_INPUT_CLOCK_X_10  			8
#define PLL_INPUT_CLOCK_X_11  			9
#define PLL_INPUT_CLOCK_X_12  			10
#define PLL_INPUT_CLOCK_X_13  			11
#define PLL_INPUT_CLOCK_X_14  			12
#define PLL_INPUT_CLOCK_X_15  			13
#define PLL_INPUT_CLOCK_X_16  			14

#define HSE_SRC							0x40010000
#define HSE_SRC_DIV_TWO					0x40030000
#define HSI_SRC_DIV_TWO					0x40000000

#define GPIO_A_ENABLE 					0x20000004
#define GPIO_B_ENABLE 					0x20000008
#define GPIO_C_ENABLE 					0x20000010
#define GPIO_D_ENABLE 					0x20000020
#define GPIO_E_ENABLE 					0x20000040
#define GPIO_F_ENABLE 					0x20000080
#define GPIO_G_ENABLE 					0x20000100

#define AHB_PRESCALER  					0x08000000
#define APB1_PRESCALER 					0x08000001
#define APB2_PRESCALER 					0x08000002

#define APB2_PRESCALER_NOT_DIVIDED 		0
#define APB2_PRESCALER_DIV_2       		4
#define APB2_PRESCALER_DIV_4       		5
#define APB2_PRESCALER_DIV_8       		6
#define APB2_PRESCALER_DIV_16      		7

#define APB1_PRESCALER_NOT_DIVIDED 		0
#define APB1_PRESCALER_DIV_2       		4
#define APB1_PRESCALER_DIV_4       		5
#define APB1_PRESCALER_DIV_8       		6
#define APB1_PRESCALER_DIV_16      		7

#define AHB_PRESCALER_NOT_DIVIDED 		0
#define AHB_PRESCALER_DIV_2       		8
#define AHB_PRESCALER_DIV_4       		9
#define AHB_PRESCALER_DIV_8   	  		10
#define AHB_PRESCALER_DIV_16      		11
#define AHB_PRESCALER_DIV_64      		12
#define AHB_PRESCALER_DIV_128     		13
#define AHB_PRESCALER_DIV_256     		14
#define AHB_PRESCALER_DIV_512     		15

#define AHB_BUS  						77
#define APB1_BUS 						78
#define APB2_BUS 						79

uint_8t RCC_SetClkStatus (uint_32t Clk,uint_8t Status);
uint_8t RCC_SetSystemClk (uint_32t Clk);
uint_8t RCC_SetPLLConfig (uint_32t Src, uint_8t Mul);
uint_8t RCC_SetPeripheralStatus (uint_32t Peripheral,uint_8t Status);
uint_8t RCC_SetBusPrescaler (uint_32t Bus,uint_8t Prescaler);
uint_8t RCC_GetBusClock (uint_32t Bus,uint_32t *Clk);

#endif