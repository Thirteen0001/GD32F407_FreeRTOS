#ifndef __LIB_SPI3_H__
#define __LIB_SPI3_H__

#include "SPI_config.h"

#if USE_LIB_SPI_3

void lib_spi3_init();

#if SPI3_MOSI_ENABLE
void lib_spi3_write(uint8_t data);
#endif

#if SPI3_MISO_ENABLE
uint8_t lib_spi3_read();
#endif

#if SPI3_MOSI_ENABLE && SPI3_MISO_ENABLE
uint8_t lib_spi3_write_read(uint8_t dat);
#endif

#endif
#endif