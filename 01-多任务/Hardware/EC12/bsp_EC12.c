#include "bsp_EC12.h"





void EC12_init() {
	
	printf("EC12 init\r\n");
}


/// A 中断
void EC12_A_EXTI_FUNC() {
	/// 当 A触发了下降沿时候，B如果是 低， 就是正转
	/// 当 A触发了下降沿时候，B如果是 高， 就是反转
	
	static uint32_t last_time = 0;
	static uint8_t last_a_state = SET;
	
//	uint32_t current_time = CURRENT_TICK_MS();
//	if(current_time - last_time < EC12_DELAY){
//		return;
//	}
//	last_time = current_time;
	
	uint8_t current_a_state = EC12_A_STATE();
	if(SET == last_a_state && RESET == current_a_state) {
		// 下降沿
		last_a_state = current_a_state;
	
		uint8_t current = EC12_B_STATE();
		if(RESET == current) {
			// 反转
			EC12_on_turn_left();
		} else {
			// 正转
			EC12_on_turn_right();
		}
		
	} else if(RESET == last_a_state && SET == current_a_state) {
		// 上升沿
		last_a_state = current_a_state;
		
		uint8_t current = EC12_B_STATE();
		if(SET == current) {
			// 反转
			EC12_on_turn_left();
		} else {
			// 正转
			EC12_on_turn_right();
		}
	}
	
}


/// D中断
void EC12_D_EXTI_FUNC() {
	static FlagStatus last = SET;
	static uint32_t last_time = 0;
	
	uint32_t current_time = CURRENT_TICK_MS();
	if(current_time - last_time < EC12_DELAY) {
		return;
	}
	last_time = current_time;
	
	// 中断
	uint8_t current = EC12_D_STATE();
	if(SET == current && RESET == last) {
		// 当前高电平
		last = current;
		// 抬起
		EC12_on_up();
	} else if(RESET == current && SET == last) {
		// 按下
		last = current;
		
		EC12_on_down();
	}
}
