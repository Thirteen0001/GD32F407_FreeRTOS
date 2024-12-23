#ifndef __LIB_TIMER3_H__
#define __LIB_TIMER3_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_3

void lib_timer3_init();
void lib_timer3_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER3_CH0
void lib_timer3_ch0_update(float duty);
#endif //USE_LIB_TIMER3_CH0

#if USE_LIB_TIMER3_CH1
void lib_timer3_ch1_update(float duty);
#endif // USE_LIB_TIMER3_CH1

#if USE_LIB_TIMER3_CH2
void lib_timer3_ch2_update(float duty);
#endif // USE_LIB_TIMER3_CH2

#if USE_LIB_TIMER3_CH3
void lib_timer3_ch3_update(float duty);
#endif // USE_LIB_TIMER3_CH3

#endif //USE_LIB_TIMER_3

#endif