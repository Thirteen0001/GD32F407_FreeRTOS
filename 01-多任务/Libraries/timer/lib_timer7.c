#include "lib_timer7.h"

#if USE_LIB_TIMER_7


#define __TIMERx				TIMER7
#define __TIMERx_RCU		RCU_TIMER7
#define __TIMERx_AF			GPIO_AF_3

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

static inline void timer_ch_duty(float duty, uint32_t timer, uint16_t chn) {
		duty = MIN(100, MAX(0, duty));
    uint32_t pulse = MAX(1, duty * period / 100.0);
	
    timer_channel_output_pulse_value_config(timer, chn, pulse - 1);
}

void lib_timer7_init() {
    /************* GPIO config **********/
    // CH 0
#if USE_LIB_TIMER7_CH0_P
    afio_cfg(__TIMERx_AF, TIMER7_CH0_P_GPIO_RCU, TIMER7_CH0_P_GPIO_PORT, TIMER7_CH0_P_GPIO_PIN);
#endif
#if USE_LIB_TIMER7_CH0_N
    afio_cfg(__TIMERx_AF, TIMER7_CH0_N_GPIO_RCU, TIMER7_CH0_N_GPIO_PORT, TIMER7_CH0_N_GPIO_PIN);
#endif
    // CH 1
#if USE_LIB_TIMER7_CH1_P
    afio_cfg(__TIMERx_AF, TIMER7_CH1_P_GPIO_RCU, TIMER7_CH1_P_GPIO_PORT, TIMER7_CH1_P_GPIO_PIN);
#endif
#if USE_LIB_TIMER7_CH1_N
    afio_cfg(__TIMERx_AF, TIMER7_CH1_N_GPIO_RCU, TIMER7_CH1_N_GPIO_PORT, TIMER7_CH1_N_GPIO_PIN);
#endif
    // CH 2
#if USE_LIB_TIMER7_CH2_P
    afio_cfg(__TIMERx_AF, TIMER7_CH2_P_GPIO_RCU, TIMER7_CH2_P_GPIO_PORT, TIMER7_CH2_P_GPIO_PIN);
#endif
#if USE_LIB_TIMER7_CH2_N
    afio_cfg(__TIMERx_AF, TIMER7_CH2_N_GPIO_RCU, TIMER7_CH2_N_GPIO_PORT, TIMER7_CH2_N_GPIO_PIN);
#endif
    // CH 3
#if USE_LIB_TIMER7_CH3
    afio_cfg(__TIMERx_AF, TIMER7_CH3_GPIO_RCU, TIMER7_CH3_GPIO_PORT, TIMER7_CH3_GPIO_PIN);
#endif

    /*************** Timer Config *******************/
    /// rcu
    rcu_periph_clock_enable(__TIMERx_RCU);
    timer_deinit(__TIMERx);
    /// timer init
    lib_timer7_update_period(TIMER7_PRESCALER, TIMER7_FREQ);
		
		
		///////////////////// CH out config /////////////
		timer_oc_parameter_struct ocpara;
		//////////// CH 0
#if USE_LIB_TIMER7_CH0_P || USE_LIB_TIMER7_CH0_N
    timer_channel_output_struct_para_init(&ocpara);
#if USE_LIB_TIMER7_CH0_P		
		// P打开
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
#endif
#if USE_LIB_TIMER7_CH0_N
		// N打开
    ocpara.outputnstate = TIMER_CCXN_ENABLE;
#endif	
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_0);
#endif

		//////////// CH 1
#if USE_LIB_TIMER7_CH1_P || USE_LIB_TIMER7_CH1_N
    timer_channel_output_struct_para_init(&ocpara);
#if USE_LIB_TIMER7_CH1_P		
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
#endif
#if USE_LIB_TIMER7_CH1_N
    ocpara.outputnstate = TIMER_CCXN_ENABLE;
#endif	
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_1);
#endif

		//////////// CH 2
#if USE_LIB_TIMER7_CH2_P || USE_LIB_TIMER7_CH2_N
    timer_channel_output_struct_para_init(&ocpara);
#if USE_LIB_TIMER7_CH2_P		
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
#endif
#if USE_LIB_TIMER7_CH2_N
    ocpara.outputnstate = TIMER_CCXN_ENABLE;
#endif	
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_2);
#endif

		//////////// CH 3
#if USE_LIB_TIMER7_CH3
    timer_channel_output_struct_para_init(&ocpara);
    ocpara.outputstate  = TIMER_CCX_ENABLE;		
		timer_ch_cfg(&ocpara, __TIMERx, TIMER_CH_3);
#endif

		////// 高级定时器单独配置
		timer_break_parameter_struct breakpara;
		timer_break_struct_para_init(&breakpara);	
    breakpara.breakpolarity   = TIMER_BREAK_POLARITY_HIGH;
    breakpara.outputautostate = TIMER_OUTAUTO_ENABLE;
    breakpara.breakstate      = TIMER_BREAK_ENABLE;
		timer_break_config(__TIMERx, &breakpara);
		timer_break_enable(__TIMERx);
		
    timer_enable(__TIMERx);
}

void lib_timer7_update_period(uint16_t psc, uint16_t freq) {
    period = (SystemCoreClock / (freq * psc));
    /// timer init
    timer_parameter_struct tps;
    timer_struct_para_init(&tps);		// 默认值
    tps.prescaler = psc - 1;				// 分频
    tps.period = period - 1;				// 周期
    timer_init(__TIMERx, &tps);
}

#if USE_LIB_TIMER7_CH0_P || USE_LIB_TIMER7_CH0_N
void lib_timer7_ch0_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_0);
}
#endif

#if USE_LIB_TIMER7_CH1_P || USE_LIB_TIMER7_CH1_N
void lib_timer7_ch1_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_1);
}
#endif

#if USE_LIB_TIMER7_CH2_P || USE_LIB_TIMER7_CH2_N
void lib_timer7_ch2_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_2);
}
#endif

#if USE_LIB_TIMER7_CH3
void lib_timer7_ch3_update(float duty) {
		timer_ch_duty(duty,__TIMERx, TIMER_CH_3);
}
#endif



#endif