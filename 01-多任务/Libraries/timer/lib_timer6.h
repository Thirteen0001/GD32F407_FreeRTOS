#ifndef __LIB_TIMER6_H__
#define __LIB_TIMER6_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_6

void lib_timer6_init();
void lib_timer6_update_period(uint16_t psc, uint16_t freq);


#if TIMER6_INT_CALLBACK
extern void lib_timer6_on_interrupt();
#endif

#endif

#endif