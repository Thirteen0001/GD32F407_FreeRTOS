#ifndef __NIXIE_H__
#define __NIXIE_H__

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

// 输入寄存器
#define NIX_DI_RCU		RCU_GPIOD
#define NIX_DI_GPIO   	GPIOD, GPIO_PIN_0
// 锁存寄存器
#define NIX_RCK_RCU		RCU_GPIOD
#define NIX_RCK_GPIO  	GPIOD, GPIO_PIN_1
// 移位寄存器
#define NIX_SCK_RCU		RCU_GPIOD
#define NIX_SCK_GPIO  	GPIOD, GPIO_PIN_4


// 初始化
void Nixie_init();

// num: 控制显示的什么内容
// idx: 控制显示哪几个显示
void Nixie_show(u8 num, u8 idx);

// num 对应的内容在数组的位置(索引)，配合自定义码表
// 除了0~9，刚好和下标一致，其它的内容，需要查表
// idx  显示在屏幕上的位置(1 -> 8)，只有1个数码管显示
void Nixie_display(u8 num, u8 idx);

#endif