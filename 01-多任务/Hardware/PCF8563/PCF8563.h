#ifndef __PCF8563_H__
#define __PCF8563_H__

#include 	"gd32f4xx.h"
#include 	"I2C.h"

#define USE_ALARM	0    // �����1������ void PCF8563_on_alarm() ����
#define USE_TIMER	0    // �����1������ void PCF8563_on_timer() ����

// ����
void PCF8563_on_alarm();
void PCF8563_on_timer();

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#define  I2C_WriteNbyte(a, b, c, d)  	I2C0_write(a, b, c, d)
#define  I2C_ReadNbyte(a, b, c, d)  	I2C0_read(a, b, c, d)

// �豸��ַ
#define		PCF8563_DEV_ADDR	(0xa2 >> 1)
// �洢��ַ(�Ĵ�����ַ): ʱ��(��)�洢��ַ
#define		PCF8563_REG_SECOND	0x02

// 10������תBCD����ʮλȡ������4λ + ��λ (�õ�BCD��)
#define WRITE_BCD(val) 	((val / 10) << 4) + (val % 10)
// BCD��ת10������������4λ����10 + ����λ (�õ�10������)
#define READ_BCD(val) 	(val >> 4) * 10 + (val & 0x0F) 


// ==================����ʱ��=====================
typedef struct {
	u16 year; 
	u8 month;
	u8 day;
	u8 weekday;
	u8 hour;
	u8 minute;
	u8 second;
} Clock_t;

// PCF8563��ʼ��
void PCF8563_init();

// ����ʱ��
void PCF8563_set_clock(Clock_t temp);

// ��ȡʱ��
void PCF8563_get_clock(Clock_t *temp);

// ==================����=====================
typedef struct {
    // ���÷�\ʱ\��\�ܣ����Ϊ-1�����ô���
    char minute ;
    char hour ;
    char day ;
    char weekday;
} Alarm_t;

// ��������
void PCF8563_set_alarm(Alarm_t alarm);
// ��������
void PCF8563_enable_alarm();
// ��������Alarm
void PCF8563_disable_alarm();
// �������ӱ��
void PCF8563_alarm_clear_flag();


//=============================��ʱ��
typedef enum { HZ4096 = 0, HZ64 = 1, HZ1 = 2, HZ1_60 = 3} TimerFreq;

// ������ʱ��
void PCF8563_enable_timer();
// ���ö�ʱ��
void PCF8563_disable_timer();
// �����ʱ����־λ
void PCF8563_clear_timer();     
// ���ö�ʱ��������1��ʱ��Ƶ�� ����2������ʱ����ֵ��ʱ��Ϊ������2/����1
void PCF8563_set_timer(TimerFreq freq, u8 countdown);

#endif