#include "bsp_touch_key.h"

// bit0 -> key11
// bit1 -> key10
static uint16_t key_state = 0;
static uint16_t last_state = 0;// 默认值都是0

void tk_init() {
    printf("tk init \r\n");
	
	unsigned char databuf;
#ifdef SPECIAL_APP
	/// 灵敏度配置 CIN4
    databuf = 0x79; 
	TK_WR(SC12B_ADDR, SenSet0_REG, &databuf, 1);
	/// 灵敏度配置 其他
    databuf = 0x79;
	TK_WR(SC12B_ADDR, SenSetCOM_REG, &databuf, 1);
    
	databuf = SLPCYC_3R5T | SLOW_TO_SLEEP | HOLD | KVF_50S_CORREC | RTM3;
	TK_WR(SC12B_ADDR, CTRL0_REG, &databuf, 1);
    
	databuf = 0b1111;
	TK_WR(SC12B_ADDR, CTRL1_REG, &databuf, 1);
#endif
	
}


void lib_exti8_on_trig() {
    // 当用户触摸了按键，产生中断，通过i2c读取触摸芯片数据 ???? TODO
	//  printf("tk interrupt \r\n");
	uint8_t data[2];
	TK_RD(SC12B_ADDR, Output_REG, data, 2);
	
	//printf("tk: 0x%02X 0x%02X\r\n", data[0], data[1]);
	
	// 12 bit
	// 16个bit： 0 1 2 3 4 5 6 7 8 9 10 11 x x x x
	// 									4  3 2 1 0
	
	// 按键状态 ： 	0 1 2 3 4 5 6 7 8 9 10 11
	// bit11-bit0：
	key_state =  (((uint16_t)data[0] << 4) & 0xFFF) + ((data[1] >> 4) & 0x0F);
	
	uint16_t diff = key_state ^ last_state;
	
	if(diff) {
		for(uint8_t i = 0; i < 12; i++) {
			// key_n 哪一个bit位
			if(diff & (1 << i)) {
				// 结果不为0， 变化了
				if(key_state & (1 << i)) {
					// 按下
					tk_on_down(11 - i);
				} else {
					// 抬起
					tk_on_up(11 - i);
				}
			}
		}
		
		// 更新状态
		last_state = key_state;
	} 
	
}

