#ifndef __BSP_KEYS_H__
#define __BSP_KEYS_H__


#include "gd32f4xx.h"



#define KEY1_RCC                   RCU_GPIOC
#define KEY1_PIN                   GPIOC, GPIO_PIN_0

#define KEY2_RCC                   RCU_GPIOC
#define KEY2_PIN                   GPIOC, GPIO_PIN_1

#define KEY3_RCC                   RCU_GPIOC
#define KEY3_PIN                   GPIOC, GPIO_PIN_2

#define KEY4_RCC                   RCU_GPIOC
#define KEY4_PIN                   GPIOC, GPIO_PIN_3



void keys_init();

void keys_scan();


/// 回调函数，中断函数
extern void keys_on_down(uint8_t i);
extern void keys_on_up(uint8_t i);


#endif