#ifndef __LIB_SPI5_H__
#define __LIB_SPI5_H__

#include "SPI_config.h"

#if USE_LIB_SPI_5

void lib_spi5_init();

#if SPI5_MOSI_ENABLE
void lib_spi5_write(uint8_t data);
#endif

#if SPI5_MISO_ENABLE
uint8_t lib_spi5_read();
#endif

#if SPI5_MOSI_ENABLE && SPI5_MISO_ENABLE
uint8_t lib_spi5_write_read(uint8_t dat);
#endif

#endif
#endif