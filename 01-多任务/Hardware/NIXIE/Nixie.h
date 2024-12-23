#ifndef __NIXIE_H__
#define __NIXIE_H__

#include "gd32f4xx.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

// ����Ĵ���
#define NIX_DI_RCU		RCU_GPIOD
#define NIX_DI_GPIO   	GPIOD, GPIO_PIN_0
// ����Ĵ���
#define NIX_RCK_RCU		RCU_GPIOD
#define NIX_RCK_GPIO  	GPIOD, GPIO_PIN_1
// ��λ�Ĵ���
#define NIX_SCK_RCU		RCU_GPIOD
#define NIX_SCK_GPIO  	GPIOD, GPIO_PIN_4


// ��ʼ��
void Nixie_init();

// num: ������ʾ��ʲô����
// idx: ������ʾ�ļ�����ʾ
void Nixie_show(u8 num, u8 idx);

// num ��Ӧ�������������λ��(����)������Զ������
// ����0~9���պú��±�һ�£����������ݣ���Ҫ���
// idx  ��ʾ����Ļ�ϵ�λ��(1 -> 8)��ֻ��1���������ʾ
void Nixie_display(u8 num, u8 idx);

#endif