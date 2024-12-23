#include "lib_exti.h"

static inline void EXTI_soft_config(exti_line_enum	extix, uint32_t extix_irq, uint8_t nvic_pre, uint8_t nvic_sub) {
    /************* Exti ****************/
    /// 初始化 syscfg
    /// rcu
    rcu_periph_clock_enable(RCU_SYSCFG);

    //// EXTI, 外部中断初始化完成
    exti_init(extix, EXTI_INTERRUPT, EXTI_TRIG_NONE);

    // 中断函数， 注册中断
    exti_interrupt_enable(extix);

    nvic_irq_enable(extix_irq, nvic_pre, nvic_sub);

}
static inline void EXTI_hard_config(uint32_t gpio_rcu, uint32_t gpio_port, uint32_t gpio_pin,
                                    uint8_t exti_port, uint8_t exti_pin,
                                    exti_line_enum	extix, uint32_t extix_irq, uint32_t gpio_pupd,
                                    exti_trig_type_enum trig,uint8_t nvic_pre,uint8_t nvic_sub) {

    // 特例，不需要AF
    /************* GPIO ****************/
    /// rcu
    rcu_periph_clock_enable(gpio_rcu);
    /// mode
    gpio_mode_set(gpio_port, GPIO_MODE_INPUT, gpio_pupd, gpio_pin);

    /************* Exti ****************/
    /// 初始化 syscfg
    /// rcu
    rcu_periph_clock_enable(RCU_SYSCFG);
    // 外部中断接管引脚
    syscfg_exti_line_config(exti_port, exti_pin);

    //// EXTI, 外部中断初始化完成
    exti_init(extix, EXTI_INTERRUPT, trig);

    // 中断函数， 注册中断
    exti_interrupt_enable(extix);

    nvic_irq_enable(extix_irq, nvic_pre, nvic_sub);
}

