#ifndef __LIB_ADC0_H__
#define __LIB_ADC0_H__


#include "ADC_config.h"

#if USE_LIB_ADC0


void lib_adc0_init();


uint16_t lib_adc0_get(uint8_t index);


#endif // USE_ADC0


#endif //__ADC0_H__
