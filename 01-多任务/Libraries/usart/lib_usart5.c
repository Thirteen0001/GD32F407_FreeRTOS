#include "lib_usart5.h"

#if USE_LIB_USART5

#include <stdio.h>
#include <string.h>

static uint8_t usart5_recv_buff[USART5_RECV_LEN];   // 接收缓冲区
static uint32_t usart5_recv_len = 0;

#define USART5_TX_AF		GPIO_AF_8
#define USART5_RX_AF		GPIO_AF_8

// 	USART5 
//			DMA		CHN		SUBPERI 
//	TX	1			6			5
//	TX	1			7			5
//	RX	1			1			5
//	RX	1			2			5

// DMA TX config
#if USART5_ENABLE_DMA_SEND
#define USART5_DMA_TX					DMA1
#define USART5_DMA_TX_RCU			RCU_DMA1
#define USART5_DMA_TX_SUBPERI	DMA_SUBPERI5
#endif

// DMA RX config
#if USART5_ENABLE_DMA_RECV
#define USART5_DMA_RX	 				DMA1
#define USART5_DMA_RX_RCU 		RCU_DMA1
#define USART5_DMA_RX_SUBPERI	DMA_SUBPERI5
#endif

#if USART5_ENABLE_DMA_SEND
static void DMA_tx_config() {
    uint32_t dma_tx_rcu = USART5_DMA_TX_RCU;
    uint32_t dma_tx = USART5_DMA_TX;
    uint32_t dma_tx_chn = USART5_DMA_TX_CHN;
    uint32_t dma_tx_direction = DMA_MEMORY_TO_PERIPH;
    uint32_t dma_tx_dst_addr = (uint32_t)(&USART_DATA(USART5));
    uint32_t dam_tx_subperi = USART5_DMA_TX_SUBPERI;
    /********************* DMA TX ***************************/
    // 配置时钟
    rcu_periph_clock_enable(dma_tx_rcu);
    // 重置DMA
    dma_deinit(dma_tx, dma_tx_chn);
    // 初始化dma
    dma_single_data_parameter_struct dsdps;
    dma_single_data_para_struct_init(&dsdps);

    dsdps.direction = dma_tx_direction;// 传输方式：内存到外设

    //dsdps.number = ARR_LEN; //传输的数据个数
    //dsdps.memory0_addr = (uint32_t)dst; // 内存地址
    dsdps.memory_inc = DMA_PERIPH_INCREASE_ENABLE;// 内存地址自增长

    dsdps.periph_addr = dma_tx_dst_addr; // 外设地址
    dsdps.periph_inc = DMA_PERIPH_INCREASE_DISABLE;// 外设地址不自增长
    dsdps.periph_memory_width = DMA_MEMORY_WIDTH_8BIT; //外设地址的数据宽度为8位

    dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;//传输优先级

    dma_single_data_mode_init(dma_tx, dma_tx_chn, &dsdps);

    // 配置DMA通道的外设连接
    dma_channel_subperipheral_select(dma_tx, dma_tx_chn, dam_tx_subperi);
}
#endif

#if USART5_ENABLE_DMA_RECV
static void DMA_rx_config() {
    uint32_t dma_rx_rcu = USART5_DMA_RX_RCU;
    uint32_t dma_rx = USART5_DMA_RX;
    uint32_t dma_rx_chn = USART5_DMA_RX_CHN;
    uint32_t dma_rx_direction = DMA_PERIPH_TO_MEMORY;
    uint32_t dma_rx_src_addr = (uint32_t)(&USART_DATA(USART5));
    uint32_t dma_rx_dst_addr = (uint32_t)usart5_recv_buff;
    uint32_t dam_rx_subperi = USART5_DMA_RX_SUBPERI;
    /******************** DMA RX *******************/
    // 配置时钟
    rcu_periph_clock_enable(dma_rx_rcu);
    // 重置DMA
    dma_deinit(dma_rx, dma_rx_chn);
    // 初始化dma
    dma_single_data_parameter_struct dsdps;
    dma_single_data_para_struct_init(&dsdps);

    dsdps.direction = dma_rx_direction;// 传输方式：外设到内存

    dsdps.number = USART5_RECV_LEN; //传输的数据个数
    dsdps.memory0_addr = dma_rx_dst_addr; // 内存地址
    dsdps.memory_inc = DMA_PERIPH_INCREASE_ENABLE;// 内存地址自增长

    dsdps.periph_addr = dma_rx_src_addr; // 外设地址
    dsdps.periph_inc = DMA_PERIPH_INCREASE_DISABLE;// 外设地址不自增长
    dsdps.periph_memory_width = DMA_MEMORY_WIDTH_8BIT; //外设地址的数据宽度为8位

    dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;//传输优先级

    dma_single_data_mode_init(dma_rx, dma_rx_chn, &dsdps);

    // 配置DMA通道的外设连接
    dma_channel_subperipheral_select(dma_rx, dma_rx_chn, dam_rx_subperi);

    // 使能DMA接收
    dma_channel_enable(dma_rx, dma_rx_chn);

    // 清理DMA标记
    dma_interrupt_flag_clear(dma_rx, dma_rx_chn, DMA_INT_FLAG_FTF);
}
#endif

void lib_usart5_init() {
    uint32_t usartx = USART5;
    uint32_t usartx_rcu = RCU_USART5;
    uint32_t usartx_irqn = USART5_IRQn;

    uint32_t tx_gpio_rcu = USART5_TX_RCU;
    uint32_t tx_gpio_port = USART5_TX_PORT;
    uint32_t tx_gpio_pin = USART5_TX_PIN;
    uint32_t tx_gpio_af = USART5_TX_AF;

    uint32_t rx_gpio_rcu = USART5_RX_RCU;
    uint32_t rx_gpio_port = USART5_RX_PORT;
    uint32_t rx_gpio_pin = USART5_RX_PIN;
    uint32_t rx_gpio_af = USART5_RX_AF;

    uint32_t baudrate = USART5_PARAM_BAUDRATE;
    uint32_t parity = 	USART5_PARAM_PARITY;
    uint32_t word_len = USART5_PARAM_WORD_LEN;
    uint32_t stop_bit = USART5_PARAM_STOP_BIT;
    uint32_t data_first = USART5_PARAM_DATA_FIRST;
    ////////// gpio config ///////////////
    // 配置时钟
    rcu_periph_clock_enable(tx_gpio_rcu);
    rcu_periph_clock_enable(rx_gpio_rcu);
    // 配置模式
    gpio_mode_set(tx_gpio_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, tx_gpio_pin);
    gpio_mode_set(rx_gpio_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, rx_gpio_pin);
    // 配置复用功能
    gpio_af_set(tx_gpio_port, tx_gpio_af, tx_gpio_pin);
    gpio_af_set(rx_gpio_port, rx_gpio_af, rx_gpio_pin);
    // 配置输出参数
    gpio_output_options_set(tx_gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, tx_gpio_pin);
    gpio_output_options_set(rx_gpio_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, rx_gpio_pin);

    ////////// usart config /////////////
    // 串口时钟
    rcu_periph_clock_enable(usartx_rcu);
    // USART复位
    usart_deinit(usartx);
    usart_baudrate_set(usartx, baudrate);// 波特率
    usart_parity_config(usartx, parity);// 校验位
    usart_word_length_set(usartx, word_len);// 数据位数
    usart_stop_bit_set(usartx, stop_bit);// 停止位
    usart_data_first_config(usartx, data_first);// 先发送高位还是低位

#if USART5_ENABLE_SEND
    // 发送功能配置
    usart_transmit_config(usartx, USART_TRANSMIT_ENABLE);
#endif

#if USART5_ENABLE_RECV
    // 接收功能配置
    usart_receive_config(usartx, USART_RECEIVE_ENABLE);
    // 接收中断配置
    nvic_irq_enable(usartx_irqn, USART5_RECV_NVIC_IRQ);
    // usart int rbne
    usart_interrupt_enable(usartx, USART_INT_RBNE);
    usart_interrupt_enable(usartx, USART_INT_IDLE);
#endif

#if USART5_ENABLE_DMA_SEND
    // 配置DMA发送功能
    usart_dma_transmit_config(usartx, USART_TRANSMIT_DMA_ENABLE);
	DMA_tx_config();
#endif

#if USART5_ENABLE_DMA_RECV
    // 配置DMA接收功能
    usart_dma_receive_config(usartx, USART_RECEIVE_DMA_ENABLE);
	DMA_rx_config();
#endif

    // 使能串口
    usart_enable(usartx);
}

