#ifndef __LIB_USART1_H__
#define __LIB_USART1_H__

#include "Usart_config.h"

#if USE_LIB_USART1

void lib_usart1_init();
void lib_usart1_send_byte(uint8_t data);
void lib_usart1_send_data(uint8_t *data, uint32_t len);
void lib_usart1_send_string(char *data);

#if USART1_RECV_CALLBACK
extern void lib_usart1_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif