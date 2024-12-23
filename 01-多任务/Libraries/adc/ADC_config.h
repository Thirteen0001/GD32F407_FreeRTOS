#ifndef __ADC_CONF_H__
#define __ADC_CONF_H__

#include "gd32f4xx.h"
#include "systick.h"



#define USE_LIB_ADC0	1



#define ADC_CLK		ADC_ADCCK_PCLK2_DIV8

/**************** ADC 0 *****************/
#if USE_LIB_ADC0

#define	ADC0_RESOLUTION 	ADC_RESOLUTION_12B


#define ADC0_CHNS_LEN		1
#define ADC0_CHNS			{	\
								ADC_CHANNEL_2,		\
							}

#define ADC0_CHNS_SAMPLES	{	\
								ADC_SAMPLETIME_480,	\
							}

														



#endif




#endif