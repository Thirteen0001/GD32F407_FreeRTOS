#ifndef __LIB_UART7_H__
#define __LIB_UART7_H__

#include "Usart_config.h"

#if USE_LIB_UART7

void lib_uart7_init();
void lib_uart7_send_data(uint8_t data);
void lib_uart7_send_string(char *data);

#if UART7_RECV_CALLBACK
extern void lib_uart7_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif