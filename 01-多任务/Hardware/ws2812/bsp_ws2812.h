#ifndef __BSP_WS2812_H__
#define __BSP_WS2812_H__

#include "board_config.h"


void ws2812_init();


// 8bit(����) + 8bit(RED) + 8bit(GREEN) + 8bit(BLUE)
void ws2812_set_color(uint16_t index, uint32_t color);

// ˢ
void ws2812_display();


#endif
