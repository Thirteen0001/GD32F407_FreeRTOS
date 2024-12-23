#ifndef __LIB_SPI_H__
#define __LIB_SPI_H__

#include "SPI_config.h"

#if USE_LIB_SPI_0
#include "lib_spi0.h"
#endif

#if USE_LIB_SPI_1
#include "lib_spi1.h"
#endif

#if USE_LIB_SPI_2
#include "lib_spi2.h"
#endif

#if USE_LIB_SPI_3
#include "lib_spi3.h"
#endif

#if USE_LIB_SPI_4
#include "lib_spi4.h"
#endif

#if USE_LIB_SPI_5
#include "lib_spi5.h"
#endif


void lib_spi_init();


#endif