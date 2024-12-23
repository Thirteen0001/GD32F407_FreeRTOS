#include "lib_usart1.h"

#if USE_LIB_USART1

#include <stdio.h>
#include <string.h>

static uint8_t usart1_recv_buff[USART1_RECV_LEN];   // ���ջ�����
static uint32_t usart1_recv_len = 0;

#define USART1_TX_AF		GPIO_AF_7
#define USART1_RX_AF		GPIO_AF_7

#if USART1_ENABLE_DMA_SEND

// 	USART1 
//			DMA		CHN		SUBPERI 
//	TX	0		6		4
//	RX	0		5		4

#define USART1_DMA_TX					DMA0
#define USART1_DMA_TX_RCU			RCU_DMA0
#define USART1_DMA_TX_CHN			DMA_CH6
#define USART1_DMA_TX_SUBPERI	DMA_SUBPERI4

static void DMA_tx_config() {
    uint32_t dma_tx_rcu = USART1_DMA_TX_RCU;
    uint32_t dma_tx = USART1_DMA_TX;
    uint32_t dma_tx_chn = USART1_DMA_TX_CHN;
    uint32_t dma_tx_direction = DMA_MEMORY_TO_PERIPH;
    uint32_t dma_tx_dst_addr = (uint32_t)(&USART_DATA(USART1));
    uint32_t dam_tx_subperi = USART1_DMA_TX_SUBPERI;
    /********************* DMA TX ***************************/
    // ����ʱ��
    rcu_periph_clock_enable(dma_tx_rcu);
    // ����DMA
    dma_deinit(dma_tx, dma_tx_chn);
    // ��ʼ��dma
    dma_single_data_parameter_struct dsdps;
    dma_single_data_para_struct_init(&dsdps);

    dsdps.direction = dma_tx_direction;// ���䷽ʽ���ڴ浽����

    //dsdps.number = ARR_LEN; //��������ݸ���
    //dsdps.memory0_addr = (uint32_t)dst; // �ڴ��ַ
    dsdps.memory_inc = DMA_PERIPH_INCREASE_ENABLE;// �ڴ��ַ������

    dsdps.periph_addr = dma_tx_dst_addr; // �����ַ
    dsdps.periph_inc = DMA_PERIPH_INCREASE_DISABLE;// �����ַ��������
    dsdps.periph_memory_width = DMA_MEMORY_WIDTH_8BIT; //�����ַ�����ݿ��Ϊ8λ

    dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;//�������ȼ�

    dma_single_data_mode_init(dma_tx, dma_tx_chn, &dsdps);

    // ����DMAͨ������������
    dma_channel_subperipheral_select(dma_tx, dma_tx_chn, dam_tx_subperi);
}
#endif

#if USART1_ENABLE_DMA_RECV

#define USART1_DMA_RX	 				DMA0
#define USART1_DMA_RX_RCU 		RCU_DMA0
#define USART1_DMA_RX_CHN 		DMA_CH5
#define USART1_DMA_RX_SUBPERI	DMA_SUBPERI4

static void DMA_rx_config() {
    uint32_t dma_rx_rcu = USART1_DMA_RX_RCU;
    uint32_t dma_rx = USART1_DMA_RX;
    uint32_t dma_rx_chn = USART1_DMA_RX_CHN;
    uint32_t dma_rx_direction = DMA_PERIPH_TO_MEMORY;
    uint32_t dma_rx_src_addr = (uint32_t)(&USART_DATA(USART1));
    uint32_t dma_rx_dst_addr = (uint32_t)usart1_recv_buff;
    uint32_t dam_rx_subperi = USART1_DMA_RX_SUBPERI;
    /******************** DMA RX *******************/
    // ����ʱ��
    rcu_periph_clock_enable(dma_rx_rcu);
    // ����DMA
    dma_deinit(dma_rx, dma_rx_chn);
    // ��ʼ��dma
    dma_single_data_parameter_struct dsdps;
    dma_single_data_para_struct_init(&dsdps);

    dsdps.direction = dma_rx_direction;// ���䷽ʽ�����赽�ڴ�

    dsdps.number = USART1_RECV_LEN; //��������ݸ���
    dsdps.memory0_addr = dma_rx_dst_addr; // �ڴ��ַ
    dsdps.memory_inc = DMA_PERIPH_INCREASE_ENABLE;// �ڴ��ַ������

    dsdps.periph_addr = dma_rx_src_addr; // �����ַ
    dsdps.periph_inc = DMA_PERIPH_INCREASE_DISABLE;// �����ַ��������
    dsdps.periph_memory_width = DMA_MEMORY_WIDTH_8BIT; //�����ַ�����ݿ��Ϊ8λ

    dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;//�������ȼ�

    dma_single_data_mode_init(dma_rx, dma_rx_chn, &dsdps);

    // ����DMAͨ������������
    dma_channel_subperipheral_select(dma_rx, dma_rx_chn, dam_rx_subperi);

    // ʹ��DMA����
    dma_channel_enable(dma_rx, dma_rx_chn);

    // ����DMA���
    dma_interrupt_flag_clear(dma_rx, dma_rx_chn, DMA_INT_FLAG_FTF);
}
#endif

