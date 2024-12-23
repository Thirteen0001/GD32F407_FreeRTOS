#ifndef __MATRIX_KEYS__
#define __MATRIX_KEYS__

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

// 1 �û���Ҫ����MK_on_keydown����   0 ���趨��
#define USE_KEYDOWN 0  

// 1 �û���Ҫ����MK_on_keyup����   0 ���趨��
#define USE_KEYUP 0


// ֻ�����������û�ʹ�õ�ʱ�� �򿪺궨��Ŀ��أ��ٶ��庯��
// ���µĻص�����
void MK_on_keydown(u8 row, u8 col);

// ̧��Ļص�����
void MK_on_keyup(u8 row, u8 col);


// ��ʼ��
void MK_init();

// ɨ�谴��
void MK_scan(u16 * ks);


// ��ȡ��row�е�col�е�״̬�Ƿ�Ϊ̧����̧�𷵻�1�����Ƿ���0
u8 MK_is_keyup(u8 row, u8 col);
// ��ȡ��row�е�col�е�״̬�Ƿ�Ϊ���£��ǰ��·���1�����Ƿ���0
u8 MK_is_keydown(u8 row, u8 col);

#endif