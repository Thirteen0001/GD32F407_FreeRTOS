#ifndef __LIB_TIMER13_H__
#define __LIB_TIMER13_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_13

void lib_timer13_init();
void lib_timer13_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER13_CH0
void lib_timer13_ch0_update(float duty);
#endif //USE_LIB_TIMER13_CH0


#endif //USE_LIB_TIMER_13

#endif