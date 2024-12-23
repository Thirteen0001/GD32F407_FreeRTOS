#include "MatrixKeys.h"

#define  DOWN   0
#define  UP		1

// 初始化
void MK_init() {
	// 行 推挽输出
	// 时钟初始化
	rcu_periph_clock_enable(RCU_GPIOE);
	// GPIO模式：推挽输出
	gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
	// 输出选项设置
	gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
	
	// 列 上拉输入
	// 时钟初始化
	rcu_periph_clock_enable(RCU_GPIOE);
	// 配置GPIO模式：输入模式，上拉
	gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

#define ROW1(state) gpio_bit_write(GPIOE, GPIO_PIN_8, state);
#define ROW2(state) gpio_bit_write(GPIOE, GPIO_PIN_9, state);
#define ROW3(state) gpio_bit_write(GPIOE, GPIO_PIN_10, state);
#define ROW4(state) gpio_bit_write(GPIOE, GPIO_PIN_11, state);


void row_output(u8 r) {
	ROW1(r == 0 ? 0 : 1);
	ROW2(r == 1 ? 0 : 1);
	ROW3(r == 2 ? 0 : 1);
	ROW4(r == 3 ? 0 : 1);
	
//	// 行引脚
//	ROW1 = r == 0 ? 0 : 1; 
//	ROW2 = r == 1 ? 0 : 1; 
//	ROW3 = r == 2 ? 0 : 1; 
//	ROW4 = r == 3 ? 0 : 1; 
}

#define COL1 	gpio_input_bit_get(GPIOE, GPIO_PIN_12)
#define COL2 	gpio_input_bit_get(GPIOE, GPIO_PIN_13)
#define COL3 	gpio_input_bit_get(GPIOE, GPIO_PIN_14)
#define COL4 	gpio_input_bit_get(GPIOE, GPIO_PIN_15)


int col_state(u8 c) { // 列的状态
	if (c == 0) return COL1; // 是返回引脚的值，是1或0
	if (c == 1) return COL2; 
	if (c == 2) return COL3; 
	if (c == 3) return COL4; 
	
	return 0;
}


static u16 states = 0xffff; 

// 判断刚才是否抬起或按下
#define 	IS_KEY_UP(r, c)  		(((states >> (r * 4 + c)) & 1) == UP) // 判断states第几位为1
#define 	IS_KEY_DOWN(r, c)  		(((states >> (r * 4 + c)) & 1) == DOWN) // 判断states第几位为0
// 设置按下或抬起
#define 	SET_KEY_UP(r, c)  		states |= (1 << (r * 4 + c))
#define 	SET_KEY_DOWN(r, c)  	states &= ~(1 << (r * 4 + c))

// ================ 只是判断states的内容
// 获取第row行第col列的状态是否为抬起，是抬起返回1，不是返回0
u8 MK_is_keyup(u8 r, u8 c) {
	return IS_KEY_UP(r, c);
}
// 获取第row行第col列的状态是否为按下，是按下返回1，不是返回0
u8 MK_is_keydown(u8 r, u8 c) {
	return IS_KEY_DOWN(r, c);
}


// 扫描按键
void MK_scan(u16 * ks) {
	u8 r, c;
	
	for (r = 0; r < 4; r++) { // 行， 4行 r = 0, 1, 2, 3
		__NOP(); // 可选的延时
		
		// 函数，设置第几行的引脚为0
		row_output(r);
		for (c = 0; c < 4; c++) { // 列，4列 c = 0, 1, 2, 3
			// 函数，获取第几列引脚的值
			if (col_state(c) == DOWN && IS_KEY_UP(r, c)) {
				// printf("第 %d 行第 %d 列按下\n", (int)(r+1), (int)(c+1));
				
				#if USE_KEYDOWN
				// 按下的回调函数
				MK_on_keydown(r, c);
				#endif 
	
				SET_KEY_DOWN(r, c); // 更新状态
			}  else if (col_state(c) == UP && IS_KEY_DOWN(r, c)) {
				// printf("第 %d 行第 %d 列抬起\n", (int)(r+1), (int)(c+1));
				#if USE_KEYUP
				MK_on_keyup(r, c);
				#endif
				
				SET_KEY_UP(r, c); // 更新状态
			}
			
		}
		
	}
	
	// 循环外面
	if (ks != NULL) {
		*ks = states;
	
	}
	
}