#ifndef __BSP_TOUCH_KEY_H__
#define __BSP_TOUCH_KEY_H__

#include "board_config.h"


#define TK_WR(a, r, d, l)	lib_I2C0_write(a,r,d,l)
#define TK_RD(a, r, d, l)	lib_I2C0_read(a,r,d,l)



/*********************************************************************************
�궨��˵��
********************************************************************************/
#define SPECIAL_APP //��Ҫ�������õ�����
typedef enum //�������ݷ�������
{
    UNDONE = 0x00,
    DONE = 0x01
} Complete_Status;
#define SDA_OUT_OR_IN TRISAbits.TRISA0 //���� SDA �����������
#define SCL_OUT_OR_IN TRISAbits.TRISA2 //���� SCL �����������
#define SDA LATAbits.LATA0 //���� SDA ���������
#define SDA_IN PORTAbits.RA0 //���� SDA �����߶�ȡ
#define SCL LATAbits.LATA2 //���� SDA ���������
#define SC12B_ADDR 	0x40 //ASEL �������գ��豸�ĵ�ַ
#define SC12B_ADDR1 0x42 //ASEL ����Ϊ�͵�ƽ���豸�ĵ�ַ
#define SC12B_ADDR2 0x44 //ASEL ����Ϊ�ߵ�ƽ���豸�ĵ�ַ
//////////////////////////  Register ADDR////////////////////////////////////////////////////////////////////////////
#define SenSet0_REG 0x00 //CIN4 ͨ�������ȵ����õ�ַ
#define SenSetCOM_REG 0x01 //����ͨ�������ȵ����õ�ַ
#define CTRL0_REG 0x02 //CTRL0 ���ƼĴ������õ�ַ
#define CTRL1_REG 0x03 //CTRL1 ���ƼĴ������õ�ַ
#define Output_REG 0x08 //����״̬�Ĵ��������ַ
#define SAMP_REG 0x0A //��������ֵ���������ַ
#define RTM0 0 //3 ������������Ч��1 �����������ж���Ч
#define RTM1 1 //4 ������������Ч��2 �����������ж���Ч
#define RTM2 2 //5 ������������Ч��3 �����������ж���Ч
#define RTM3 3 //6 ������������Ч��4 �����������ж���Ч
#define KVF_STOP_CORREC (1u<<2) // ������Ч��������У׼
#define KVF_50S_CORREC (0u<<2) // ������Ч��50S ��ʼУ׼
#define HOLD (1u<<3) //���߱��ֲ�У׼
#define NOTHOLD (0u<<3) //���߳���У׼
#define SLPCYC_LGT (0u<<5) //�����
#define SLPCYC_0R5T (1u<<5) //���ߺ������� 60MS
#define SLPCYC_1R5T (2u<<5) //���ߺ������� 180MS
#define SLPCYC_2R5T (3u<<5) //���ߺ������� 300MS
#define SLPCYC_3R5T (4u<<5) //���ߺ������� 420MS
#define SLPCYC_4R5T (5u<<5) //���ߺ������� 540MS
#define SLPCYC_5R5T (6u<<5) //���ߺ������� 660MS
#define SLPCYC_6R5T (7u<<5) //���ߺ������� 780MS
#define FAST_TO_SLEEP (1u<<4) //���ٽ�������
#define SLOW_TO_SLEEP (0u<<4) // 75S ��������





void tk_init();


extern void tk_on_down(uint8_t i);
extern void tk_on_up(uint8_t i);



#endif