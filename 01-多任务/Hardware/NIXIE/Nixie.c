#include "Nixie.h"

static void GPIO_init(uint32_t rcu, uint32_t port, uint32_t pin) {
    rcu_periph_clock_enable(rcu);
    gpio_mode_set(port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pin);
    gpio_output_options_set(port, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, pin);
}


// 初始化
void Nixie_init() {
    GPIO_init(NIX_DI_RCU, NIX_DI_GPIO);
    GPIO_init(NIX_RCK_RCU, NIX_RCK_GPIO);
    GPIO_init(NIX_SCK_RCU, NIX_SCK_GPIO);
}

// 索引对应表格参见：
// https://www.yuque.com/icheima/stc8h/kmz2mllvxs1uvdfy#lLhhp
// 下标0~9，对应显示内容也是0~9，其它内容需要查表
static u8 LED_TABLE[] =
{
    // 0 	1	 2	-> 9	(索引012...9)
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,
    // 0.  1. 2. -> 9.	(索引10,11,12....19)
    0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,
    // . -						(索引20,21)
    0x7F, 0xBF,
    // AbCdEFHJLPqU		(索引22,23,24....33)
    0x88,0x83,0xC6,0xA1,0x86,0x8E,0x89,0xF1,0xC7,0x8C,0x98,0xC1
};

#define RCK_ACTION() {gpio_bit_write(NIX_RCK_GPIO, SET); __NOP(); gpio_bit_write(NIX_RCK_GPIO, RESET); __NOP();}

void Nixie_output(u8 dat) { // data是关键字不能写
    char i;  // 有-操作，用char
    // 内容
    for(i = 7; i >= 0; i--) { // i = 7~0
        // NIX_DI = (dat >> i) & 1;
		
		gpio_bit_write(NIX_DI_GPIO, ((dat >> i) & 1) ? SET : RESET);

        // 移位  0 -> 1
        gpio_bit_write(NIX_SCK_GPIO, RESET);
        __NOP();
        gpio_bit_write(NIX_SCK_GPIO, SET);
        __NOP();
    }
}

// num: 控制显示的什么内容
// idx: 控制显示哪几个显示
void Nixie_show(u8 num, u8 idx) {
    Nixie_output(num); // 内容

    Nixie_output(idx); // 位置

    // 锁存，更新电路  1 -> 0
    RCK_ACTION();
}


// num 对应的内容在数组的位置(索引)，配合自定义码表
// 除了0~9，刚好和下标一致，其它的内容，需要查表
// idx  显示在屏幕上的位置(1 -> 8)，只有1个数码管显示
void Nixie_display(u8 num, u8 idx) {
    Nixie_show(LED_TABLE[num],  1 << (idx - 1));
}