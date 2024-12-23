#ifndef __LIB_TIMER9_H__
#define __LIB_TIMER9_H__

#include "Timer_config.h"

#if USE_LIB_TIMER_9

void lib_timer9_init();
void lib_timer9_update_period(uint16_t psc, uint16_t freq);

#if USE_LIB_TIMER9_CH0
void lib_timer9_ch0_update(float duty);
#endif //USE_LIB_TIMER9_CH0


#endif //USE_LIB_TIMER_9

#endif