void lib_usart1_init() {
    uint32_t usartx = USART1;
    uint32_t usartx_rcu = RCU_USART1;
    uint32_t usartx_irqn = USART1_IRQn;

    uint32_t tx_gpio_rcu = USART1_TX_RCU;
    uint32_t tx_gpio_port = USART1_TX_PORT;
    uint32_t tx_gpio_pin = USART1_TX_PIN;
    uint32_t tx_gpio_af = USART1_TX_AF;

    uint32_t rx_gpio_rcu = USART1_RX_RCU;
    uint32_t rx_gpio_port = USART1_RX_PORT;
    uint32_t rx_gpio_pin = USART1_RX_PIN;
    uint32_t rx_gpio_af = USART1_RX_AF;

    uint32_t baudrate = USART1_PARAM_BAUDRATE;
    uint32_t parity = 	USART1_PARAM_PARITY;
    uint32_t word_len = USART1_PARAM_WORD_LEN;
    uint32_t stop_bit = USART1_PARAM_STOP_BIT;
    uint32_t data_first = USART1_PARAM_DATA_FIRST;
    ////////// gpio config ///////////////
    // ����ʱ��
    rcu_periph_clock_enable(tx_gpio_rcu);
    rcu_periph_clock_enable(rx_gpio_rcu);
    // ����ģʽ
    gpio_mode_set(tx_gpio_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, tx_gpio_pin);
    gpio_mode_set(rx_gpio_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, rx_gpio_pin);
    // ���ø��ù���
    gpio_af_set(tx_gpio_port, tx_gpio_af, tx_gpio_pin);
    gpio_af_set(rx_gpio_port, rx_gpio_af, rx_gpio_pin);
    // �����������
    gpio_output_options_set(tx_gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, tx_gpio_pin);
    gpio_output_options_set(rx_gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, rx_gpio_pin);

    ////////// usart config /////////////
    // ����ʱ��
    rcu_periph_clock_enable(usartx_rcu);
    // USART��λ
    usart_deinit(usartx);
    usart_baudrate_set(usartx, baudrate);// ������
    usart_parity_config(usartx, parity);// У��λ
    usart_word_length_set(usartx, word_len);// ����λ��
    usart_stop_bit_set(usartx, stop_bit);// ֹͣλ
    usart_data_first_config(usartx, data_first);// �ȷ��͸�λ���ǵ�λ

#if USART1_ENABLE_SEND
    // ���͹�������
    usart_transmit_config(usartx, USART_TRANSMIT_ENABLE);
#endif

#if USART1_ENABLE_RECV
    // ���չ�������
    usart_receive_config(usartx, USART_RECEIVE_ENABLE);
    // �����ж�����
    nvic_irq_enable(usartx_irqn, USART1_RECV_NVIC_IRQ);
    // usart int rbne
    usart_interrupt_enable(usartx, USART_INT_RBNE);
    usart_interrupt_enable(usartx, USART_INT_IDLE);
#endif

#if USART1_ENABLE_DMA_SEND
    // ����DMA���͹���
    usart_dma_transmit_config(usartx, USART_TRANSMIT_DMA_ENABLE);
	DMA_tx_config();
#endif

#if USART1_ENABLE_DMA_RECV
    // ����DMA���չ���
    usart_dma_receive_config(usartx, USART_RECEIVE_DMA_ENABLE);
	DMA_rx_config();
#endif

    // ʹ�ܴ���
    usart_enable(usartx);
}

