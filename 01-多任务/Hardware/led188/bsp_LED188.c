#include "bsp_LED188.h"



#define PIN1_OUT(val)	bsp_gpio_out(PIN1_RCU, PIN1_PIN);bsp_gpio_write(PIN1_PIN, (val) ? SET : RESET)
#define PIN2_OUT(val)	bsp_gpio_out(PIN2_RCU, PIN2_PIN);bsp_gpio_write(PIN2_PIN, (val) ? SET : RESET)
#define PIN3_OUT(val)	bsp_gpio_out(PIN3_RCU, PIN3_PIN);bsp_gpio_write(PIN3_PIN, (val) ? SET : RESET)
#define PIN4_OUT(val)	bsp_gpio_out(PIN4_RCU, PIN4_PIN);bsp_gpio_write(PIN4_PIN, (val) ? SET : RESET)
#define PIN5_OUT(val)	bsp_gpio_out(PIN5_RCU, PIN5_PIN);bsp_gpio_write(PIN5_PIN, (val) ? SET : RESET)

#define PIN1_IN()		bsp_gpio_in(PIN1_RCU, PIN1_PIN)
#define PIN2_IN()		bsp_gpio_in(PIN2_RCU, PIN2_PIN)
#define PIN3_IN()		bsp_gpio_in(PIN3_RCU, PIN3_PIN)
#define PIN4_IN()		bsp_gpio_in(PIN4_RCU, PIN4_PIN)
#define PIN5_IN()		bsp_gpio_in(PIN5_RCU, PIN5_PIN)

#define ALL_IN()		PIN1_IN();PIN2_IN();PIN3_IN();PIN4_IN();PIN5_IN()


static uint32_t state = 0x00; //������

#define A3	(1 << 0)
#define B3	(1 << 1)
#define C3	(1 << 2)
#define D3	(1 << 3)
#define E3	(1 << 4)
#define F3	(1 << 5)
#define G3	(1 << 6)

#define A2	(1 << 7)
#define B2	(1 << 8)
#define C2	(1 << 9)
#define D2	(1 << 10)
#define E2	(1 << 11)
#define F2	(1 << 12)
#define G2	(1 << 13)

#define B1	(1 << 14)
#define C1	(1 << 15)

#define L1	(1 << 16)
#define L2	(1 << 17)

static uint8_t table[] = {
	0x3F, //0
	0x06, //1
	0x5B, //2
	0x4F, //3
	0x66, //4
	0x6D, //5
	0x7D, //6
	0x07, //7
	0x7F, //8
	0x6F, //9
};

void LED188_init() {
	// �������Ÿ���
	bsp_gpio_in(PIN1_RCU, PIN1_PIN);
	bsp_gpio_in(PIN2_RCU, PIN2_PIN);
	bsp_gpio_in(PIN3_RCU, PIN3_PIN);
	bsp_gpio_in(PIN4_RCU, PIN4_PIN);
	bsp_gpio_in(PIN5_RCU, PIN5_PIN);
}

void LED188_set_num(uint8_t num) {
	if(num > 100) return;
	
	if(num == 100) {
		// ��
		/// 1. ���
		state &= ~B1;
		state &= ~C1;
		/// 2. ��ʾ
		state |= B1;
		state |= C1;
		
		// ʮ 
		/// 1. ���
		state &= ~A2;
		state &= ~B2;
		state &= ~C2;
		state &= ~D2;
		state &= ~E2;
		state &= ~F2;
		state &= ~G2;
		/// 2. ��ʾ 0
		state |= A2;
		state |= B2;
		state |= C2;
		state |= D2;
		state |= E2;
		state |= F2;
		
		// ��  
		/// 1. ���
		state &= ~A3;
		state &= ~B3;
		state &= ~C3;
		state &= ~D3;
		state &= ~E3;
		state &= ~F3;
		state &= ~G3;
		/// 2. ��ʾ 0 
		state |= A3;
		state |= B3;
		state |= C3;
		state |= D3;
		state |= E3;
		state |= F3;
	} else {
		// �� 
		// ��ղ���
		state &= ~B1;
		state &= ~C1;
		
		// ʮ 
		uint8_t shi = num / 10;
		
		/// 1. ���
		state &= ~A2;
		state &= ~B2;
		state &= ~C2;
		state &= ~D2;
		state &= ~E2;
		state &= ~F2;
		state &= ~G2;
		/// 2. ��ʾ shi
		if(shi != 0) state |= (table[shi] << 7);
		
		// ��  
		uint8_t ge = num % 10;
		
		/// 1. ���
		state &= ~A3;
		state &= ~B3;
		state &= ~C3;
		state &= ~D3;
		state &= ~E3;
		state &= ~F3;
		state &= ~G3;
		/// 2. ��ʾ ?
		state |= table[ge];
	}
	
}

void LED188_charge(uint8_t enable) {
	if(enable) {
		// L1 �����Ѷ�Ӧ��bitλ��Ϊ1
		state |= L1;
	} else {
		// L1 �𣬰Ѷ�Ӧ��bitλ��Ϊ0
		state &= ~L1;
	}
	
}

void LED188_percent(uint8_t enable) {
	if(enable) {
		// L2 �����Ѷ�Ӧ��bitλ��Ϊ1
		state |= L2;
	} else {
		// L2 �𣬰Ѷ�Ӧ��bitλ��Ϊ0
		state &= ~L2;
	}
}


void LED188_display() {
	static uint8_t i = 0;
	// ����ɨ�����
	if(i == 0) {
		// all ���裬 ����1 �ߣ��жϵ��Ƿ���������������õ͵�ƽ
		ALL_IN();
		PIN1_OUT(1);
		if(state & A3) {PIN2_OUT(0);}
		if(state & C3) {PIN3_OUT(0);}
		if(state & E3) {PIN4_OUT(0);}
	} else if(i == 1) {
		// all ���裬 ����2 �ߣ��ж��Ƿ���������������õ͵�ƽ
		ALL_IN();
		PIN2_OUT(1);
		if(state & B3) {PIN1_OUT(0);}
		if(state & A2) {PIN3_OUT(0);}
		if(state & C1) {PIN4_OUT(0);}
		if(state & L2) {PIN5_OUT(0);}
	} else if(i == 2) {
		// all ���裬 ����3 �ߣ��ж��Ƿ���������������õ͵�ƽ
		ALL_IN();
		PIN3_OUT(1);
		if(state & D3) {PIN1_OUT(0);}
		if(state & B2) {PIN2_OUT(0);}
		if(state & B1) {PIN4_OUT(0);}
		if(state & L1) {PIN5_OUT(0);}
	} else if(i == 3) {
		// all ���裬 ����4 �ߣ��ж��Ƿ���������������õ͵�ƽ
		ALL_IN();
		PIN4_OUT(1);
		if(state & F3) {PIN1_OUT(0);}
		if(state & D2) {PIN2_OUT(0);}
		if(state & C2) {PIN3_OUT(0);}
	} else if(i == 4) {
		// all ���裬 ����5 �ߣ��ж��Ƿ���������������õ͵�ƽ
		ALL_IN();
		PIN5_OUT(1);
		if(state & G3) {PIN1_OUT(0);}
		if(state & E2) {PIN2_OUT(0);}
		if(state & F2) {PIN3_OUT(0);}
		if(state & G2) {PIN4_OUT(0);}
	} 
	i++;
	if(i == 5) {
		i = 0;
	}
}