void lib_exti_init() {
#if USE_LIB_EXTI_0
#if EXTI0_SOFT_TRIG
    EXTI_soft_config(EXTI_0, EXTI0_IRQn, EXTI0_NVIC);
#else
    EXTI_hard_config(EXTI0_GPIO_RCU, EXTI0_GPIO_PORT, GPIO_PIN_0,
                     EXTI0_SRC, EXTI_SOURCE_PIN0, EXTI_0, EXTI0_IRQn,
                     EXTI0_GPIO_PUPD,EXTI0_TRIGGER,EXTI0_NVIC);
#endif
#endif

#if USE_LIB_EXTI_1
#if EXTI1_SOFT_TRIG
    EXTI_soft_config(EXTI_1, EXTI1_IRQn, EXTI1_NVIC);
#else
    EXTI_hard_config(EXTI1_GPIO_RCU, EXTI1_GPIO_PORT, GPIO_PIN_1,
                     EXTI1_SRC, EXTI_SOURCE_PIN1, EXTI_1, EXTI1_IRQn,
                     EXTI1_GPIO_PUPD,EXTI1_TRIGGER,EXTI1_NVIC);
#endif
#endif

#if USE_LIB_EXTI_2
#if EXTI2_SOFT_TRIG
    EXTI_soft_config(EXTI_2, EXTI2_IRQn, EXTI2_NVIC);
#else
    EXTI_hard_config(EXTI2_GPIO_RCU, EXTI2_GPIO_PORT, GPIO_PIN_2,
                     EXTI2_SRC, EXTI_SOURCE_PIN2, EXTI_2, EXTI2_IRQn,
                     EXTI2_GPIO_PUPD,EXTI2_TRIGGER,EXTI2_NVIC);
#endif
#endif

#if USE_LIB_EXTI_3
#if EXTI3_SOFT_TRIG
    EXTI_soft_config(EXTI_3, EXTI3_IRQn, EXTI3_NVIC);
#else
    EXTI_hard_config(EXTI3_GPIO_RCU, EXTI3_GPIO_PORT, GPIO_PIN_3,
                     EXTI3_SRC, EXTI_SOURCE_PIN3, EXTI_3, EXTI3_IRQn,
                     EXTI3_GPIO_PUPD,EXTI3_TRIGGER,EXTI3_NVIC);
#endif
#endif

#if USE_LIB_EXTI_4
#if EXTI4_SOFT_TRIG
    EXTI_soft_config(EXTI_4, EXTI4_IRQn, EXTI4_NVIC);
#else
    EXTI_hard_config(EXTI4_GPIO_RCU, EXTI4_GPIO_PORT, GPIO_PIN_4,
                     EXTI4_SRC, EXTI_SOURCE_PIN4, EXTI_4, EXTI4_IRQn,
                     EXTI4_GPIO_PUPD,EXTI4_TRIGGER,EXTI4_NVIC);
#endif
#endif


#if USE_LIB_EXTI_5
#if EXTI5_SOFT_TRIG
    EXTI_soft_config(EXTI_5, EXTI5_9_IRQn, EXTI5_NVIC);
#else
    EXTI_hard_config(EXTI5_GPIO_RCU, EXTI5_GPIO_PORT, GPIO_PIN_5,
                     EXTI5_SRC, EXTI_SOURCE_PIN5, EXTI_5, EXTI5_9_IRQn,
                     EXTI5_GPIO_PUPD,EXTI5_TRIGGER,EXTI5_NVIC);
#endif
#endif


#if USE_LIB_EXTI_6
#if EXTI6_SOFT_TRIG
    EXTI_soft_config(EXTI_6, EXTI5_9_IRQn, EXTI6_NVIC);
#else
    EXTI_hard_config(EXTI6_GPIO_RCU, EXTI6_GPIO_PORT, GPIO_PIN_6,
                     EXTI6_SRC, EXTI_SOURCE_PIN6, EXTI_6, EXTI5_9_IRQn,
                     EXTI6_GPIO_PUPD,EXTI6_TRIGGER,EXTI6_NVIC);
#endif
#endif


#if USE_LIB_EXTI_7
#if EXTI7_SOFT_TRIG
    EXTI_soft_config(EXTI_7, EXTI5_9_IRQn, EXTI6_NVIC);
#else
    EXTI_hard_config(EXTI7_GPIO_RCU, EXTI7_GPIO_PORT, GPIO_PIN_7,
                     EXTI7_SRC, EXTI_SOURCE_PIN7, EXTI_7, EXTI5_9_IRQn,
                     EXTI7_GPIO_PUPD,EXTI7_TRIGGER,EXTI7_NVIC);
#endif
#endif


#if USE_LIB_EXTI_8
#if EXTI8_SOFT_TRIG
    EXTI_soft_config(EXTI_8, EXTI5_9_IRQn, EXTI8_NVIC);
#else
    EXTI_hard_config(EXTI8_GPIO_RCU, EXTI8_GPIO_PORT, GPIO_PIN_8,
                     EXTI8_SRC, EXTI_SOURCE_PIN8, EXTI_8, EXTI5_9_IRQn,
                     EXTI8_GPIO_PUPD,EXTI8_TRIGGER,EXTI8_NVIC);
#endif
#endif


#if USE_LIB_EXTI_9
#if EXTI9_SOFT_TRIG
    EXTI_soft_config(EXTI_9, EXTI5_9_IRQn, EXTI9_NVIC);
#else
    EXTI_hard_config(EXTI9_GPIO_RCU, EXTI9_GPIO_PORT, GPIO_PIN_9,
                     EXTI9_SRC, EXTI_SOURCE_PIN9, EXTI_9, EXTI5_9_IRQn,
                     EXTI9_GPIO_PUPD,EXTI9_TRIGGER,EXTI9_NVIC);
#endif
#endif


#if USE_LIB_EXTI_10
#if EXTI10_SOFT_TRIG
    EXTI_soft_config(EXTI_10, EXTI10_15_IRQn, EXTI10_NVIC);
#else
    EXTI_hard_config(EXTI10_GPIO_RCU, EXTI10_GPIO_PORT, GPIO_PIN_10,
                     EXTI10_SRC, EXTI_SOURCE_PIN10, EXTI_10, EXTI10_15_IRQn,
                     EXTI10_GPIO_PUPD,EXTI10_TRIGGER,EXTI10_NVIC);
#endif
#endif


#if USE_LIB_EXTI_11
#if EXTI11_SOFT_TRIG
    EXTI_soft_config(EXTI_11, EXTI10_15_IRQn, EXTI11_NVIC);
#else
    EXTI_hard_config(EXTI11_GPIO_RCU, EXTI11_GPIO_PORT, GPIO_PIN_11,
                     EXTI11_SRC, EXTI_SOURCE_PIN11, EXTI_11, EXTI10_15_IRQn,
                     EXTI11_GPIO_PUPD,EXTI11_TRIGGER,EXTI11_NVIC);
#endif
#endif


#if USE_LIB_EXTI_12
#if EXTI12_SOFT_TRIG
    EXTI_soft_config(EXTI_12, EXTI10_15_IRQn, EXTI12_NVIC);
#else
    EXTI_hard_config(EXTI12_GPIO_RCU, EXTI12_GPIO_PORT, GPIO_PIN_12,
                     EXTI12_SRC, EXTI_SOURCE_PIN12, EXTI_12, EXTI10_15_IRQn,
                     EXTI12_GPIO_PUPD,EXTI12_TRIGGER,EXTI12_NVIC);
#endif
#endif


#if USE_LIB_EXTI_13
#if EXTI13_SOFT_TRIG
    EXTI_soft_config(EXTI_13, EXTI10_15_IRQn, EXTI13_NVIC);
#else
    EXTI_hard_config(EXTI13_GPIO_RCU, EXTI13_GPIO_PORT, GPIO_PIN_13,
                     EXTI13_SRC, EXTI_SOURCE_PIN13, EXTI_13, EXTI10_15_IRQn,
                     EXTI13_GPIO_PUPD,EXTI13_TRIGGER,EXTI13_NVIC);
#endif
#endif


#if USE_LIB_EXTI_14
#if EXTI14_SOFT_TRIG
    EXTI_soft_config(EXTI_14, EXTI10_15_IRQn, EXTI14_NVIC);
#else
    EXTI_hard_config(EXTI14_GPIO_RCU, EXTI14_GPIO_PORT, GPIO_PIN_14,
                     EXTI14_SRC, EXTI_SOURCE_PIN14, EXTI_14, EXTI10_15_IRQn,
                     EXTI14_GPIO_PUPD,EXTI14_TRIGGER,EXTI14_NVIC);
#endif
#endif


#if USE_LIB_EXTI_15
#if EXTI15_SOFT_TRIG
    EXTI_soft_config(EXTI_15, EXTI10_15_IRQn, EXTI15_NVIC);
#else
    EXTI_hard_config(EXTI15_GPIO_RCU, EXTI15_GPIO_PORT, GPIO_PIN_15,
                     EXTI15_SRC, EXTI_SOURCE_PIN15, EXTI_15, EXTI10_15_IRQn,
                     EXTI15_GPIO_PUPD,EXTI15_TRIGGER,EXTI15_NVIC);
#endif
#endif


}

#if USE_LIB_EXTI_0
void EXTI0_IRQHandler(void) {
    if(SET == exti_interrupt_flag_get(EXTI_0)) {
        exti_interrupt_flag_clear(EXTI_0);
        lib_exti0_on_trig();
    }
}

#if EXTI0_SOFT_TRIG
void lib_exti0_soft_trig() {
    exti_software_interrupt_enable(EXTI_0);
}
#endif
#endif


#if USE_LIB_EXTI_1
void EXTI1_IRQHandler(void) {
    if(SET == exti_interrupt_flag_get(EXTI_1)) {
        exti_interrupt_flag_clear(EXTI_1);
        lib_exti1_on_trig();
    }
}

#if EXTI1_SOFT_TRIG
void lib_exti1_soft_trig() {
    exti_software_interrupt_enable(EXTI_1);
}
#endif
#endif


#if USE_LIB_EXTI_2
void EXTI2_IRQHandler(void) {
    if(SET == exti_interrupt_flag_get(EXTI_2)) {
        exti_interrupt_flag_clear(EXTI_2);
        lib_exti2_on_trig();

    }
}

#if EXTI2_SOFT_TRIG
void lib_exti2_soft_trig() {
    exti_software_interrupt_enable(EXTI_2);
}
#endif
#endif


#if USE_LIB_EXTI_3
void EXTI3_IRQHandler(void) {
    if(SET == exti_interrupt_flag_get(EXTI_3)) {
        exti_interrupt_flag_clear(EXTI_3);
        lib_exti3_on_trig();

    }
}

#if EXTI3_SOFT_TRIG
void lib_exti3_soft_trig() {
    exti_software_interrupt_enable(EXTI_3);
}
#endif
#endif


#if USE_LIB_EXTI_4
void EXTI4_IRQHandler(void) {
    if(SET == exti_interrupt_flag_get(EXTI_4)) {
        exti_interrupt_flag_clear(EXTI_4);
        lib_exti4_on_trig();

    }
}

#if EXTI4_SOFT_TRIG
void lib_exti4_soft_trig() {
    exti_software_interrupt_enable(EXTI_4);
}
#endif
#endif



#if USE_LIB_EXTI_5 || USE_LIB_EXTI_6 || USE_LIB_EXTI_7 || USE_LIB_EXTI_8 || USE_LIB_EXTI_9
void EXTI5_9_IRQHandler(void) {
#if USE_LIB_EXTI_5
    if(SET == exti_interrupt_flag_get(EXTI_5)) {
        exti_interrupt_flag_clear(EXTI_5);
        lib_exti5_on_trig();
    }
#endif
#if USE_LIB_EXTI_6
    if(SET == exti_interrupt_flag_get(EXTI_6)) {
        exti_interrupt_flag_clear(EXTI_6);
        lib_exti6_on_trig();
    }
#endif
#if USE_LIB_EXTI_7
    if(SET == exti_interrupt_flag_get(EXTI_7)) {
        exti_interrupt_flag_clear(EXTI_7);
        lib_exti7_on_trig();

    }
#endif
#if USE_LIB_EXTI_8
    if(SET == exti_interrupt_flag_get(EXTI_8)) {
        exti_interrupt_flag_clear(EXTI_8);
        lib_exti8_on_trig();

    }
#endif
#if USE_LIB_EXTI_9
    if(SET == exti_interrupt_flag_get(EXTI_9)) {
        exti_interrupt_flag_clear(EXTI_9);
        lib_exti9_on_trig();

    }
#endif
}

#if EXTI5_SOFT_TRIG
void lib_exti5_soft_trig() {
    exti_software_interrupt_enable(EXTI_5);
}
#endif

#if EXTI6_SOFT_TRIG
void lib_exti6_soft_trig() {
    exti_software_interrupt_enable(EXTI_6);
}
#endif

#if EXTI7_SOFT_TRIG
void lib_exti7_soft_trig() {
    exti_software_interrupt_enable(EXTI_7);
}
#endif

#if EXTI8_SOFT_TRIG
void lib_exti8_soft_trig() {
    exti_software_interrupt_enable(EXTI_8);
}
#endif

#if EXTI9_SOFT_TRIG
void lib_exti9_soft_trig() {
    exti_software_interrupt_enable(EXTI_9);
}
#endif
#endif



#if USE_LIB_EXTI_10 || USE_LIB_EXTI_11 || USE_LIB_EXTI_12 || USE_LIB_EXTI_13 || USE_LIB_EXTI_14 || USE_LIB_EXTI_15
void EXTI10_15_IRQHandler(void) {
#if USE_LIB_EXTI_10
    if(SET == exti_interrupt_flag_get(EXTI_10)) {
        exti_interrupt_flag_clear(EXTI_10);
        lib_exti10_on_trig();
    }
#endif
#if USE_LIB_EXTI_11
    if(SET == exti_interrupt_flag_get(EXTI_11)) {
        exti_interrupt_flag_clear(EXTI_11);
        lib_exti11_on_trig();
    }
#endif
#if USE_LIB_EXTI_12
    if(SET == exti_interrupt_flag_get(EXTI_12)) {
        exti_interrupt_flag_clear(EXTI_12);
        lib_exti12_on_trig();

    }
#endif
#if USE_LIB_EXTI_13
    if(SET == exti_interrupt_flag_get(EXTI_13)) {
        exti_interrupt_flag_clear(EXTI_13);
        lib_exti13_on_trig();

    }
#endif
#if USE_LIB_EXTI_14
    if(SET == exti_interrupt_flag_get(EXTI_14)) {
        exti_interrupt_flag_clear(EXTI_14);
        lib_exti14_on_trig();

    }
#endif
#if USE_LIB_EXTI_15
    if(SET == exti_interrupt_flag_get(EXTI_15)) {
        exti_interrupt_flag_clear(EXTI_15);
        lib_exti15_on_trig();

    }
#endif
}

#if EXTI10_SOFT_TRIG
void lib_exti10_soft_trig() {
    exti_software_interrupt_enable(EXTI_10);
}
#endif

#if EXTI11_SOFT_TRIG
void lib_exti11_soft_trig() {
    exti_software_interrupt_enable(EXTI_11);
}
#endif

#if EXTI12_SOFT_TRIG
void lib_exti12_soft_trig() {
    exti_software_interrupt_enable(EXTI_12);
}
#endif

#if EXTI13_SOFT_TRIG
void lib_exti13_soft_trig() {
    exti_software_interrupt_enable(EXTI_13);
}
#endif

#if EXTI14_SOFT_TRIG
void lib_exti14_soft_trig() {
    exti_software_interrupt_enable(EXTI_14);
}
#endif

#if EXTI15_SOFT_TRIG
void lib_exti15_soft_trig() {
    exti_software_interrupt_enable(EXTI_15);
}
#endif
#endif