#if USART1_ENABLE_DMA_SEND
static void Usart1_dma_send(uint8_t* data, uint32_t len) {
	if(data == NULL || len == 0) return;
	
    uint32_t dma_tx_rcu = USART1_DMA_TX_RCU;
    uint32_t dma_tx = USART1_DMA_TX;
    uint32_t dma_tx_chn = USART1_DMA_TX_CHN;
    uint32_t dma_tx_direction = DMA_MEMORY_TO_PERIPH;
    uint32_t dma_tx_dst_addr = (uint32_t)(&USART_DATA(USART1));
    /******************** DMA send *******************/
    /* �ر�DMAͨ�� */
    dma_channel_disable(dma_tx, dma_tx_chn);
    /* ����DMA������ڴ��ַ�ʹ������ݴ�С */
    dma_memory_address_config(dma_tx, dma_tx_chn, DMA_MEMORY_0, (uint32_t)data);
    dma_transfer_number_config(dma_tx, dma_tx_chn, len);
    /* ʹ��DMAͨ�� */
    dma_channel_enable(dma_tx, dma_tx_chn);
	
	while(1) {
		if(dma_flag_get(dma_tx, dma_tx_chn, DMA_FLAG_FTF) != RESET) {
			/* ���DMA������ɱ�־ */
			dma_flag_clear(dma_tx, dma_tx_chn, DMA_FLAG_FTF);
			break;
		}
	}
}
#endif

void lib_usart1_send_byte(uint8_t data) {
	#if USART1_ENABLE_DMA_SEND
	Usart1_dma_send(&data, 1);
	#else
    //ͨ��USART����
    usart_data_transmit(USART1, data);
    //�жϻ������Ƿ��Ѿ�����
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
	#endif
}

void lib_usart1_send_data(uint8_t *data, uint32_t len) {
#if USART1_ENABLE_DMA_SEND
    Usart1_dma_send(data, len);
#else
    while(len--) {
        //ͨ��USART����
        usart_data_transmit(USART1, *data++);

        //�жϻ������Ƿ��Ѿ�����
        while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    }
#endif
}

//�����ַ���
void lib_usart1_send_string(char *data) {
    while(data && *data) {
        lib_usart1_send_byte((uint8_t)(*data));
        data++;
    }
}

#if USART1_ENABLE_RECV
void USART1_IRQHandler(void) {
#if USART1_ENABLE_DMA_RECV
    uint32_t dma_rx = USART1_DMA_RX;
    uint32_t dma_rx_chn = USART1_DMA_RX_CHN;

    if (usart_interrupt_flag_get(USART1, USART_INT_FLAG_IDLE) == SET) {
        /* ������ڿ����жϱ�־ */
        usart_interrupt_flag_clear(USART1, USART_INT_FLAG_IDLE);

        //��ȡ������,��ջ�����
        usart_data_receive(USART1);

        // �ر�DMA����ͨ��
        dma_channel_disable(dma_rx, dma_rx_chn);

        usart1_recv_len = USART1_RECV_LEN - dma_transfer_number_get(dma_rx, dma_rx_chn);
        if(usart1_recv_len != 0 && usart1_recv_len < USART1_RECV_LEN)
        {
#if USART1_RECV_CALLBACK
			// ����ֹͣʱ���������е����ݣ������ڴ˴����������ݡ�TODO:
            lib_usart1_on_recv(usart1_recv_buff, usart1_recv_len);
#endif
            usart1_recv_buff[usart1_recv_len] = '\0';
            
            dma_flag_clear(dma_rx, dma_rx_chn, DMA_FLAG_FTF);
            dma_channel_enable(dma_rx, dma_rx_chn);
        } else {
            memset(usart1_recv_buff, 0, USART1_RECV_LEN);
        }
    }
#else
    if ((usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE)) == SET) {
        uint16_t value = usart_data_receive(USART1);
        usart1_recv_buff[usart1_recv_len] = value;
        usart1_recv_len++;
        // ���յ�����byte�������ڴ˴�������յ�value��TODO:
    }
    if (usart_interrupt_flag_get(USART1, USART_INT_FLAG_IDLE) == SET) {
        //��ȡ������,��ջ�����
        usart_data_receive(USART1);
        usart1_recv_buff[usart1_recv_len] = '\0';

        // ����ֹͣʱ���������е����ݣ������ڴ˴����������ݡ�TODO:
#if USART1_RECV_CALLBACK
        lib_usart1_on_recv(usart1_recv_buff, usart1_recv_len);
#endif
        usart1_recv_len = 0;
    }
#endif
}
#endif

#ifdef USE_LIB_PRINT
#if USE_LIB_PRINT == 1

int fputc(int ch, FILE *f) {
    lib_usart1_send_byte((uint8_t)ch);
    return ch;
}

#endif
#endif

#endif