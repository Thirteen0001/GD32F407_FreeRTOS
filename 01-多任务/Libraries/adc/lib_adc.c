#include "lib_adc.h"


void lib_adc_init() {
	 // ����
    adc_deinit();
    // ������Ƶ
    adc_clock_config(ADC_CLK);// Ck_ADC 10.5MHZ, �����1�����ĵ�ʱ�� 1s/21MHZ
	
#if USE_LIB_ADC0
	lib_adc0_init();
#endif
}