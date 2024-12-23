#ifndef __LIB_USART0_H__
#define __LIB_USART0_H__

#include "Usart_config.h"

#if USE_LIB_USART0


void lib_usart0_init();
void lib_usart0_send_byte(uint8_t data);
void lib_usart0_send_data(uint8_t *data, uint32_t len);
void lib_usart0_send_string(char *data);

#if USART0_RECV_CALLBACK
extern void lib_usart0_on_recv(uint8_t *data, uint32_t len);
#endif


#endif // USE_USART0

#endif //__USART0_H__