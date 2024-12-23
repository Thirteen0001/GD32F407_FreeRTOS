#ifndef __LIB_TIMER8_H__
#define __LIB_TIMER8_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_8

void lib_timer8_init();
void lib_timer8_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER8_CH0
void lib_timer8_ch0_update(float duty);
#endif //USE_LIB_TIMER8_CH0

#if USE_LIB_TIMER8_CH1
void lib_timer8_ch1_update(float duty);
#endif // USE_LIB_TIMER8_CH1


#endif //USE_LIB_TIMER_8

#endif