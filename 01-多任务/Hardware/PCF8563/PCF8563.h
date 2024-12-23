#ifndef __PCF8563_H__
#define __PCF8563_H__

#include 	"gd32f4xx.h"
#include 	"I2C.h"

#define USE_ALARM	0    // 如果是1，定义 void PCF8563_on_alarm() 函数
#define USE_TIMER	0    // 如果是1，定义 void PCF8563_on_timer() 函数

// 声明
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

// 设备地址
#define		PCF8563_DEV_ADDR	(0xa2 >> 1)
// 存储地址(寄存器地址): 时间(秒)存储地址
#define		PCF8563_REG_SECOND	0x02

// 10进制数转BCD数：十位取出左移4位 + 个位 (得到BCD数)
#define WRITE_BCD(val) 	((val / 10) << 4) + (val % 10)
// BCD数转10进制数：将高4位乘以10 + 低四位 (得到10进制数)
#define READ_BCD(val) 	(val >> 4) * 10 + (val & 0x0F) 


// ==================日期时间=====================
typedef struct {
	u16 year; 
	u8 month;
	u8 day;
	u8 weekday;
	u8 hour;
	u8 minute;
	u8 second;
} Clock_t;

// PCF8563初始化
void PCF8563_init();

// 设置时间
void PCF8563_set_clock(Clock_t temp);

// 获取时间
void PCF8563_get_clock(Clock_t *temp);

// ==================闹钟=====================
typedef struct {
    // 设置分\时\天\周，如果为-1，禁用此项
    char minute ;
    char hour ;
    char day ;
    char weekday;
} Alarm_t;

// 设置闹钟
void PCF8563_set_alarm(Alarm_t alarm);
// 启用闹钟
void PCF8563_enable_alarm();
// 禁用闹钟Alarm
void PCF8563_disable_alarm();
// 清理闹钟标记
void PCF8563_alarm_clear_flag();


//=============================定时器
typedef enum { HZ4096 = 0, HZ64 = 1, HZ1 = 2, HZ1_60 = 3} TimerFreq;

// 启动定时器
void PCF8563_enable_timer();
// 禁用定时器
void PCF8563_disable_timer();
// 清除定时器标志位
void PCF8563_clear_timer();     
// 设置定时器，参数1：时钟频率 参数2：倒计时计算值，时间为：参数2/参数1
void PCF8563_set_timer(TimerFreq freq, u8 countdown);

#endif