#include "bsp_leds.h"


// 连续内存空间，数组
typedef struct {
		rcu_periph_enum rcu;
		uint32_t port;
		uint32_t pin;
} led_gpio_t;

static led_gpio_t leds[LEDn] = {
		{LED1_GPIO_CLK, LED1_GPIO_PORT, LED1_PIN},
		{LED2_GPIO_CLK, LED2_GPIO_PORT, LED2_PIN},
		{LED3_GPIO_CLK, LED3_GPIO_PORT, LED3_PIN},	
		{LED4_GPIO_CLK, LED4_GPIO_PORT, LED4_PIN},
		{LED5_GPIO_CLK, LED5_GPIO_PORT, LED5_PIN},
		{LED6_GPIO_CLK, LED6_GPIO_PORT, LED6_PIN},
		{LED7_GPIO_CLK, LED7_GPIO_PORT, LED7_PIN},
		{LED8_GPIO_CLK, LED8_GPIO_PORT, LED8_PIN},
};
static led_gpio_t ledsw = {LEDSW_GPIO_CLK, LEDSW_GPIO_PORT, LEDSW_PIN};


static inline void gpio_cfg(led_gpio_t led) {
		rcu_periph_clock_enable(led.rcu);
		gpio_mode_set(led.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, led.pin);
    gpio_output_options_set(led.port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, led.pin);
}



void leds_init() {
    // sw
    gpio_cfg(ledsw);

    // led1 - led4
		//	gpio_cfg(RCU_GPIOD, GPIOD,  GPIO_PIN_8 | GPIO_PIN_9  | GPIO_PIN_10  | GPIO_PIN_11);// 缺乏通用性
		for(uint8_t i = 0; i < LEDn; i++) {
				gpio_cfg(leds[i]);
		}

		gpio_bit_reset(ledsw.port, ledsw.pin);
		leds_off_all();
}

void leds_on_all() {
		for(uint8_t i = 0; i < LEDn; i++) {
				leds_on(i);
		}
}

void leds_off_all() {
    for(uint8_t i = 0; i < LEDn; i++) {
				leds_off(i);
		}
}

void leds_on(uint8_t i) {

		gpio_bit_reset(leds[i].port, leds[i].pin);
}
void leds_off(uint8_t i) {

			gpio_bit_set(leds[i].port, leds[i].pin);
}

void leds_turn(uint8_t i, uint8_t on) {
		if(on) {
			leds_on(i);
		} else {
			leds_off(i);
		}
}


void leds_toggle(uint8_t i) {
		gpio_bit_toggle(leds[i].port, leds[i].pin);
}