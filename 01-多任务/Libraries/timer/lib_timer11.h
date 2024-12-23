#ifndef __LIB_TIMER11_H__
#define __LIB_TIMER11_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_11

void lib_timer11_init();
void lib_timer11_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER11_CH0
void lib_timer11_ch0_update(float duty);
#endif //USE_LIB_TIMER11_CH0

#if USE_LIB_TIMER11_CH1
void lib_timer11_ch1_update(float duty);
#endif // USE_LIB_TIMER11_CH1


#endif //USE_LIB_TIMER_11

#endif