#if USART5_ENABLE_DMA_SEND
static void Usart5_dma_send(uint8_t* data, uint32_t len) {
	if(data == NULL || len == 0) return;
	
    uint32_t dma_tx_rcu = USART5_DMA_TX_RCU;
    uint32_t dma_tx = USART5_DMA_TX;
    uint32_t dma_tx_chn = USART5_DMA_TX_CHN;
    uint32_t dma_tx_direction = DMA_MEMORY_TO_PERIPH;
    uint32_t dma_tx_dst_addr = (uint32_t)(&USART_DATA(USART5));
    /******************** DMA send *******************/
    /* 关闭DMA通道 */
    dma_channel_disable(dma_tx, dma_tx_chn);
    /* 配置DMA传输的内存地址和传输数据大小 */
    dma_memory_address_config(dma_tx, dma_tx_chn, DMA_MEMORY_0, (uint32_t)data);
    dma_transfer_number_config(dma_tx, dma_tx_chn, len);
    /* 使能DMA通道 */
    dma_channel_enable(dma_tx, dma_tx_chn);
	
	while(1) {
		if(dma_flag_get(dma_tx, dma_tx_chn, DMA_FLAG_FTF) != RESET) {
			/* 清除DMA传输完成标志 */
			dma_flag_clear(dma_tx, dma_tx_chn, DMA_FLAG_FTF);
			break;
		}
	}
}
#endif

void lib_usart5_send_byte(uint8_t data) {
	#if USART5_ENABLE_DMA_SEND
	Usart5_dma_send(&data, 1);
	#else
    //通过USART发送
    usart_data_transmit(USART5, data);
    //判断缓冲区是否已经空了
    while(RESET == usart_flag_get(USART5, USART_FLAG_TBE));
	#endif
}

void lib_usart5_send_data(uint8_t* data, uint32_t len) {
#if USART5_ENABLE_DMA_SEND
    Usart5_dma_send(data, len);
#else
    while(len--) {
        //通过USART发送
        usart_data_transmit(USART5, *data++);

        //判断缓冲区是否已经空了
        while(RESET == usart_flag_get(USART5, USART_FLAG_TBE));
    }
#endif
}

//发送字符串
void lib_usart5_send_string(char *data) {
    while(data && *data) {
        lib_usart5_send_byte((uint8_t)(*data));
        data++;
    }
}

#if USART5_ENABLE_RECV
void USART5_IRQHandler(void) {
#if USART5_ENABLE_DMA_RECV
    uint32_t dma_rx = USART5_DMA_RX;
    uint32_t dma_rx_chn = USART5_DMA_RX_CHN;

    if (usart_interrupt_flag_get(USART5, USART_INT_FLAG_IDLE) == SET) {
        /* 清除串口空闲中断标志 */
        usart_interrupt_flag_clear(USART5, USART_INT_FLAG_IDLE);

        //读取缓冲区,清空缓冲区
        usart_data_receive(USART5);

        // 关闭DMA接收通道
        dma_channel_disable(dma_rx, dma_rx_chn);

        usart5_recv_len = USART5_RECV_LEN - dma_transfer_number_get(dma_rx, dma_rx_chn);
        if(usart5_recv_len != 0 && usart5_recv_len < USART5_RECV_LEN)
        {
#if USART5_RECV_CALLBACK
			// 接收停止时，缓冲区中的数据，可以在此处处理缓存数据。TODO:
            lib_usart5_on_recv(usart5_recv_buff, usart5_recv_len);
#endif
            usart5_recv_buff[usart5_recv_len] = '\0';
            
            dma_flag_clear(dma_rx, dma_rx_chn, DMA_FLAG_FTF);
            dma_channel_enable(dma_rx, dma_rx_chn);
        } else {
            memset(usart5_recv_buff, 0, USART5_RECV_LEN);
        }
    }
#else
    if ((usart_interrupt_flag_get(USART5, USART_INT_FLAG_RBNE)) == SET) {
        uint16_t value = usart_data_receive(USART5);
        usart5_recv_buff[usart5_recv_len] = value;
        usart5_recv_len++;
        // 接收到单个byte，可以在此处处理接收到value。TODO:
    }
    if (usart_interrupt_flag_get(USART5, USART_INT_FLAG_IDLE) == SET) {
        //读取缓冲区,清空缓冲区
        usart_data_receive(USART5);
        usart5_recv_buff[usart5_recv_len] = '\0';

        // 接收停止时，缓冲区中的数据，可以在此处处理缓存数据。TODO:
#if USART5_RECV_CALLBACK
        lib_usart5_on_recv(usart5_recv_buff, usart5_recv_len);
#endif
        usart5_recv_len = 0;
    }
#endif
}
#endif

#ifdef USE_LIB_PRINT
#if USE_LIB_PRINT == 5

int fputc(int ch, FILE *f) {
    lib_usart5_send_byte((uint8_t)ch);
    return ch;
}

#endif
#endif

#endif