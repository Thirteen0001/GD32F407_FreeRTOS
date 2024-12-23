#ifndef __USART_CONF_H__
#define __USART_CONF_H__

#include "gd32f4xx.h"
#include "systick.h"


#define USE_LIB_USART0	1
#define USE_LIB_USART1	0
#define USE_LIB_USART2	0
#define USE_LIB_UART3	0
#define USE_LIB_UART4	0
#define USE_LIB_USART5	0
#define USE_LIB_UART6	0
#define USE_LIB_UART7	0

#define USE_LIB_PRINT	0
//#define USE_LIB_PRINT	1
//#define USE_LIB_PRINT	2
//#define USE_LIB_PRINT	3
//#define USE_LIB_PRINT	4
//#define USE_LIB_PRINT	5
//#define USE_LIB_PRINT	6
//#define USE_LIB_PRINT	7


/**************** USART 0 *****************/
#if USE_LIB_USART0
#define USART0_ENABLE_SEND			1
#define USART0_ENABLE_RECV			1
#define USART0_RECV_LEN				512
#define USART0_RECV_NVIC_IRQ		2, 2
#define USART0_RECV_CALLBACK		1
#define USART0_ENABLE_DMA_SEND		0
#define USART0_ENABLE_DMA_RECV		0

//////// TX GPIO config
// PIN:	|	PA9	|	PA15	|	PB6
#define USART0_TX_RCU					RCU_GPIOA
#define USART0_TX_PORT					GPIOA
#define USART0_TX_PIN					GPIO_PIN_9

//////// RX GPIO config
// PIN:	| PA10 | PB3	| PB7
#define USART0_RX_RCU					RCU_GPIOA
#define USART0_RX_PORT					GPIOA
#define USART0_RX_PIN					GPIO_PIN_10

// 	USART0 
//				DMA		CHN		SUBPERI 
//	TX		1			7			4
//	RX		1			2			4
//	RX		1			5			4
// DMA RX config (2 or 5)
#if USART0_ENABLE_DMA_RECV
#define USART0_DMA_RX_CHN 		DMA_CH2
#endif

// param config
#define USART0_PARAM_BAUDRATE			115200
#define USART0_PARAM_PARITY				USART_PM_NONE
#define USART0_PARAM_WORD_LEN			USART_WL_8BIT
#define USART0_PARAM_STOP_BIT			USART_STB_1BIT
#define USART0_PARAM_DATA_FIRST			USART_MSBF_LSB

#endif

/**************** USART 1 *****************/
#if USE_LIB_USART1
#define USART1_ENABLE_SEND			1
#define USART1_ENABLE_RECV			1
#define USART1_RECV_LEN				512
#define USART1_RECV_NVIC_IRQ		2, 2
#define USART1_RECV_CALLBACK		0
#define USART1_ENABLE_DMA_SEND		1
#define USART1_ENABLE_DMA_RECV		1

// TX GPIO config
// PIN:	|	PA2	|	PD5
#define USART1_TX_RCU		RCU_GPIOD
#define USART1_TX_PORT		GPIOD
#define USART1_TX_PIN		GPIO_PIN_5

// RX GPIO config
// PIN:	| PA3	|  PD6	
#define USART1_RX_RCU		RCU_GPIOD
#define USART1_RX_PORT		GPIOD
#define USART1_RX_PIN		GPIO_PIN_6

// param config
#define USART1_PARAM_BAUDRATE			9600
#define USART1_PARAM_PARITY				USART_PM_NONE
#define USART1_PARAM_WORD_LEN			USART_WL_8BIT
#define USART1_PARAM_STOP_BIT			USART_STB_1BIT
#define USART1_PARAM_DATA_FIRST			USART_MSBF_LSB
#endif

