#include "lib_adc.h"


void lib_adc_init() {
	 // 重置
    adc_deinit();
    // 配置主频
    adc_clock_config(ADC_CLK);// Ck_ADC 10.5MHZ, 计算出1次消耗的时长 1s/21MHZ
	
#if USE_LIB_ADC0
	lib_adc0_init();
#endif
}