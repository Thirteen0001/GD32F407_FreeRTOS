#ifndef __I2C2_H__
#define __I2C2_H__

#include "I2C_config.h"

#if USE_I2C2
#include "systick.h"
#include "gd32f4xx.h"

void I2C2_init();

uint8_t I2C2_read(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len);

uint8_t I2C2_write(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t len);

uint8_t I2C2_write2(uint8_t addr, uint8_t reg, uint8_t* data, uint32_t offset, uint32_t len);

void I2C2_deinit();

#endif

#endif