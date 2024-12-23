#ifndef __BSP_LEDS_H__
#define __BSP_LEDS_H__

#include "gd32f4xx.h"


#define LEDn 														8


#define LEDSW_GPIO_CLK                   RCU_GPIOC
#define LEDSW_GPIO_PORT                  GPIOC
#define LEDSW_PIN                        GPIO_PIN_6



#define LED1_GPIO_CLK                   RCU_GPIOD
#define LED1_GPIO_PORT                  GPIOD
#define LED1_PIN                        GPIO_PIN_8

#define LED2_GPIO_CLK                   RCU_GPIOD
#define LED2_GPIO_PORT                  GPIOD
#define LED2_PIN                        GPIO_PIN_9

#define LED3_GPIO_CLK                   RCU_GPIOD
#define LED3_GPIO_PORT                  GPIOD
#define LED3_PIN                        GPIO_PIN_10

#define LED4_GPIO_CLK                   RCU_GPIOD
#define LED4_GPIO_PORT                  GPIOD
#define LED4_PIN                        GPIO_PIN_11

#define LED5_GPIO_CLK                   RCU_GPIOD
#define LED5_GPIO_PORT                  GPIOD
#define LED5_PIN                        GPIO_PIN_12

#define LED6_GPIO_CLK                   RCU_GPIOD
#define LED6_GPIO_PORT                  GPIOD
#define LED6_PIN                        GPIO_PIN_13

#define LED7_GPIO_CLK                   RCU_GPIOD
#define LED7_GPIO_PORT                  GPIOD
#define LED7_PIN                        GPIO_PIN_14

#define LED8_GPIO_CLK                   RCU_GPIOD
#define LED8_GPIO_PORT                  GPIOD
#define LED8_PIN                        GPIO_PIN_15



void leds_init();	

// 定义规则
void leds_on_all();
void leds_off_all();

void leds_on(uint8_t i);
void leds_off(uint8_t i);
void leds_turn(uint8_t i, uint8_t on);
void leds_toggle(uint8_t i);


#endif