#ifndef __LIB_TIMER10_H__
#define __LIB_TIMER10_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_10

void lib_timer10_init();
void lib_timer10_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER10_CH0
void lib_timer10_ch0_update(float duty);
#endif //USE_LIB_TIMER10_CH0


#endif //USE_LIB_TIMER_10

#endif