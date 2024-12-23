#ifndef __LIB_SPI0_H__
#define __LIB_SPI0_H__

#include "SPI_config.h"

#if USE_LIB_SPI_0

void lib_spi0_init();

#if SPI0_MOSI_ENABLE
void lib_spi0_write(uint8_t data);
#endif

#if SPI0_MISO_ENABLE
uint8_t lib_spi0_read();
#endif

#if SPI0_MOSI_ENABLE && SPI0_MISO_ENABLE
uint8_t lib_spi0_write_read(uint8_t dat);
#endif


#if SPI0_DMA_TX_ENABLE
void lib_spi0_dma_write(uint32_t memery_addr, uint32_t memery_len);

extern void lib_spi0_dma_write_on_finish();
#endif

#endif
#endif