#include "lib_timer.h"


void lib_timer_init() {
		rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
#if USE_LIB_TIMER_0
		lib_timer0_init();
#endif

#if USE_LIB_TIMER_1
		lib_timer1_init();
#endif

#if USE_LIB_TIMER_2
		lib_timer2_init();
#endif

#if USE_LIB_TIMER_3
		lib_timer3_init();
#endif

#if USE_LIB_TIMER_4
		lib_timer4_init();
#endif

#if USE_LIB_TIMER_5
		lib_timer5_init();
#endif

#if USE_LIB_TIMER_6
		lib_timer6_init();
#endif

#if USE_LIB_TIMER_7
		lib_timer7_init();
#endif

#if USE_LIB_TIMER_8
		lib_timer8_init();
#endif

#if USE_LIB_TIMER_9
		lib_timer9_init();
#endif

#if USE_LIB_TIMER_10
		lib_timer10_init();
#endif

#if USE_LIB_TIMER_11
		lib_timer11_init();
#endif

#if USE_LIB_TIMER_12
		lib_timer12_init();
#endif

#if USE_LIB_TIMER_13
		lib_timer13_init();
#endif
}
