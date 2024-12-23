#include "lib_usart.h"


void lib_usart_init() {
#if USE_LIB_USART0
	lib_usart0_init();
#endif

#if USE_LIB_USART1
	lib_usart1_init();
#endif

#if USE_LIB_USART2
	lib_usart2_init();
#endif

#if USE_LIB_UART3
	lib_uart3_init();
#endif

#if USE_LIB_UART4
	lib_uart4_init();
#endif

#if USE_LIB_USART5
	lib_usart5_init();
#endif

#if USE_LIB_UART6
	lib_uart6_init();
#endif

#if USE_LIB_UART7
	lib_uart7_init();
#endif

}
