#include "bsp_ADKey.h"


#define SAMPLE_TIME		50

/// 均值滤波  中值滤波  
/// (取和 - 最大值 - 最小值) / (采样次数 - 2)

// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		0	 0
// 0表示抬起
// 1表示按下

#define KEY_1	(1 << 0)
#define KEY_2	(1 << 1)
#define KEY_3	(1 << 2)

#define RANGE	10

#define KEY_RANGE_ALL_UP	4095
#define KEY_RANGE_KEY1		945
#define KEY_RANGE_KEY2		2054
#define KEY_RANGE_KEY3		3150
#define KEY_RANGE_KEY1_KEY2	769
#define KEY_RANGE_KEY1_KEY3	883
#define KEY_RANGE_KEY2_KEY3	1785
#define KEY_RANGE_ALL_DOWN	727

#define DELAY			10
// 10 * 200 = 2s
#define LONG_DELAY		200
// 10 * 20 = 300ms
#define CLICK_DELAY		30


#define IS_IN_RANGE(result, val)	((result) > ((val) - RANGE)) && ((result) < ((val) + RANGE))

// 当前状态
static uint8_t key_state = 0;

static uint8_t last_state = 0;

void ADkey_init() {

}


void ADKey_scan() {
	//通过ADC去读取 电压，判断哪一个按键被按下
	static uint8_t i = 0;
	static uint32_t sum = 0;
	static uint16_t min_value = 4096; // 最小值给一个最大的值
	static uint16_t max_value = 0;	  // 最大值给一个最小的值
	
	static uint8_t adv_cnt = 0;

	// 采样的过程
	
	/////////////// 获取状态的过程 ///////////////////////
	// 1000s --> 50次 每20次得到一次结果
	if(i < SAMPLE_TIME) {
		i++;
		uint16_t value = lib_adc0_get(0);
		sum += value;
		// printf("adkey: %d\r\n", value);
		if(value > max_value) max_value = value;
		if(value < min_value) min_value = value;
	} else {
		// 得到一次结果
		// 滤波后的结果
		sum -= max_value;
		sum -= min_value;
		uint16_t result = sum / (SAMPLE_TIME - 2);
		
		//printf("result: %d\r\n", result);
		// 使用滤波后的结果处理逻辑
		if(IS_IN_RANGE(result, KEY_RANGE_ALL_UP)) {
			// 都是抬起的
			key_state &= ~KEY_1; // key1 抬起
			key_state &= ~KEY_2; // key2 抬起
			key_state &= ~KEY_3; // key3 抬起
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1)) {
			// key1 按下
			key_state |= KEY_1; // key1 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY2)) {
			// key2 按下
			key_state |= KEY_2; // key2 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY3)) {
			// key3 按下
			key_state |= KEY_3; // key3 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1_KEY2)) {
			// key1 key2 按下
			key_state |= KEY_1; // key1 按下
			key_state |= KEY_2; // key2 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1_KEY3)) {
			// key1 key3 按下
			key_state |= KEY_1; // key1 按下
			key_state |= KEY_3; // key3 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY2_KEY3)) {
			// key2 key3 按下
			key_state |= KEY_2; // key2 按下
			key_state |= KEY_3; // key3 按下
		} else if(IS_IN_RANGE(result, KEY_RANGE_ALL_DOWN)) {
			// key2 key3 按下
			key_state |= KEY_1; // key1 按下
			key_state |= KEY_2; // key2 按下
			key_state |= KEY_3; // key3 按下
		}
		
		// 比较当前和上一次的状态，找到不同，
		
////////// 上一次	
// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		1	 0
		
////////// 当前	
// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		0	 1
		
//		key_state ^ last_state
//last_state	1		1	 1
//key_state		0		0	 0
//				1		1	 1
		
		uint8_t diff = key_state ^ last_state;
		
		// 只在不同的时候干活
		if(diff) {
			// key1着手
			if(diff & KEY_1) {
				// 结果不为0， 变化了
				if(key_state & KEY_1) {
					// 按下
					ADKey_on_down(0);
				} else {
					// 抬起
					ADKey_on_up(0);
				}
			}
			
			// key2着手
			if(diff & KEY_2) {
				// 结果不为0， 变化了
				if(key_state & KEY_2) {
					// 按下
					ADKey_on_down(1);
				} else {
					// 抬起
					ADKey_on_up(1);
				}
			}
			
			// key3着手
			if(diff & KEY_3) {
				// 结果不为0， 变化了
				if(key_state & KEY_3) {
					// 按下
					ADKey_on_down(2);
				} else {
					// 抬起
					ADKey_on_up(2);
				}
			}
			
			// 更新状态
			last_state = key_state;
		}
		
		///key1 和 key2 按下，触发 key1 和 key2 的down事件
		
		i = 0;
		sum = 0;
		min_value = 4096;
		max_value = 0;
	}
	
	if(adv_cnt++ >= DELAY) { // 20ms进入一次
		adv_cnt = 0;
		///////////// 使用 按下 抬起状态， 做高级的事件判断 ////////////////////
		static uint8_t key1_down_cnt = 0;// 按下的计数，按下的时长
		static uint8_t key1_is_long_click = 0; // 触发长按标记 1 个 bit
		static uint8_t key1_up_time	= 0; //抬起的次数 2 个 bit
		static uint8_t key1_up_cnt = 0;// 抬起的计数，抬起的时长
		
		//// key1 按键

		///// 长按 ，用户按下 时间持续了 1s，就是长按
		///// 1) 只有第一次是长按   <<< 
		///// 2) 长按事件触发太频繁
		///// 单击，
		///// 1) 频繁调用问题 （按下后抬起）
		///// 2) 和长按冲突
		
		////// 双击
		/////
		
		//// 当 按键被按下后，又抬起了，过后的一段时间，没有再次的按下抬起，就认为是单击事件
		
		if(key_state & KEY_1) {
			///////////// 按下
			// 计数 10 次就是1s
			key1_down_cnt++;
			
			/******************* 长按 ************************/
			if(key1_down_cnt >= LONG_DELAY && key1_is_long_click == 0) { // 10 * 100ms >= 1s
				// 我已经触发了长按
				key1_is_long_click = 1;
				// 触发了长按
				ADKey_on_long_click(0);
			}
			
		} else {
			///////////// 抬起
			
			if(key1_up_time == 1) {
				// 用户抬起过一次
				key1_up_cnt++;
				
				if(key1_up_cnt > CLICK_DELAY) { //200ms没有再次操作
					key1_up_time = 0;
					key1_up_cnt = 0;
					// 触发单击
					ADKey_on_click(0);
				}
			}
			
			
			/******************* 单击 或 双击 ************************/
			if(key1_down_cnt > 0 && key1_is_long_click == 0) { // 按下后抬起
				if(key1_up_time == 0) {
					// 用户第一次抬起
					key1_up_cnt = 0;
				}
				
				// 不一定要触发单击
				// 等待下一次的单击，拼凑成双击
				// 记录 抬起的次数
				key1_up_time++;
				
//				if(key1_up_time == 1) {
//					//用户按下抬起 1 次， 单击
//					key1_up_time = 0;
//					/********* 单击 *******/
//					ADKey_on_click(0);
//					
//				} 
				if(key1_up_time == 2) {
					//用户按下抬起 2 次， 双击
					key1_up_time = 0;
					key1_up_cnt = 0;
					/********* 双击 *******/
					ADKey_on_double_click(0);
				}
			}
			
			/******************* 长按 ************************/
			key1_down_cnt = 0;
			// 重置长按标记
			key1_is_long_click = 0;
			
		}
	
	}
}


//void ADKey_adv() { // 100ms
//	///////////// 使用 按下 抬起状态， 做高级的事件判断 ////////////////////
//	
//	//// key1 按键
//	
//	
//	///// 长按 ，用户按下 时间持续了 1s，就是长按
//	
//	//按下
//	if(key_state & KEY_1) {
//	}
//}