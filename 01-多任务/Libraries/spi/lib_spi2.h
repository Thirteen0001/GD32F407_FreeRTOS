#ifndef __LIB_SPI2_H__
#define __LIB_SPI2_H__

#include "SPI_config.h"

#if USE_LIB_SPI_2

void lib_spi2_init();

#if SPI2_MOSI_ENABLE
void lib_spi2_write(uint8_t data);
#endif

#if SPI2_MISO_ENABLE
uint8_t lib_spi2_read();
#endif

#if SPI2_MOSI_ENABLE && SPI2_MISO_ENABLE
uint8_t lib_spi2_write_read(uint8_t dat);
#endif


#if SPI2_DMA_TX_ENABLE
void lib_spi2_dma_write(uint32_t memery_addr, uint32_t memery_len);

extern void lib_spi2_dma_write_on_finish();
#endif


#endif
#endif