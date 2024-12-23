#ifndef __LIB_UART4_H__
#define __LIB_UART4_H__

#include "Usart_config.h"

#if USE_LIB_UART4

void lib_uart4_init();
void lib_uart4_send_data(uint8_t data);
void lib_uart4_send_string(char *data);

#if UART4_RECV_CALLBACK
extern void lib_uart4_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif