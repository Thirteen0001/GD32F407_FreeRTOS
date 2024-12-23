#ifndef __LIB_TIMER4_H__
#define __LIB_TIMER4_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_4

void lib_timer4_init();
void lib_timer4_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER4_CH0
void lib_timer4_ch0_update(float duty);
#endif //USE_LIB_TIMER4_CH0

#if USE_LIB_TIMER4_CH1
void lib_timer4_ch1_update(float duty);
#endif // USE_LIB_TIMER4_CH1

#if USE_LIB_TIMER4_CH2
void lib_timer4_ch2_update(float duty);
#endif // USE_LIB_TIMER4_CH2

#if USE_LIB_TIMER4_CH3
void lib_timer4_ch3_update(float duty);
#endif // USE_LIB_TIMER4_CH3

#endif //USE_LIB_TIMER_4

#endif