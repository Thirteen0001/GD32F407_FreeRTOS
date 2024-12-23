#ifndef __LIB_SPI4_H__
#define __LIB_SPI4_H__

#include "SPI_config.h"

#if USE_LIB_SPI_4

void lib_spi4_init();

#if SPI4_MOSI_ENABLE
void lib_spi4_write(uint8_t data);
#endif

#if SPI4_MISO_ENABLE
uint8_t lib_spi4_read();
#endif

#if SPI4_MOSI_ENABLE && SPI4_MISO_ENABLE
uint8_t lib_spi4_write_read(uint8_t dat);
#endif

#endif
#endif