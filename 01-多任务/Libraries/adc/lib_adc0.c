#include "lib_adc0.h"


#if USE_LIB_ADC0


static uint16_t buff[ADC0_CHNS_LEN] = {0};
static uint8_t	adc_chns[ADC0_CHNS_LEN] = ADC0_CHNS;
static uint32_t adc_chns_samples[ADC0_CHNS_LEN] = ADC0_CHNS_SAMPLES;

#define CH0_PIN	 RCU_GPIOA,GPIOA,GPIO_PIN_0
#define CH1_PIN	 RCU_GPIOA,GPIOA,GPIO_PIN_1
#define CH2_PIN	 RCU_GPIOA,GPIOA,GPIO_PIN_2
#define CH3_PIN	 RCU_GPIOA,GPIOA,GPIO_PIN_3

static void DMA_config() {
    uint32_t dmax = DMA1;
    uint32_t dmax_rcu = RCU_DMA1;
    uint32_t dmax_ch = DMA_CH0;
    uint32_t damx_sub = DMA_SUBPERI0;

    uint32_t dmax_dirction = DMA_PERIPH_TO_MEMORY;

    uint32_t dmax_src = (uint32_t)(&ADC_RDATA(ADC0));
    uint32_t dmax_src_inc = DMA_PERIPH_INCREASE_DISABLE;
    uint32_t dmax_src_width = DMA_PERIPH_WIDTH_16BIT;
    uint32_t dmax_src_len = ADC0_CHNS_LEN;

    uint32_t dmax_dst = (uint32_t)(buff);
    uint32_t dmax_dst_inc = DMA_MEMORY_INCREASE_ENABLE;

    /**************** DMA p2m *******************/
    // ʱ��
    rcu_periph_clock_enable(dmax_rcu);
    // ����dma
    dma_deinit(dmax, dmax_ch);

    //////// dma ����
    dma_single_data_parameter_struct dsdps;
    dma_single_data_para_struct_init(&dsdps);
    // ����
    dsdps.direction = DMA_PERIPH_TO_MEMORY;
    // �ڴ�: dst
    dsdps.memory0_addr = dmax_dst;
    dsdps.memory_inc = dmax_dst_inc;
    // ����: src
    dsdps.periph_addr = dmax_src;
    dsdps.periph_inc = dmax_src_inc;
    // ���ݳ���
    dsdps.number = dmax_src_len;
    // dst���ݿ��
    dsdps.periph_memory_width = dmax_src_width;
    // �������ȼ�
    dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(dmax, dmax_ch, &dsdps);

    //////// ���� dma ������
    dma_channel_subperipheral_select(dmax, dmax_ch, damx_sub);

    dma_circulation_enable(dmax, dmax_ch);

    // Ĭ�Ͽ�������
    dma_flag_clear(dmax, dmax_ch, DMA_FLAG_FTF);
    dma_channel_enable(dmax, dmax_ch);
}

static void gpio_adc_config(uint32_t rcu, uint32_t port, uint32_t pin) {
	// 1. ʱ�ӳ�ʼ��
	rcu_periph_clock_enable(rcu);
	// 2. ����GPIO �������ģʽ
	gpio_mode_set(port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, pin);
}

void lib_adc0_init() {
	// ADC����
	/****************** GPIO config *********************/
	for(uint8_t i = 0; i < ADC0_CHNS_LEN; i++) {
		if(adc_chns[i] == ADC_CHANNEL_0) {
			gpio_adc_config(CH0_PIN);
		} else if(adc_chns[i] == ADC_CHANNEL_1) {
			gpio_adc_config(CH1_PIN);
		} else if(adc_chns[i] == ADC_CHANNEL_2) {
			gpio_adc_config(CH2_PIN);
		} else if(adc_chns[i] == ADC_CHANNEL_3) {
			gpio_adc_config(CH3_PIN);
		}
	}
	
	/******************** ADC config **********************/
    // ����ʱ��
    rcu_periph_clock_enable(RCU_ADC0);
   
    ////////// ��������
    adc_resolution_config(ADC0, ADC0_RESOLUTION); // �ֱ���
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);// �����Ҷ���

    //////////// ��������
    // ����ͨ����ͨ������  ?????????????
	adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, ADC0_CHNS_LEN);
	for(uint8_t i = 0; i < ADC0_CHNS_LEN; i++) {
		adc_routine_channel_config(ADC0, i, adc_chns[i], adc_chns_samples[i]);
	}
   
    /////////// ģʽ����
    adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);// ɨ��ģʽ
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, ENABLE);//ȡ������ģʽ

    // DMA
    adc_dma_request_after_last_enable(ADC0);
    adc_dma_mode_enable(ADC0);

    // ��ADC
    adc_enable(ADC0);

    // У׼ADC
    adc_calibration_enable(ADC0);
    delay_1ms(100);//
	
	
	DMA_config();
	

    // ��������
    adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL);

}




uint16_t lib_adc0_get(uint8_t index) {
	return buff[index];
}














#endif // USE_ADC0