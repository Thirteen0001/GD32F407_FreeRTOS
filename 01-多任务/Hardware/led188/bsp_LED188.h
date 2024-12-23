#ifndef __BSP_LED188_H__
#define __BSP_LED188_H__


#include "board_config.h"




void LED188_init();


void LED188_set_num(uint8_t num);
void LED188_charge(uint8_t enable);
void LED188_percent(uint8_t enable);


void LED188_display();



#endif