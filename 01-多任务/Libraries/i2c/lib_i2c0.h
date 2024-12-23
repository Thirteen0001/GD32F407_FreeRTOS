#ifndef __LIB_I2C0_H__
#define __LIB_I2C0_H__

#include "I2C_config.h"

#if USE_LIB_I2C0
#include "systick.h"
#include "gd32f4xx.h"


void lib_I2C0_init();

uint8_t lib_I2C0_read(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len);

uint8_t lib_I2C0_write(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len);

uint8_t lib_I2C0_write2(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t offset, uint32_t len);

void lib_I2C0_deinit();

#endif

#endif