/**************** USART 2 *****************/
#if USE_LIB_USART2
#define USART2_ENABLE_SEND			1
#define USART2_ENABLE_RECV			1
#define USART2_RECV_LEN				512
#define USART2_RECV_NVIC_IRQ		2, 2
#define USART2_RECV_CALLBACK		1
#define USART2_ENABLE_DMA_SEND		1
#define USART2_ENABLE_DMA_RECV		1

// TX GPIO config
// PIN:	|	PB10	|	PC10	|	PD8
#define USART2_TX_RCU			RCU_GPIOB
#define USART2_TX_PORT			GPIOB
#define USART2_TX_PIN			GPIO_PIN_10

// RX GPIO config
// PIN:	|	PB11	|	PC5		|	PD9
#define USART2_RX_RCU			RCU_GPIOB
#define USART2_RX_PORT			GPIOB
#define USART2_RX_PIN			GPIO_PIN_11

// param config
#define USART2_PARAM_BAUDRATE		9600
#define USART2_PARAM_PARITY			USART_PM_NONE
#define USART2_PARAM_WORD_LEN		USART_WL_8BIT
#define USART2_PARAM_STOP_BIT		USART_STB_1BIT
#define USART2_PARAM_DATA_FIRST		USART_MSBF_LSB

#endif


/**************** UART 3 *****************/
#if USE_LIB_UART3
#define UART3_ENABLE_SEND		1
#define UART3_ENABLE_RECV		1
#define UART3_RECV_LEN			1024
#define UART3_RECV_NVIC_IRQ		2, 2
#define UART3_RECV_CALLBACK		1
#define UART3_ENABLE_DMA_SEND	1
#define UART3_ENABLE_DMA_RECV	1

// TX GPIO config
// PIN:	|	PA0	|	PC10
#define UART3_TX_RCU	RCU_GPIOA
#define UART3_TX_PORT	GPIOA
#define UART3_TX_PIN	GPIO_PIN_2


// RX GPIO config
// PIN:	| PA1	|  PC11	
#define UART3_RX_RCU	RCU_GPIOA
#define UART3_RX_PORT	GPIOA
#define UART3_RX_PIN	GPIO_PIN_3

// param config
#define UART3_PARAM_BAUDRATE		115200
#define UART3_PARAM_PARITY			USART_PM_NONE
#define UART3_PARAM_WORD_LEN		USART_WL_8BIT
#define UART3_PARAM_STOP_BIT		USART_STB_1BIT
#define UART3_PARAM_DATA_FIRST		USART_MSBF_LSB
#endif


/**************** UART 4 *****************/
#if USE_LIB_UART4
#define UART4_ENABLE_SEND		1
#define UART4_ENABLE_RECV		1
#define UART4_RECV_LEN			512
#define UART4_RECV_NVIC_IRQ		2, 2
#define UART4_RECV_CALLBACK		1
#define UART4_ENABLE_DMA_SEND	1
#define UART4_ENABLE_DMA_RECV	1

// TX GPIO config
// PIN:	PC12
#define UART4_TX_RCU	RCU_GPIOC
#define UART4_TX_PORT	GPIOC
#define UART4_TX_PIN	GPIO_PIN_12

// RX GPIO config
// PIN:	PD2	
#define UART4_RX_RCU	RCU_GPIOD
#define UART4_RX_PORT	GPIOD
#define UART4_RX_PIN	GPIO_PIN_2

// param config
#define UART4_PARAM_BAUDRATE	115200
#define UART4_PARAM_PARITY		USART_PM_NONE
#define UART4_PARAM_WORD_LEN	USART_WL_8BIT
#define UART4_PARAM_STOP_BIT	USART_STB_1BIT
#define UART4_PARAM_DATA_FIRST	USART_MSBF_LSB

#endif

/**************** USART 5 *****************/
#if USE_LIB_USART5
#define USART5_ENABLE_SEND		1
#define USART5_ENABLE_RECV		1
#define USART5_RECV_LEN			512
#define USART5_RECV_NVIC_IRQ	2, 2
#define USART5_RECV_CALLBACK	1
#define USART5_ENABLE_DMA_SEND	1
#define USART5_ENABLE_DMA_RECV	1

// TX GPIO config 
// PIN:	|	PA11	|	PC6		|	PG14
#define USART5_TX_RCU		RCU_GPIOG
#define USART5_TX_PORT		GPIOG
#define USART5_TX_PIN		GPIO_PIN_14


// RX GPIO config
// PIN:	|	PA12	|	PC7		|	PG9
#define USART5_RX_RCU		RCU_GPIOG
#define USART5_RX_PORT		GPIOG
#define USART5_RX_PIN		GPIO_PIN_9

// 	USART2 
//			DMA		CHN		SUBPERI 
//	TX	1			6			5
//	TX	1			7			5
//	RX	1			1			5
//	RX	1			2			5

// DMA TX config(6 or 7)
#if USART5_ENABLE_DMA_SEND
#define USART5_DMA_TX_CHN			DMA_CH6
#endif

// DMA RX config(1 or 2)
#if USART5_ENABLE_DMA_RECV
#define USART5_DMA_RX_CHN 		DMA_CH1
#endif

// param config
#define USART5_PARAM_BAUDRATE		9600
#define USART5_PARAM_PARITY			USART_PM_NONE
#define USART5_PARAM_WORD_LEN		USART_WL_8BIT
#define USART5_PARAM_STOP_BIT		USART_STB_1BIT
#define USART5_PARAM_DATA_FIRST		USART_MSBF_LSB

#endif


/**************** UART 6 *****************/
#if USE_LIB_UART6
#define UART6_ENABLE_SEND			1
#define UART6_ENABLE_RECV			1
#define UART6_RECV_LEN				512
#define UART6_RECV_NVIC_IRQ			2, 2
#define UART6_RECV_CALLBACK			1
#define UART6_ENABLE_DMA_SEND		1
#define UART6_ENABLE_DMA_RECV		1

// TX GPIO config
// PIN:	|	PE8	| PF7
#define UART6_TX_RCU	RCU_GPIOE
#define UART6_TX_PORT	GPIOE
#define UART6_TX_PIN	GPIO_PIN_8

// RX GPIO config
// PIN:	| PE7	| PE8
#define UART6_RX_RCU	RCU_GPIOE
#define UART6_RX_PORT	GPIOE
#define UART6_RX_PIN	GPIO_PIN_7

// param config
#define UART6_PARAM_BAUDRATE		115200
#define UART6_PARAM_PARITY			USART_PM_NONE
#define UART6_PARAM_WORD_LEN		USART_WL_8BIT
#define UART6_PARAM_STOP_BIT		USART_STB_1BIT
#define UART6_PARAM_DATA_FIRST		USART_MSBF_LSB

#endif


/**************** USART 7 *****************/
#if USE_LIB_UART7
#define UART7_ENABLE_SEND		1
#define UART7_ENABLE_RECV		1
#define UART7_RECV_LEN			512
#define UART7_RECV_NVIC_IRQ		2, 2
#define UART7_RECV_CALLBACK		1
#define UART7_ENABLE_DMA_SEND	1
#define UART7_ENABLE_DMA_RECV	1

// TX GPIO config
// PIN:	|	PE1
#define UART7_TX_RCU	RCU_GPIOE
#define UART7_TX_PORT	GPIOE
#define UART7_TX_PIN	GPIO_PIN_1

// RX GPIO config
// PIN:	| PE0
#define UART7_RX_RCU	RCU_GPIOE
#define UART7_RX_PORT	GPIOE
#define UART7_RX_PIN	GPIO_PIN_0

// param config
#define UART7_PARAM_BAUDRATE		115200
#define UART7_PARAM_PARITY			USART_PM_NONE
#define UART7_PARAM_WORD_LEN		USART_WL_8BIT
#define UART7_PARAM_STOP_BIT		USART_STB_1BIT
#define UART7_PARAM_DATA_FIRST		USART_MSBF_LSB

#endif


#endif