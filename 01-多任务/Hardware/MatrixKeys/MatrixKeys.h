#ifndef __MATRIX_KEYS__
#define __MATRIX_KEYS__

#include "gd32f4xx.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

// 1 用户需要定义MK_on_keydown函数   0 无需定义
#define USE_KEYDOWN 0  

// 1 用户需要定义MK_on_keyup函数   0 无需定义
#define USE_KEYUP 0


// 只是做声明，用户使用的时候 打开宏定义的开关，再定义函数
// 按下的回调函数
void MK_on_keydown(u8 row, u8 col);

// 抬起的回调函数
void MK_on_keyup(u8 row, u8 col);


// 初始化
void MK_init();

// 扫描按键
void MK_scan(u16 * ks);


// 获取第row行第col列的状态是否为抬起，是抬起返回1，不是返回0
u8 MK_is_keyup(u8 row, u8 col);
// 获取第row行第col列的状态是否为按下，是按下返回1，不是返回0
u8 MK_is_keydown(u8 row, u8 col);

#endif