#include "lib_timer6.h"


#if USE_LIB_TIMER_6

#define __TIMERx				TIMER6
#define __TIMERx_RCU		RCU_TIMER6
#define __TIMERx_IRQn		TIMER6_IRQn

static uint16_t period = 0;

void lib_timer6_init() {
	
    /*************** Timer Config *******************/
    /// rcu
    rcu_periph_clock_enable(__TIMERx_RCU);
    timer_deinit(__TIMERx);
    /// timer init
    lib_timer6_update_period(TIMER6_PRESCALER, TIMER6_FREQ);
	
	/******************* INT config *******************/
	nvic_irq_enable(__TIMERx_IRQn, TIMER6_NVIC);
    timer_interrupt_enable(__TIMERx, TIMER_INT_UP);

    // ʹ��timer
    timer_enable(__TIMERx);
}

void lib_timer6_update_period(uint16_t psc, uint16_t freq) {
    period = (SystemCoreClock / (freq * psc));
    /// timer init
    timer_parameter_struct tps;
    timer_struct_para_init(&tps);		// Ĭ��ֵ
    tps.prescaler = psc - 1;				// ��Ƶ
    tps.period = period - 1;				// ����
    timer_init(__TIMERx, &tps);
}

#if TIMER6_INT_CALLBACK
void TIMER6_IRQHandler(void) {
    if(SET == timer_interrupt_flag_get(__TIMERx, TIMER_INT_UP)) {
				lib_timer6_on_interrupt();
    }
    //����жϱ�־λ
    timer_interrupt_flag_clear(__TIMERx, TIMER_INT_FLAG_UP);
}

#endif

#endif