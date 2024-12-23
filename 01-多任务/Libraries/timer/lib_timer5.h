#ifndef __LIB_TIMER5_H__
#define __LIB_TIMER5_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_5

void lib_timer5_init();
void lib_timer5_update_period(uint16_t psc, uint16_t freq);


#if TIMER5_INT_CALLBACK
void lib_timer5_on_interrupt();
#endif

#endif

#endif