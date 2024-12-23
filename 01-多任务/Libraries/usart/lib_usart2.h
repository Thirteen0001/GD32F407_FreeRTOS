#ifndef __LIB_USART2_H__
#define __LIB_USART2_H__

#include "Usart_config.h"

#if USE_LIB_USART2

void lib_usart2_init();
void lib_usart2_send_byte(uint8_t data);
void lib_usart2_send_data(uint8_t *data, uint32_t len);
void lib_usart2_send_string(char *data);

#if USART2_RECV_CALLBACK
extern void lib_usart2_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif