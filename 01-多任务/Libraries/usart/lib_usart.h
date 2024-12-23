#ifndef __LIB_USART_H__
#define __LIB_USART_H__

#include "Usart_config.h"


#if USE_LIB_USART0
#include "lib_usart0.h"
#endif

#if USE_LIB_USART1
#include "lib_usart1.h"
#endif

#if USE_LIB_USART2
#include "lib_usart2.h"
#endif

#if USE_LIB_UART3
#include "lib_uart3.h"
#endif

#if USE_LIB_UART4
#include "lib_uart4.h"
#endif

#if USE_LIB_USART5
#include "lib_usart5.h"
#endif


#if USE_LIB_UART6
#include "lib_uart6.h"
#endif


#if USE_LIB_UART7
#include "lib_uart7.h"
#endif


void lib_usart_init();


#endif