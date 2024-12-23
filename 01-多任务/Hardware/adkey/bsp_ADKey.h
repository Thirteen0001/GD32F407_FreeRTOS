#ifndef __BSP_ADKEY_H__
#define __BSP_ADKEY_H__



#include "board_config.h"



void ADkey_init();



void ADKey_scan();
//void ADKey_adv();



extern void ADKey_on_down(uint8_t i);
extern void ADKey_on_up(uint8_t i);

//µ¥»÷
extern void ADKey_on_click(uint8_t i);
//Ë«»÷
extern void ADKey_on_double_click(uint8_t i);
//³¤°´
extern void ADKey_on_long_click(uint8_t i);




#endif