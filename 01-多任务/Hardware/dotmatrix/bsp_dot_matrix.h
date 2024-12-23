#ifndef __DOT_MATRIX_H__
#define __DOT_MATRIX_H__

#include "board_config.h"


void dm_init();

void dm_set_num(uint8_t index, uint8_t num);

/// index 表示，设置哪一个点阵
/// data  点阵对应的数据
void dm_set_data(uint8_t index, uint8_t dat[8]);

void dm_display();

#endif