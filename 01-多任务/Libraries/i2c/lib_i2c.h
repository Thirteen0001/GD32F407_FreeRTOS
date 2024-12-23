#ifndef __I2C_H__
#define __I2C_H__


#include "I2C_config.h"


#if USE_LIB_I2C0
#include "lib_I2C0.h"
#endif

#if USE_LIB_I2C1
#include "lib_I2C1.h"
#endif

#if USE_LIB_I2C2
#include "lib_I2C2.h"
#endif

void lib_I2C_init();

#endif