#ifndef __BSP_WS2812_H__
#define __BSP_WS2812_H__

#include "board_config.h"


void ws2812_init();


// 8bit(±£¡Ù) + 8bit(RED) + 8bit(GREEN) + 8bit(BLUE)
void ws2812_set_color(uint16_t index, uint32_t color);

// À¢
void ws2812_display();


#endif
