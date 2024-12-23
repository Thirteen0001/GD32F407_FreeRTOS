#ifndef __LIB_TIMER2_H__
#define __LIB_TIMER2_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_2

void lib_timer2_init();
void lib_timer2_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER2_CH0
void lib_timer2_ch0_update(float duty);
#endif //USE_LIB_TIMER2_CH0

#if USE_LIB_TIMER2_CH1
void lib_timer2_ch1_update(float duty);
#endif // USE_LIB_TIMER2_CH1

#if USE_LIB_TIMER2_CH2
void lib_timer2_ch2_update(float duty);
#endif // USE_LIB_TIMER2_CH2

#if USE_LIB_TIMER2_CH3
void lib_timer2_ch3_update(float duty);
#endif // USE_LIB_TIMER2_CH3

#endif //USE_LIB_TIMER

#endif