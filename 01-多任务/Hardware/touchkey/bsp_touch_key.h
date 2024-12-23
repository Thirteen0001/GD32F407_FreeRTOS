#ifndef __BSP_TOUCH_KEY_H__
#define __BSP_TOUCH_KEY_H__

#include "board_config.h"


#define TK_WR(a, r, d, l)	lib_I2C0_write(a,r,d,l)
#define TK_RD(a, r, d, l)	lib_I2C0_read(a,r,d,l)



/*********************************************************************************
宏定义说明
********************************************************************************/
#define SPECIAL_APP //需要特殊配置的运用
typedef enum //定义数据返回类型
{
    UNDONE = 0x00,
    DONE = 0x01
} Complete_Status;
#define SDA_OUT_OR_IN TRISAbits.TRISA0 //定义 SDA 输入输出方向
#define SCL_OUT_OR_IN TRISAbits.TRISA2 //定义 SCL 输入输出方向
#define SDA LATAbits.LATA0 //定义 SDA 数据线输出
#define SDA_IN PORTAbits.RA0 //定义 SDA 数据线读取
#define SCL LATAbits.LATA2 //定义 SDA 数据线输出
#define SC12B_ADDR 	0x40 //ASEL 引脚悬空，设备的地址
#define SC12B_ADDR1 0x42 //ASEL 引脚为低电平，设备的地址
#define SC12B_ADDR2 0x44 //ASEL 引脚为高电平，设备的地址
//////////////////////////  Register ADDR////////////////////////////////////////////////////////////////////////////
#define SenSet0_REG 0x00 //CIN4 通道灵敏度的设置地址
#define SenSetCOM_REG 0x01 //其他通道灵敏度的设置地址
#define CTRL0_REG 0x02 //CTRL0 控制寄存器设置地址
#define CTRL1_REG 0x03 //CTRL1 控制寄存器设置地址
#define Output_REG 0x08 //触摸状态寄存器输出地址
#define SAMP_REG 0x0A //触摸数据值存器输出地址
#define RTM0 0 //3 个采样周期有效，1 个采样周期判断无效
#define RTM1 1 //4 个采样周期有效，2 个采样周期判断无效
#define RTM2 2 //5 个采样周期有效，3 个采样周期判断无效
#define RTM3 3 //6 个采样周期有效，4 个采样周期判断无效
#define KVF_STOP_CORREC (1u<<2) // 按键有效，触摸不校准
#define KVF_50S_CORREC (0u<<2) // 按下有效后，50S 开始校准
#define HOLD (1u<<3) //基线保持不校准
#define NOTHOLD (0u<<3) //基线持续校准
#define SLPCYC_LGT (0u<<5) //无穷大
#define SLPCYC_0R5T (1u<<5) //休眠后采样间隔 60MS
#define SLPCYC_1R5T (2u<<5) //休眠后采样间隔 180MS
#define SLPCYC_2R5T (3u<<5) //休眠后采样间隔 300MS
#define SLPCYC_3R5T (4u<<5) //休眠后采样间隔 420MS
#define SLPCYC_4R5T (5u<<5) //休眠后采样间隔 540MS
#define SLPCYC_5R5T (6u<<5) //休眠后采样间隔 660MS
#define SLPCYC_6R5T (7u<<5) //休眠后采样间隔 780MS
#define FAST_TO_SLEEP (1u<<4) //快速进入休眠
#define SLOW_TO_SLEEP (0u<<4) // 75S 进入休眠





void tk_init();


extern void tk_on_down(uint8_t i);
extern void tk_on_up(uint8_t i);



#endif