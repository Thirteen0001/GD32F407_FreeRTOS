#include "lib_I2C.h"



void lib_I2C_init() {
#if USE_LIB_I2C0
	lib_I2C0_init();
#endif

#if USE_LIB_I2C1
	lib_I2C1_init();
#endif

#if USE_LIB_I2C2
	lib_I2C2_init();
#endif
}