#include "bsp_keys.h"


static inline void gpio_cfg(uint32_t rcc, uint32_t port, uint32_t pin) {
    rcu_periph_clock_enable(rcc);
    gpio_mode_set(port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, pin);
}



void keys_init() {
    gpio_cfg(KEY1_RCC, KEY1_PIN);
    gpio_cfg(KEY2_RCC, KEY2_PIN);
    gpio_cfg(KEY3_RCC, KEY3_PIN);
    gpio_cfg(KEY4_RCC, KEY4_PIN);
}


void keys_scan() {
    static FlagStatus last0 = SET, last1 = SET, last2 = SET, last3 = SET;//原理图

    // 读取引脚的输入状态
    FlagStatus state0 = gpio_input_bit_get(KEY1_PIN);

    if(SET == state0 && RESET == last0) {
        last0 = state0;
        // 当前是高，上一次是低，抬起

        keys_on_up(0);
    } else if(RESET == state0 && SET == last0) {
        last0 = state0;
        // 当前是低，上一次是高，按下
        keys_on_down(0);
    }

    FlagStatus state1 = gpio_input_bit_get(KEY2_PIN);

    if(SET == state1 && RESET == last1) {
        last1 = state1;
        // 当前是高，上一次是低，抬起

        keys_on_up(1);
    } else if(RESET == state1 && SET == last1) {
        last1 = state1;
        // 当前是低，上一次是高，按下
        keys_on_down(1);
    }


    FlagStatus state2 = gpio_input_bit_get(KEY3_PIN);

    if(SET == state2 && RESET == last2) {
        last2 = state2;
        // 当前是高，上一次是低，抬起

        keys_on_up(2);
    } else if(RESET == state2 && SET == last2) {
        last2 = state2;
        // 当前是低，上一次是高，按下
        keys_on_down(2);
    }


    FlagStatus state3 = gpio_input_bit_get(KEY4_PIN);

    if(SET == state3 && RESET == last3) {
        last3 = state3;
        // 当前是高，上一次是低，抬起

        keys_on_up(3);
    } else if(RESET == state3 && SET == last3) {
        last3 = state3;
        // 当前是低，上一次是高，按下
        keys_on_down(3);
    }
}