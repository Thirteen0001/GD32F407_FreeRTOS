#ifndef __BSP_EC12_H__
#define __BSP_EC12_H__

#include "board_config.h"

void EC12_init();

// ������ת

// ���԰��º�̧��
// 1) �ж�
///// �����ж�

// 2) ɨ��
///// ɨ�� EC12_scan() --> Task


extern void EC12_on_down();
extern void EC12_on_up();

extern void EC12_on_turn_right();
extern void EC12_on_turn_left();



#endif