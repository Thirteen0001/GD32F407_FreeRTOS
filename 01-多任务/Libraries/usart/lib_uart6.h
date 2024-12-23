#ifndef __LIB_UART6_H__
#define __LIB_UART6_H__

#include "Usart_config.h"

#if USE_LIB_UART6

void lib_uart6_init();
void lib_uart6_send_data(uint8_t data);
void lib_uart6_send_string(char *data);

#if UART6_RECV_CALLBACK
extern void lib_uart6_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif