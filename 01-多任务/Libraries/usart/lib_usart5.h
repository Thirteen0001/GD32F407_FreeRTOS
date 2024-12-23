#ifndef __LIB_USART5_H__
#define __LIB_USART5_H__

#include "Usart_config.h"

#if USE_LIB_USART5

void lib_usart5_init();
void lib_usart5_send_byte(uint8_t data);
void lib_usart5_send_data(uint8_t* data, uint32_t len);
void lib_usart5_send_string(char *data);

#if USART5_RECV_CALLBACK
extern void lib_usart5_on_recv(uint8_t *data, uint32_t len);
#endif

#endif

#endif