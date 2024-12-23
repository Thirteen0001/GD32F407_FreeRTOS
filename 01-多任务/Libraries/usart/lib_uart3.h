#ifndef __LIB_UART3_H__
#define __LIB_UART3_H__

#include "Usart_config.h"

#if USE_LIB_UART3

void lib_uart3_init();
void lib_uart3_send_data(uint8_t data);
void lib_uart3_send_string(char *data);

#if UART3_RECV_CALLBACK
extern void lib_uart3_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif