#include "lib_timer1.h"

#if USE_LIB_TIMER_1


#define __TIMERx				TIMER1
#define __TIMERx_RCU		RCU_TIMER1
#define __TIMERx_AF			GPIO_AF_1

#define MIN(a, b)  ((a) > (b) ? (b) : (a))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))

static uint16_t period = 0;

static inline void afio_cfg(uint32_t af, uint32_t rcu, uint32_t port, uint32_t pin) {
    rcu_periph_clock_enable(rcu);
    gpio_mode_set(port, GPIO_MODE_AF, GPIO_PUPD_NONE, pin);
		gpio_output_options_set(port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, pin);
    gpio_af_set(port, af, pin);
}

static inline void timer_ch_cfg(timer_oc_parameter_struct *ocpara, uint32_t timer, uint16_t chn) {
		timer_channel_output_config(timer, chn, ocpara);
    timer_channel_output_mode_config(timer, chn, TIMER_OC_MODE_PWM0);
    timer_channel_output_pulse_value_config(timer, chn, 0);
}

void lib_timer1_init() {
    /************* GPIO config **********/
    // CH 0
#if USE_LIB_TIMER1_CH0
    afio_cfg(__TIMERx_AF, TIMER1_CH0_GPIO_RCU, TIMER1_CH0_GPIO_PORT, TIMER1_CH0_GPIO_PIN);
#endif
    // CH 1
#if USE_LIB_TIMER1_CH1
    afio_cfg(__TIMERx_AF, TIMER1_CH1_GPIO_RCU, TIMER1_CH1_GPIO_PORT, TIMER1_CH1_GPIO_PIN);
#endif
    // CH 2
#if USE_LIB_TIMER1_CH2
    afio_cfg(__TIMERx_AF, TIMER1_CH2_GPIO_RCU, TIMER1_CH2_GPIO_PORT, TIMER1_CH2_GPIO_PIN);
#endif
    // CH 3
#if USE_LIB_TIMER1_CH3
    afio_cfg(__TIMERx_AF, TIMER1_CH3_GPIO_RCU, TIMER1_CH3_GPIO_PORT, TIMER1_CH3_GPIO_PIN);
#endif

    /*************** Timer Config *******************/
    /// rcu
    rcu_periph_clock_enable(__TIMERx_RCU);
    timer_deinit(__TIMERx);
    /// timer init
    lib_timer1_update_period(TIMER1_PRESCALER, TIMER1_FREQ);
		
		
		///////////////////// CH out config /////////////
		timer_oc_parameter_struct ocpara;
		//////////// CH 0
#if USE_LIB_TIMER1_CH0
    timer_channel_output_struct_para_init(&ocpara);		
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_0);
#endif

		//////////// CH 1
#if USE_LIB_TIMER1_CH1
    timer_channel_output_struct_para_init(&ocpara);
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_1);
#endif

		//////////// CH 2
#if USE_LIB_TIMER1_CH2
    timer_channel_output_struct_para_init(&ocpara);		
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_2);
#endif

		//////////// CH 3
#if USE_LIB_TIMER1_CH3
    timer_channel_output_struct_para_init(&ocpara);
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_3);
#endif

    timer_enable(__TIMERx);
}

void lib_timer1_update_period(uint16_t psc, uint16_t freq) {
    period = (SystemCoreClock / (freq * psc));
    /// timer init
    timer_parameter_struct tps;
    timer_struct_para_init(&tps);		// 默认值
    tps.prescaler = psc - 1;				// 分频
    tps.period = period - 1;				// 周期
    timer_init(__TIMERx, &tps);
}

static inline void timer_ch_duty(float duty, uint32_t timer, uint16_t chn) {
		duty = MIN(100, MAX(0, duty));
    uint32_t pulse = MAX(1, duty * (period + 1) / 100.0);
    timer_channel_output_pulse_value_config(timer, chn, pulse - 1);
}

#if USE_LIB_TIMER1_CH0
void lib_timer1_ch0_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_0);
}
#endif

#if USE_LIB_TIMER1_CH1
void lib_timer1_ch1_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_1);
}
#endif

#if USE_LIB_TIMER1_CH2
void lib_timer1_ch2_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_2);
}
#endif

#if USE_LIB_TIMER1_CH3
void lib_timer1_ch3_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_3);
}
#endif



#endif