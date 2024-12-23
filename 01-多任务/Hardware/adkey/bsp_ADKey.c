#include "bsp_ADKey.h"


#define SAMPLE_TIME		50

/// ��ֵ�˲�  ��ֵ�˲�  
/// (ȡ�� - ���ֵ - ��Сֵ) / (�������� - 2)

// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		0	 0
// 0��ʾ̧��
// 1��ʾ����

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

// ��ǰ״̬
static uint8_t key_state = 0;

static uint8_t last_state = 0;

void ADkey_init() {

}


void ADKey_scan() {
	//ͨ��ADCȥ��ȡ ��ѹ���ж���һ������������
	static uint8_t i = 0;
	static uint32_t sum = 0;
	static uint16_t min_value = 4096; // ��Сֵ��һ������ֵ
	static uint16_t max_value = 0;	  // ���ֵ��һ����С��ֵ
	
	static uint8_t adv_cnt = 0;

	// �����Ĺ���
	
	/////////////// ��ȡ״̬�Ĺ��� ///////////////////////
	// 1000s --> 50�� ÿ20�εõ�һ�ν��
	if(i < SAMPLE_TIME) {
		i++;
		uint16_t value = lib_adc0_get(0);
		sum += value;
		// printf("adkey: %d\r\n", value);
		if(value > max_value) max_value = value;
		if(value < min_value) min_value = value;
	} else {
		// �õ�һ�ν��
		// �˲���Ľ��
		sum -= max_value;
		sum -= min_value;
		uint16_t result = sum / (SAMPLE_TIME - 2);
		
		//printf("result: %d\r\n", result);
		// ʹ���˲���Ľ�������߼�
		if(IS_IN_RANGE(result, KEY_RANGE_ALL_UP)) {
			// ����̧���
			key_state &= ~KEY_1; // key1 ̧��
			key_state &= ~KEY_2; // key2 ̧��
			key_state &= ~KEY_3; // key3 ̧��
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1)) {
			// key1 ����
			key_state |= KEY_1; // key1 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY2)) {
			// key2 ����
			key_state |= KEY_2; // key2 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY3)) {
			// key3 ����
			key_state |= KEY_3; // key3 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1_KEY2)) {
			// key1 key2 ����
			key_state |= KEY_1; // key1 ����
			key_state |= KEY_2; // key2 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY1_KEY3)) {
			// key1 key3 ����
			key_state |= KEY_1; // key1 ����
			key_state |= KEY_3; // key3 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_KEY2_KEY3)) {
			// key2 key3 ����
			key_state |= KEY_2; // key2 ����
			key_state |= KEY_3; // key3 ����
		} else if(IS_IN_RANGE(result, KEY_RANGE_ALL_DOWN)) {
			// key2 key3 ����
			key_state |= KEY_1; // key1 ����
			key_state |= KEY_2; // key2 ����
			key_state |= KEY_3; // key3 ����
		}
		
		// �Ƚϵ�ǰ����һ�ε�״̬���ҵ���ͬ��
		
////////// ��һ��	
// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		1	 0
		
////////// ��ǰ	
// bit 7 6 5 4 3 	2 		1 	 0
//				 	key3  key2	 key1
//     0 0 0 0 0 	0		0	 1
		
//		key_state ^ last_state
//last_state	1		1	 1
//key_state		0		0	 0
//				1		1	 1
		
		uint8_t diff = key_state ^ last_state;
		
		// ֻ�ڲ�ͬ��ʱ��ɻ�
		if(diff) {
			// key1����
			if(diff & KEY_1) {
				// �����Ϊ0�� �仯��
				if(key_state & KEY_1) {
					// ����
					ADKey_on_down(0);
				} else {
					// ̧��
					ADKey_on_up(0);
				}
			}
			
			// key2����
			if(diff & KEY_2) {
				// �����Ϊ0�� �仯��
				if(key_state & KEY_2) {
					// ����
					ADKey_on_down(1);
				} else {
					// ̧��
					ADKey_on_up(1);
				}
			}
			
			// key3����
			if(diff & KEY_3) {
				// �����Ϊ0�� �仯��
				if(key_state & KEY_3) {
					// ����
					ADKey_on_down(2);
				} else {
					// ̧��
					ADKey_on_up(2);
				}
			}
			
			// ����״̬
			last_state = key_state;
		}
		
		///key1 �� key2 ���£����� key1 �� key2 ��down�¼�
		
		i = 0;
		sum = 0;
		min_value = 4096;
		max_value = 0;
	}
	
	if(adv_cnt++ >= DELAY) { // 20ms����һ��
		adv_cnt = 0;
		///////////// ʹ�� ���� ̧��״̬�� ���߼����¼��ж� ////////////////////
		static uint8_t key1_down_cnt = 0;// ���µļ��������µ�ʱ��
		static uint8_t key1_is_long_click = 0; // ����������� 1 �� bit
		static uint8_t key1_up_time	= 0; //̧��Ĵ��� 2 �� bit
		static uint8_t key1_up_cnt = 0;// ̧��ļ�����̧���ʱ��
		
		//// key1 ����

		///// ���� ���û����� ʱ������� 1s�����ǳ���
		///// 1) ֻ�е�һ���ǳ���   <<< 
		///// 2) �����¼�����̫Ƶ��
		///// ������
		///// 1) Ƶ���������� �����º�̧��
		///// 2) �ͳ�����ͻ
		
		////// ˫��
		/////
		
		//// �� ���������º���̧���ˣ������һ��ʱ�䣬û���ٴεİ���̧�𣬾���Ϊ�ǵ����¼�
		
		if(key_state & KEY_1) {
			///////////// ����
			// ���� 10 �ξ���1s
			key1_down_cnt++;
			
			/******************* ���� ************************/
			if(key1_down_cnt >= LONG_DELAY && key1_is_long_click == 0) { // 10 * 100ms >= 1s
				// ���Ѿ������˳���
				key1_is_long_click = 1;
				// �����˳���
				ADKey_on_long_click(0);
			}
			
		} else {
			///////////// ̧��
			
			if(key1_up_time == 1) {
				// �û�̧���һ��
				key1_up_cnt++;
				
				if(key1_up_cnt > CLICK_DELAY) { //200msû���ٴβ���
					key1_up_time = 0;
					key1_up_cnt = 0;
					// ��������
					ADKey_on_click(0);
				}
			}
			
			
			/******************* ���� �� ˫�� ************************/
			if(key1_down_cnt > 0 && key1_is_long_click == 0) { // ���º�̧��
				if(key1_up_time == 0) {
					// �û���һ��̧��
					key1_up_cnt = 0;
				}
				
				// ��һ��Ҫ��������
				// �ȴ���һ�εĵ�����ƴ�ճ�˫��
				// ��¼ ̧��Ĵ���
				key1_up_time++;
				
//				if(key1_up_time == 1) {
//					//�û�����̧�� 1 �Σ� ����
//					key1_up_time = 0;
//					/********* ���� *******/
//					ADKey_on_click(0);
//					
//				} 
				if(key1_up_time == 2) {
					//�û�����̧�� 2 �Σ� ˫��
					key1_up_time = 0;
					key1_up_cnt = 0;
					/********* ˫�� *******/
					ADKey_on_double_click(0);
				}
			}
			
			/******************* ���� ************************/
			key1_down_cnt = 0;
			// ���ó������
			key1_is_long_click = 0;
			
		}
	
	}
}


//void ADKey_adv() { // 100ms
//	///////////// ʹ�� ���� ̧��״̬�� ���߼����¼��ж� ////////////////////
//	
//	//// key1 ����
//	
//	
//	///// ���� ���û����� ʱ������� 1s�����ǳ���
//	
//	//����
//	if(key_state & KEY_1) {
//	}
//}