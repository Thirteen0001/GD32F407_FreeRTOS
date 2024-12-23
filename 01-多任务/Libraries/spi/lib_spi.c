#include "lib_spi.h"


void lib_spi_init() {

#if USE_LIB_SPI_0
	lib_spi0_init();
#endif

#if USE_LIB_SPI_1
	lib_spi1_init();
#endif
	
#if USE_LIB_SPI_2
	lib_spi2_init();
#endif
	
#if USE_LIB_SPI_3
	lib_spi3_init();
#endif
	
#if USE_LIB_SPI_4
	lib_spi4_init();
#endif
	
#if USE_LIB_SPI_5
	lib_spi5_init();
#endif
	
}