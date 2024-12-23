#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__


#include "gd32f4xx.h"
#include <stdio.h>
#include "systick.h"

#include "lib_adc.h"
#include "lib_spi.h"
#include "lib_i2c.h"


#define CURRENT_TICK_MS()	(get_current_tick_us() / 1000)


////////////////////////// LED 188 模块 ///////////////////
#define PIN1_RCU	RCU_GPIOE
#define PIN1_PIN	GPIOE, GPIO_PIN_7

#define PIN2_RCU	RCU_GPIOE
#define PIN2_PIN	GPIOE, GPIO_PIN_9

#define PIN3_RCU	RCU_GPIOE
#define PIN3_PIN	GPIOE, GPIO_PIN_11

#define PIN4_RCU	RCU_GPIOE
#define PIN4_PIN	GPIOE, GPIO_PIN_13

#define PIN5_RCU	RCU_GPIOE
#define PIN5_PIN	GPIOE, GPIO_PIN_15



////////////////////////// ADKey 模块 ///////////////////
//// ADC0 IN2
#define ADKEY_RCU	RCU_GPIOA
#define ADKEY_PIN	GPIOA, GPIO_PIN_2


////////////////////////// EC12 模块 ///////////////////
//// 中断实现 D ，轻触按键 EXTI 15
//// 中断实现 A ， EXTI 11， 下降沿
#define EC12_DELAY	5

#define EC12_A_RCU			RCU_GPIOD
#define EC12_A_PIN			GPIOD, GPIO_PIN_11
#define EC12_A_EXTI_FUNC 	lib_exti11_on_trig
#define EC12_A_STATE()		gpio_input_bit_get(EC12_A_PIN)

#define EC12_B_RCU	RCU_GPIOD
#define EC12_B_PIN	GPIOD, GPIO_PIN_13
#define EC12_B_STATE()		gpio_input_bit_get(EC12_B_PIN)

#define EC12_D_RCU			RCU_GPIOD
#define EC12_D_PIN			GPIOD, GPIO_PIN_15
#define EC12_D_EXTI_FUNC 	lib_exti15_on_trig
#define EC12_D_STATE()		gpio_input_bit_get(EC12_D_PIN)


//////////////////////////////// WS2812
#define WS2812_NUM		4



/////////////////////////////// touch key
// i2c scl PB6
// i2c sda PB7
// EXTI 8  PB8


//////////////////////////////// Dot matrix 
#define DM_NUM				2

#define DM_CS_RCU			RCU_GPIOA
#define DM_CS_PIN			GPIOA, GPIO_PIN_4
#define DM_CS(val)			gpio_bit_write(DM_CS_PIN, (val) ? SET : RESET)

#define DM_WR(dat)			lib_spi2_write(dat)




























static inline void bsp_gpio_in(uint32_t rcu, uint32_t port, uint32_t pin) {
	rcu_periph_clock_enable(rcu);
	gpio_mode_set(port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, pin);
}

static inline void bsp_gpio_out(uint32_t rcu, uint32_t port, uint32_t pin) {
	rcu_periph_clock_enable(rcu);
	gpio_mode_set(port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
	gpio_output_options_set(port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, pin);
}

static inline void bsp_gpio_write(uint32_t port, uint32_t pin, uint8_t val) {
	gpio_bit_write(port, pin, (val) ? SET : RESET);
}


static inline void bsp_gpio_adc(uint32_t rcu, uint32_t port, uint32_t pin) {
	// 1. 时钟初始化
    rcu_periph_clock_enable(rcu);
    // 2. 配置GPIO 输入输出模式
    gpio_mode_set(port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, pin);
}


#endif