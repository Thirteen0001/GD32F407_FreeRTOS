#ifndef __LIB_TIMER1_H__
#define __LIB_TIMER1_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_1

void lib_timer1_init();
void lib_timer1_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER1_CH0
void lib_timer1_ch0_update(float duty);
#endif //USE_LIB_TIMER1_CH0

#if USE_LIB_TIMER1_CH1
void lib_timer1_ch1_update(float duty);
#endif // USE_LIB_TIMER1_CH1

#if USE_LIB_TIMER1_CH2
void lib_timer1_ch2_update(float duty);
#endif // USE_LIB_TIMER1_CH2

#if USE_LIB_TIMER1_CH3
void lib_timer1_ch3_update(float duty);
#endif // USE_LIB_TIMER1_CH3

#endif //USE_LIB_TIMER_1

#endif // __TIMER1_H__