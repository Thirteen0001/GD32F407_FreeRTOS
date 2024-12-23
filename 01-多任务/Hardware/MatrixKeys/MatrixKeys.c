#include "MatrixKeys.h"

#define  DOWN   0
#define  UP		1

// ��ʼ��
void MK_init() {
	// �� �������
	// ʱ�ӳ�ʼ��
	rcu_periph_clock_enable(RCU_GPIOE);
	// GPIOģʽ���������
	gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
	// ���ѡ������
	gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
	
	// �� ��������
	// ʱ�ӳ�ʼ��
	rcu_periph_clock_enable(RCU_GPIOE);
	// ����GPIOģʽ������ģʽ������
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
	
//	// ������
//	ROW1 = r == 0 ? 0 : 1; 
//	ROW2 = r == 1 ? 0 : 1; 
//	ROW3 = r == 2 ? 0 : 1; 
//	ROW4 = r == 3 ? 0 : 1; 
}

#define COL1 	gpio_input_bit_get(GPIOE, GPIO_PIN_12)
#define COL2 	gpio_input_bit_get(GPIOE, GPIO_PIN_13)
#define COL3 	gpio_input_bit_get(GPIOE, GPIO_PIN_14)
#define COL4 	gpio_input_bit_get(GPIOE, GPIO_PIN_15)


int col_state(u8 c) { // �е�״̬
	if (c == 0) return COL1; // �Ƿ������ŵ�ֵ����1��0
	if (c == 1) return COL2; 
	if (c == 2) return COL3; 
	if (c == 3) return COL4; 
	
	return 0;
}


static u16 states = 0xffff; 

// �жϸղ��Ƿ�̧�����
#define 	IS_KEY_UP(r, c)  		(((states >> (r * 4 + c)) & 1) == UP) // �ж�states�ڼ�λΪ1
#define 	IS_KEY_DOWN(r, c)  		(((states >> (r * 4 + c)) & 1) == DOWN) // �ж�states�ڼ�λΪ0
// ���ð��»�̧��
#define 	SET_KEY_UP(r, c)  		states |= (1 << (r * 4 + c))
#define 	SET_KEY_DOWN(r, c)  	states &= ~(1 << (r * 4 + c))

// ================ ֻ���ж�states������
// ��ȡ��row�е�col�е�״̬�Ƿ�Ϊ̧����̧�𷵻�1�����Ƿ���0
u8 MK_is_keyup(u8 r, u8 c) {
	return IS_KEY_UP(r, c);
}
// ��ȡ��row�е�col�е�״̬�Ƿ�Ϊ���£��ǰ��·���1�����Ƿ���0
u8 MK_is_keydown(u8 r, u8 c) {
	return IS_KEY_DOWN(r, c);
}


// ɨ�谴��
void MK_scan(u16 * ks) {
	u8 r, c;
	
	for (r = 0; r < 4; r++) { // �У� 4�� r = 0, 1, 2, 3
		__NOP(); // ��ѡ����ʱ
		
		// ���������õڼ��е�����Ϊ0
		row_output(r);
		for (c = 0; c < 4; c++) { // �У�4�� c = 0, 1, 2, 3
			// ��������ȡ�ڼ������ŵ�ֵ
			if (col_state(c) == DOWN && IS_KEY_UP(r, c)) {
				// printf("�� %d �е� %d �а���\n", (int)(r+1), (int)(c+1));
				
				#if USE_KEYDOWN
				// ���µĻص�����
				MK_on_keydown(r, c);
				#endif 
	
				SET_KEY_DOWN(r, c); // ����״̬
			}  else if (col_state(c) == UP && IS_KEY_DOWN(r, c)) {
				// printf("�� %d �е� %d ��̧��\n", (int)(r+1), (int)(c+1));
				#if USE_KEYUP
				MK_on_keyup(r, c);
				#endif
				
				SET_KEY_UP(r, c); // ����״̬
			}
			
		}
		
	}
	
	// ѭ������
	if (ks != NULL) {
		*ks = states;
	
	}
	
}