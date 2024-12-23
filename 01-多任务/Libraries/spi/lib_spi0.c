#include "lib_spi0.h"

#if USE_LIB_SPI_0

#if SPI0_SOFT


#define CLK(bit) 	gpio_bit_write(SPI0_CLK_PORT, SPI0_CLK_PIN, ((bit) == 0) ? RESET : SET)
#define MOSI(bit) 	gpio_bit_write(SPI0_MOSI_PORT,SPI0_MOSI_PIN, ((bit) == 0) ? RESET : SET)

#if SPI0_MISO_ENABLE
#define MISO_STATE()  gpio_input_bit_get(SPI0_MISO_PORT, SPI0_MISO_PIN)
#endif

void lib_spi0_init() {
    /*********** GPIO config ***************/
    // clk
    rcu_periph_clock_enable(SPI0_CLK_PORT_RCU);
    gpio_mode_set(SPI0_CLK_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SPI0_CLK_PIN);
    gpio_output_options_set(SPI0_CLK_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_CLK_PIN);

#if SPI0_MOSI_ENABLE
    // mosi
    rcu_periph_clock_enable(SPI0_MOSI_PORT_RCU);
    gpio_mode_set(SPI0_MOSI_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, SPI0_MOSI_PIN);
    gpio_output_options_set(SPI0_MOSI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_MOSI_PIN);
#endif
#if SPI0_MISO_ENABLE
    // miso
    rcu_periph_clock_enable(SPI0_MISO_PORT_RCU);
    gpio_mode_set(SPI0_MISO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, SPI0_MISO_PIN);
    gpio_output_options_set(SPI0_MISO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_MISO_PIN);
#endif
}


#if SPI0_MOSI_ENABLE
void lib_spi0_write(uint8_t dat) {
    uint8_t i;
    for(i=0; i<8; i++)
    {
        CLK(0);
        MOSI(dat&0x80);
        dat<<=1;
        CLK(1);
    }
    CLK(0);//拉低
}
#endif
#if SPI0_MISO_ENABLE
uint8_t lib_spi0_read() {
    uint8_t i,read=0;
    for(i=0; i<8; i++)
    {
        CLK(0);
        read<<=1;
        if(MISO_STATE())
        {
            read++;
        }
        CLK(1);
    }
    CLK(0);//拉低
    return read;
}
#endif


#if SPI0_MOSI_ENABLE && SPI0_MISO_ENABLE
uint8_t lib_spi0_write_read(uint8_t dat) {
    uint8_t i,read=0;
    for(i=0; i<8; i++)
    {
        CLK(0);
        MOSI(dat&0x80);
        dat<<=1;

        read<<=1;
        if(MISO_STATE())
        {
            read++;
        }
        CLK(1);
    }
    CLK(0);//拉低
    return read;
}
#endif


#else

#define SPIx_RCU		RCU_SPI0
#define SPIx				SPI0

#if SPI0_DMA_TX_ENABLE
#define DMAx		DMA1
#define RCU_DMAx	RCU_DMA1
#define DMAx_CH		DMA_CH5
#define DMAx_SUB	DMA_SUBPERI3
#define DMAx_IRQ	DMA1_Channel5_IRQn

static void dma_tx_config() {
	
	uint32_t dmax = DMAx;
	uint32_t dmax_rcu = RCU_DMAx;
	uint32_t dmax_ch = DMAx_CH;
	uint32_t damx_sub = DMAx_SUB;

	uint32_t dmax_dirction = DMA_MEMORY_TO_PERIPH;

	//    uint32_t dmax_src = (uint32_t)src;
	uint32_t dmax_src_inc = DMA_MEMORY_INCREASE_ENABLE;
	uint32_t dmax_src_width = DMA_MEMORY_WIDTH_8BIT;
	//    uint32_t dmax_src_len = ARR_LEN;

	uint32_t dmax_dst = (uint32_t)(&SPI_DATA(SPIx));
	uint32_t dmax_dst_inc = DMA_PERIPH_INCREASE_DISABLE;

	/***************** DMA m2p *******************/
	// 时钟
	rcu_periph_clock_enable(dmax_rcu);
	// 重置dma
	dma_deinit(dmax, dmax_ch);

	//////// dma 配置
	dma_single_data_parameter_struct dsdps;
	dma_single_data_para_struct_init(&dsdps);
	// 方向
	dsdps.direction = dmax_dirction;
	// 内存: src
	//    dsdps.memory0_addr = (uint32_t)src;
	dsdps.memory_inc = dmax_src_inc;
	// 外设: dst
	dsdps.periph_addr = dmax_dst;
	dsdps.periph_inc = dmax_dst_inc;
	//    // 数据长度
	//    dsdps.number = ARR_LEN;
	// 数据宽度
	dsdps.periph_memory_width = dmax_src_width;
	// 传输优先级
	dsdps.priority = DMA_PRIORITY_ULTRA_HIGH;
	
	dma_single_data_mode_init(dmax, dmax_ch, &dsdps);

	//////// 配置 dma 子连接
	dma_channel_subperipheral_select(dmax, dmax_ch, damx_sub);
	
	
	/* 关闭DMA通道 */
    dma_channel_disable(DMAx, DMAx_CH);
    dma_flag_clear(DMAx, DMAx_CH, DMA_FLAG_FTF);
	
	////// 配置dma的中断
	dma_interrupt_enable(dmax, dmax_ch, DMA_INT_FTF);
	nvic_irq_enable(DMAx_IRQ, SPI0_DMA_TX_NVIC);
	
}
#endif

void lib_spi0_init() {

    /*********** GPIO config ***************/
    // clk
    rcu_periph_clock_enable(SPI0_CLK_PORT_RCU);
    gpio_mode_set(SPI0_CLK_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SPI0_CLK_PIN);
    gpio_output_options_set(SPI0_CLK_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_CLK_PIN);
    gpio_af_set(SPI0_CLK_PORT, SPI0_CLK_AF, SPI0_CLK_PIN);

#if SPI0_MOSI_ENABLE
    // mosi
    rcu_periph_clock_enable(SPI0_MOSI_PORT_RCU);
    gpio_mode_set(SPI0_MOSI_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SPI0_MOSI_PIN);
    gpio_output_options_set(SPI0_MOSI_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_MOSI_PIN);
    gpio_af_set(SPI0_MOSI_PORT, SPI0_MOSI_AF, SPI0_MOSI_PIN);
#endif
#if SPI0_MISO_ENABLE
    // miso
    rcu_periph_clock_enable(SPI0_MISO_PORT_RCU);
    gpio_mode_set(SPI0_MISO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, SPI0_MISO_PIN);
    gpio_output_options_set(SPI0_MISO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_MISO_PIN);
    gpio_af_set(SPI0_MISO_PORT, SPI0_MISO_AF, SPI0_MISO_PIN);
#endif
    /*************** spi config **************/
    // 时钟
    rcu_periph_clock_enable(SPIx_RCU);

    spi_parameter_struct spi_init_struct;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    // negative slave select
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.clock_polarity_phase = SPI0_PARAM_CPOL_CPHA;
    spi_init_struct.prescale             = SPI0_PARAM_PSC;
    spi_init_struct.endian               = SPI0_PARAM_ENDIAN;

    spi_init(SPIx, &spi_init_struct);

#if SPI0_DMA_TX_ENABLE
	/// DMA 发送
	dma_tx_config();
	spi_dma_enable(SPIx, SPI_DMA_TRANSMIT);
#endif

    spi_enable(SPIx);
}


#if SPI0_DMA_TX_ENABLE

void lib_spi0_dma_write(uint32_t memery_addr, uint32_t memery_len) {
	 /* 关闭DMA通道 */
    dma_channel_disable(DMAx, DMAx_CH);
    dma_flag_clear(DMAx, DMAx_CH, DMA_FLAG_FTF);
	
	// 数据来源 和 长度
    dma_memory_address_config(DMAx, DMAx_CH, DMA_MEMORY_0, memery_addr);
    dma_transfer_number_config(DMAx, DMAx_CH, memery_len);

    // 触发传输
    dma_channel_enable(DMAx, DMAx_CH);

	////// 不需要卡住，中断去实现
//    // 等待DMA传输完成
//    while(RESET == dma_flag_get(DMAx, DMAx_CH, DMA_FLAG_FTF));
//    // 清理标记
//    dma_flag_clear(DMAx, DMAx_CH, DMA_FLAG_FTF);
}

void DMA1_Channel5_IRQHandler() {
	if(SET == dma_interrupt_flag_get(DMAx, DMAx_CH, DMA_INT_FLAG_FTF)) {
		dma_interrupt_flag_clear(DMAx, DMAx_CH, DMA_INT_FLAG_FTF);
		
		/// 传输完成
		lib_spi0_dma_write_on_finish();
	}
}

#endif



#if SPI0_MOSI_ENABLE
void lib_spi0_write(uint8_t data) {
    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_TBE));
    //硬件电路，发送数据，放到寄存器
    spi_i2s_data_transmit(SPIx, data);

    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_RBNE));
    //硬件电路，发送数据，放到寄存器
    spi_i2s_data_receive(SPIx);
}
#endif
#if SPI0_MISO_ENABLE
uint8_t lib_spi0_read() {
    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_TBE));
    //硬件电路，发送数据，放到寄存器
    spi_i2s_data_transmit(SPIx, 0x00);

    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_RBNE));
    //硬件电路，发送数据，放到寄存器
    return spi_i2s_data_receive(SPIx);
}
#endif

#if SPI0_MOSI_ENABLE && SPI0_MISO_ENABLE
uint8_t lib_spi0_write_read(uint8_t dat) {
    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_TBE));
    //硬件电路，发送数据，放到寄存器
    spi_i2s_data_transmit(SPIx, dat);

    while(RESET == spi_i2s_flag_get(SPIx, SPI_FLAG_RBNE));
    //硬件电路，发送数据，放到寄存器
    return spi_i2s_data_receive(SPIx);
}
#endif

#endif

#endif