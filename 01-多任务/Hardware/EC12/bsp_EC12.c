#include "bsp_EC12.h"





void EC12_init() {
	
	printf("EC12 init\r\n");
}


/// A �ж�
void EC12_A_EXTI_FUNC() {
	/// �� A�������½���ʱ��B����� �ͣ� ������ת
	/// �� A�������½���ʱ��B����� �ߣ� ���Ƿ�ת
	
	static uint32_t last_time = 0;
	static uint8_t last_a_state = SET;
	
//	uint32_t current_time = CURRENT_TICK_MS();
//	if(current_time - last_time < EC12_DELAY){
//		return;
//	}
//	last_time = current_time;
	
	uint8_t current_a_state = EC12_A_STATE();
	if(SET == last_a_state && RESET == current_a_state) {
		// �½���
		last_a_state = current_a_state;
	
		uint8_t current = EC12_B_STATE();
		if(RESET == current) {
			// ��ת
			EC12_on_turn_left();
		} else {
			// ��ת
			EC12_on_turn_right();
		}
		
	} else if(RESET == last_a_state && SET == current_a_state) {
		// ������
		last_a_state = current_a_state;
		
		uint8_t current = EC12_B_STATE();
		if(SET == current) {
			// ��ת
			EC12_on_turn_left();
		} else {
			// ��ת
			EC12_on_turn_right();
		}
	}
	
}


/// D�ж�
void EC12_D_EXTI_FUNC() {
	static FlagStatus last = SET;
	static uint32_t last_time = 0;
	
	uint32_t current_time = CURRENT_TICK_MS();
	if(current_time - last_time < EC12_DELAY) {
		return;
	}
	last_time = current_time;
	
	// �ж�
	uint8_t current = EC12_D_STATE();
	if(SET == current && RESET == last) {
		// ��ǰ�ߵ�ƽ
		last = current;
		// ̧��
		EC12_on_up();
	} else if(RESET == current && SET == last) {
		// ����
		last = current;
		
		EC12_on_down();
	}
}
