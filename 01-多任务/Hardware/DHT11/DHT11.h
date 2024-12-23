#ifndef __DHT11_H__
#define __DHT11_H__

#include "gd32f4xx.h"
#include <stdio.h>
#include "systick.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#define DHT_RCU			RCU_GPIOB
#define DHT_PORT		GPIOB
#define DHT_PIN			GPIO_PIN_15

void DHT11_init();
// 返回-1：获取数据失败， 返回0：获取数据成功
char DHT11_get_humidity_temperature(int *humidity, float *temperature);

#endif