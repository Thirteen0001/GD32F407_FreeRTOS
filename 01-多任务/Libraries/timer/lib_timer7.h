#ifndef __LIB_TIMER7_H__
#define __LIB_TIMER7_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_7

void lib_timer7_init();
void lib_timer7_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER7_CH0_P || USE_LIB_TIMER7_CH0_N
void lib_timer7_ch0_update(float duty);
#endif //USE_LIB_TIMER7_CH0

#if USE_LIB_TIMER7_CH1_P || USE_LIB_TIMER7_CH1_N
void lib_timer7_ch1_update(float duty);
#endif // USE_LIB_TIMER7_CH1

#if USE_LIB_TIMER7_CH2_P || USE_LIB_TIMER7_CH2_N
void lib_timer7_ch2_update(float duty);
#endif // USE_LIB_TIMER7_CH2

#if USE_LIB_TIMER7_CH3
void lib_timer7_ch3_update(float duty);
#endif // USE_LIB_TIMER7_CH3

#endif //USE_LIB_TIMER0

#endif // __TIMER7_H__