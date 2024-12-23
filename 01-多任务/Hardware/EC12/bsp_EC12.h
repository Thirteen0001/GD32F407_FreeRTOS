#ifndef __BSP_EC12_H__
#define __BSP_EC12_H__

#include "board_config.h"

void EC12_init();

// 可以旋转

// 可以按下和抬起
// 1) 中断
///// 配置中断

// 2) 扫描
///// 扫描 EC12_scan() --> Task


extern void EC12_on_down();
extern void EC12_on_up();

extern void EC12_on_turn_right();
extern void EC12_on_turn_left();



#endif