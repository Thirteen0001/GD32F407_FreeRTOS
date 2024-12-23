#ifndef __LIB_SPI1_H__
#define __LIB_SPI1_H__

#include "SPI_config.h"

#if USE_LIB_SPI_1

void lib_spi1_init();

#if SPI1_MOSI_ENABLE
void lib_spi1_write(uint8_t data);
#endif

#if SPI1_MISO_ENABLE
uint8_t lib_spi1_read();
#endif

#if SPI1_MOSI_ENABLE && SPI1_MISO_ENABLE
uint8_t SPI1_write_read(uint8_t dat);
#endif

#if SPI1_DMA_TX_ENABLE
void lib_spi1_dma_write(uint32_t memery_addr, uint32_t memery_len);
extern void lib_spi1_dma_write_on_finish();
#endif

#endif
#endif