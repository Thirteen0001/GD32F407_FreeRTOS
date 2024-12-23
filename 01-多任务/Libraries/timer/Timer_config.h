#ifndef __TIMER_CONFIG_H___
#define __TIMER_CONFIG_H___

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>


#define	USE_LIB_TIMER_0		0
#define	USE_LIB_TIMER_1		0
#define	USE_LIB_TIMER_2		0
#define	USE_LIB_TIMER_3		0
#define	USE_LIB_TIMER_4		0
#define	USE_LIB_TIMER_5		1
#define	USE_LIB_TIMER_6		0
#define	USE_LIB_TIMER_7		0
#define	USE_LIB_TIMER_8		0
#define	USE_LIB_TIMER_9		0
#define	USE_LIB_TIMER_10	0
#define	USE_LIB_TIMER_11	0
#define	USE_LIB_TIMER_12	0
#define	USE_LIB_TIMER_13	0


/*****************************************/
/************* TIMER0 Config *************/
/*****************************************/
#if USE_LIB_TIMER_0

#define USE_LIB_TIMER0_CH0_P	1
#define USE_LIB_TIMER0_CH0_N	1
#define USE_LIB_TIMER0_CH1_P	1
#define USE_LIB_TIMER0_CH1_N	1
#define USE_LIB_TIMER0_CH2_P	1
#define USE_LIB_TIMER0_CH2_N	1
#define USE_LIB_TIMER0_CH3		1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER0_PRESCALER		10
#define TIMER0_FREQ					500

/********** Timer0 CH0 *********/
///// PA8, PE9
#if USE_LIB_TIMER0_CH0_P
#define TIMER0_CH0_P_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH0_P_GPIO_PORT	GPIOE
#define TIMER0_CH0_P_GPIO_PIN		GPIO_PIN_9
#endif
///// PA7 ON, PB13 ON, PE8 ON
#if USE_LIB_TIMER0_CH0_N
#define TIMER0_CH0_N_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH0_N_GPIO_PORT	GPIOE
#define TIMER0_CH0_N_GPIO_PIN		GPIO_PIN_8
#endif

/********** Timer0 CH1 *********/
// PA9,PE11
#if USE_LIB_TIMER0_CH1_P
#define TIMER0_CH1_P_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH1_P_GPIO_PORT	GPIOE
#define TIMER0_CH1_P_GPIO_PIN		GPIO_PIN_11
#endif
// PB0,PB14,PE1,PE10
#if USE_LIB_TIMER0_CH1_N
#define TIMER0_CH1_N_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH1_N_GPIO_PORT	GPIOE
#define TIMER0_CH1_N_GPIO_PIN		GPIO_PIN_10
#endif

/********** Timer0 ch2 *********/
// PA10,PE13
#if USE_LIB_TIMER0_CH2_P
#define TIMER0_CH2_P_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH2_P_GPIO_PORT	GPIOE
#define TIMER0_CH2_P_GPIO_PIN		GPIO_PIN_13
#endif
// PB1,PB15,PE12
#if USE_LIB_TIMER0_CH2_N
#define TIMER0_CH2_N_GPIO_RCU		RCU_GPIOE
#define TIMER0_CH2_N_GPIO_PORT	GPIOE
#define TIMER0_CH2_N_GPIO_PIN		GPIO_PIN_12
#endif

/********** timer0 ch3 *********/
// PA11, PE14
#if USE_LIB_TIMER0_CH3
#define TIMER0_CH3_GPIO_RCU			RCU_GPIOA
#define TIMER0_CH3_GPIO_PORT		GPIOA
#define TIMER0_CH3_GPIO_PIN			GPIO_PIN_11
#endif

#endif

/*****************************************/
/************* TIMER1 Config *************/
/*****************************************/
#if USE_LIB_TIMER_1

#define USE_LIB_TIMER1_CH0	0
#define USE_LIB_TIMER1_CH1	1
#define USE_LIB_TIMER1_CH2	0
#define USE_LIB_TIMER1_CH3	0


//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER1_PRESCALER		10
#define TIMER1_FREQ				500

/********** Timer1 CH0 *********/
///// PA0,PA5,PA15,PB8
#if USE_LIB_TIMER1_CH0
#define TIMER1_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER1_CH0_GPIO_PORT	GPIOA
#define TIMER1_CH0_GPIO_PIN		GPIO_PIN_0
#endif
/********** Timer1 CH1 *********/
///// PA1,PB3,PB9
#if USE_LIB_TIMER1_CH1
#define TIMER1_CH1_GPIO_RCU		RCU_GPIOB
#define TIMER1_CH1_GPIO_PORT	GPIOB
#define TIMER1_CH1_GPIO_PIN		GPIO_PIN_9
#endif
/********** Timer1 CH2 *********/
///// PA2,PB10
#if USE_LIB_TIMER1_CH2
#define TIMER1_CH2_GPIO_RCU		RCU_GPIOA
#define TIMER1_CH2_GPIO_PORT	GPIOA
#define TIMER1_CH2_GPIO_PIN		GPIO_PIN_2
#endif
/********** Timer1 CH3 *********/
///// PA3,PB2,PB11
#if USE_LIB_TIMER1_CH3
#define TIMER1_CH3_GPIO_RCU		RCU_GPIOA
#define TIMER1_CH3_GPIO_PORT	GPIOA
#define TIMER1_CH3_GPIO_PIN		GPIO_PIN_3
#endif

#endif


/*****************************************/
/************* TIMER2 Config *************/
/*****************************************/
#if USE_LIB_TIMER_2

#define USE_LIB_TIMER2_CH0	1
#define USE_LIB_TIMER2_CH1	1
#define USE_LIB_TIMER2_CH2	1
#define USE_LIB_TIMER2_CH3	1


//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER2_PRESCALER		10
#define TIMER2_FREQ					500

/********** Timer2 CH0 *********/
///// PA6,PB4,PC6
#if USE_LIB_TIMER2_CH0
#define TIMER2_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER2_CH0_GPIO_PORT	GPIOA
#define TIMER2_CH0_GPIO_PIN		GPIO_PIN_6
#endif
/********** Timer2 CH1 *********/
///// PA7,PB5,PC7
#if USE_LIB_TIMER2_CH1
#define TIMER2_CH1_GPIO_RCU		RCU_GPIOA
#define TIMER2_CH1_GPIO_PORT	GPIOA
#define TIMER2_CH1_GPIO_PIN		GPIO_PIN_7
#endif
/********** Timer2 CH2 *********/
///// PB0,PC8
#if USE_LIB_TIMER2_CH2
#define TIMER2_CH2_GPIO_RCU		RCU_GPIOB
#define TIMER2_CH2_GPIO_PORT	GPIOB
#define TIMER2_CH2_GPIO_PIN		GPIO_PIN_0
#endif
/********** Timer2 CH3 *********/
///// PB1,PC9
#if USE_LIB_TIMER2_CH3
#define TIMER2_CH3_GPIO_RCU		RCU_GPIOB
#define TIMER2_CH3_GPIO_PORT	GPIOB
#define TIMER2_CH3_GPIO_PIN		GPIO_PIN_1
#endif

#endif
/*****************************************/
/************* TIMER3 Config *************/
/*****************************************/
#if USE_LIB_TIMER_3

#define USE_LIB_TIMER3_CH0	0
#define USE_LIB_TIMER3_CH1	0
#define USE_LIB_TIMER3_CH2	0
#define USE_LIB_TIMER3_CH3	1


//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER3_PRESCALER		100
#define TIMER3_FREQ				50

/********** Timer3 CH0 *********/
///// PB6,PD12
#if USE_LIB_TIMER3_CH0
#define TIMER3_CH0_GPIO_RCU		RCU_GPIOB
#define TIMER3_CH0_GPIO_PORT	GPIOB
#define TIMER3_CH0_GPIO_PIN		GPIO_PIN_6
#endif
/********** Timer3 CH1 *********/
///// PB7,PD13
#if USE_LIB_TIMER3_CH1
#define TIMER3_CH1_GPIO_RCU		RCU_GPIOB
#define TIMER3_CH1_GPIO_PORT	GPIOB
#define TIMER3_CH1_GPIO_PIN		GPIO_PIN_7
#endif
/********** Timer3 CH2 *********/
///// PB8,PD14
#if USE_LIB_TIMER3_CH2
#define TIMER3_CH2_GPIO_RCU		RCU_GPIOB
#define TIMER3_CH2_GPIO_PORT	GPIOB
#define TIMER3_CH2_GPIO_PIN		GPIO_PIN_8
#endif
/********** Timer3 CH3 *********/
///// PB9,PD15
#if USE_LIB_TIMER3_CH3
#define TIMER3_CH3_GPIO_RCU		RCU_GPIOD
#define TIMER3_CH3_GPIO_PORT	GPIOD
#define TIMER3_CH3_GPIO_PIN		GPIO_PIN_15
#endif

#endif
/*****************************************/
/************* TIMER4 Config *************/
/*****************************************/
#if USE_LIB_TIMER_4

#define USE_LIB_TIMER4_CH0	1
#define USE_LIB_TIMER4_CH1	1
#define USE_LIB_TIMER4_CH2	1
#define USE_LIB_TIMER4_CH3	1


//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER4_PRESCALER		10
#define TIMER4_FREQ					500

/********** Timer4 CH0 *********/
///// PA0,PH10
#if USE_LIB_TIMER4_CH0
#define TIMER4_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER4_CH0_GPIO_PORT	GPIOA
#define TIMER4_CH0_GPIO_PIN		GPIO_PIN_0
#endif
/********** Timer4 CH1 *********/
///// PA1,PH11
#if USE_LIB_TIMER4_CH1
#define TIMER4_CH1_GPIO_RCU		RCU_GPIOA
#define TIMER4_CH1_GPIO_PORT	GPIOA
#define TIMER4_CH1_GPIO_PIN		GPIO_PIN_1
#endif
/********** Timer4 CH2 *********/
///// PA2,PH12
#if USE_LIB_TIMER4_CH2
#define TIMER4_CH2_GPIO_RCU		RCU_GPIOA
#define TIMER4_CH2_GPIO_PORT	GPIOA
#define TIMER4_CH2_GPIO_PIN		GPIO_PIN_2
#endif
/********** Timer4 CH3 *********/
///// PA3,PI0
#if USE_LIB_TIMER4_CH3
#define TIMER4_CH3_GPIO_RCU		RCU_GPIOA
#define TIMER4_CH3_GPIO_PORT	GPIOA
#define TIMER4_CH3_GPIO_PIN		GPIO_PIN_3
#endif

#endif

/*****************************************/
/************* TIMER5 Config *************/
/*****************************************/
#if USE_LIB_TIMER_5

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER5_PRESCALER		10
#define TIMER5_FREQ				1000

#define TIMER5_INT_CALLBACK		1

#endif

/*****************************************/
/************* TIMER6 Config *************/
/*****************************************/
#if USE_LIB_TIMER_6

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER6_PRESCALER		10
#define TIMER6_FREQ				1000

#define TIMER6_NVIC				2, 2
#define TIMER6_INT_CALLBACK		1

#endif

/*****************************************/
/************* TIMER7 Config *************/
/*****************************************/
#if USE_LIB_TIMER_7

#define USE_LIB_TIMER7_CH0_P	1
#define USE_LIB_TIMER7_CH0_N	1
#define USE_LIB_TIMER7_CH1_P	1
#define USE_LIB_TIMER7_CH1_N	1
#define USE_LIB_TIMER7_CH2_P	1
#define USE_LIB_TIMER7_CH2_N	1
#define USE_LIB_TIMER7_CH3		1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER7_PRESCALER		10
#define TIMER7_FREQ					500

/********** Timer7 CH0 *********/
///// PC6, PI15
#if USE_LIB_TIMER7_CH0_P
#define TIMER7_CH0_P_GPIO_RCU		RCU_GPIOC
#define TIMER7_CH0_P_GPIO_PORT	GPIOC
#define TIMER7_CH0_P_GPIO_PIN		GPIO_PIN_6
#endif
///// PA5 ON, PA7 ON, PH13 ON
#if USE_LIB_TIMER7_CH0_N
#define TIMER7_CH0_N_GPIO_RCU		RCU_GPIOA
#define TIMER7_CH0_N_GPIO_PORT	GPIOA
#define TIMER7_CH0_N_GPIO_PIN		GPIO_PIN_5
#endif

/********** Timer7 CH1 *********/
///// PC7, PI6
#if USE_LIB_TIMER7_CH1_P
#define TIMER7_CH1_P_GPIO_RCU		RCU_GPIOC
#define TIMER7_CH1_P_GPIO_PORT	GPIOC
#define TIMER7_CH1_P_GPIO_PIN		GPIO_PIN_7
#endif
///// PB0 ON, PB14 ON, PH14 ON
#if USE_LIB_TIMER7_CH1_N
#define TIMER7_CH1_N_GPIO_RCU		RCU_GPIOB
#define TIMER7_CH1_N_GPIO_PORT	GPIOB
#define TIMER7_CH1_N_GPIO_PIN		GPIO_PIN_0
#endif

/********** Timer7 ch2 *********/
///// PC8, PI7
#if USE_LIB_TIMER7_CH2_P
#define TIMER7_CH2_P_GPIO_RCU		RCU_GPIOC
#define TIMER7_CH2_P_GPIO_PORT	GPIOC
#define TIMER7_CH2_P_GPIO_PIN		GPIO_PIN_8
#endif
///// PB1 ON, PB15 ON, PH15 ON
#if USE_LIB_TIMER7_CH2_N
#define TIMER7_CH2_N_GPIO_RCU		RCU_GPIOB
#define TIMER7_CH2_N_GPIO_PORT	GPIOB
#define TIMER7_CH2_N_GPIO_PIN		GPIO_PIN_1
#endif

/********** Timer7 ch3 *********/
// PC9, PI2
#if USE_LIB_TIMER7_CH3
#define TIMER7_CH3_GPIO_RCU			RCU_GPIOC
#define TIMER7_CH3_GPIO_PORT		GPIOC
#define TIMER7_CH3_GPIO_PIN			GPIO_PIN_9
#endif

#endif
/*****************************************/
/************* TIMER8 Config *************/
/*****************************************/
#if USE_LIB_TIMER_8

#define USE_LIB_TIMER8_CH0	1
#define USE_LIB_TIMER8_CH1	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER8_PRESCALER		10
#define TIMER8_FREQ					500

/********** Timer8 CH0 *********/
///// PA2,PE5
#if USE_LIB_TIMER8_CH0
#define TIMER8_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER8_CH0_GPIO_PORT	GPIOA
#define TIMER8_CH0_GPIO_PIN		GPIO_PIN_2
#endif
/********** Timer8 CH1 *********/
///// PA3,PE6
#if USE_LIB_TIMER8_CH1
#define TIMER8_CH1_GPIO_RCU		RCU_GPIOA
#define TIMER8_CH1_GPIO_PORT	GPIOA
#define TIMER8_CH1_GPIO_PIN		GPIO_PIN_3
#endif

#endif

/*****************************************/
/************* TIMER9 Config *************/
/*****************************************/
#if USE_LIB_TIMER_9

#define USE_LIB_TIMER9_CH0	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER9_PRESCALER		10
#define TIMER9_FREQ					500

/********** Timer9 CH0 *********/
///// PB8,PF6
#if USE_LIB_TIMER9_CH0
#define TIMER9_CH0_GPIO_RCU		RCU_GPIOB
#define TIMER9_CH0_GPIO_PORT	GPIOB
#define TIMER9_CH0_GPIO_PIN		GPIO_PIN_8
#endif

#endif
/*****************************************/
/************* TIMER10 Config ************/
/*****************************************/
#if USE_LIB_TIMER_10

#define USE_LIB_TIMER10_CH0	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER10_PRESCALER			10
#define TIMER10_FREQ					500

/********** Timer10 CH0 *********/
///// PB9,PF7
#if USE_LIB_TIMER10_CH0
#define TIMER10_CH0_GPIO_RCU		RCU_GPIOB
#define TIMER10_CH0_GPIO_PORT		GPIOB
#define TIMER10_CH0_GPIO_PIN		GPIO_PIN_9
#endif

#endif
/*****************************************/
/************* TIMER11 Config ************/
/*****************************************/
#if USE_LIB_TIMER_11

#define USE_LIB_TIMER11_CH0	1
#define USE_LIB_TIMER11_CH1	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER11_PRESCALER			10
#define TIMER11_FREQ					500

/********** Timer11 CH0 *********/
///// PB14,PH6
#if USE_LIB_TIMER11_CH0
#define TIMER11_CH0_GPIO_RCU		RCU_GPIOB
#define TIMER11_CH0_GPIO_PORT		GPIOB
#define TIMER11_CH0_GPIO_PIN		GPIO_PIN_14
#endif
/********** Timer11 CH1 *********/
///// PB15,PH7
#if USE_LIB_TIMER11_CH1
#define TIMER11_CH1_GPIO_RCU		RCU_GPIOB
#define TIMER11_CH1_GPIO_PORT		GPIOB
#define TIMER11_CH1_GPIO_PIN		GPIO_PIN_15
#endif

#endif
/*****************************************/
/************* TIMER12 Config ************/
/*****************************************/
#if USE_LIB_TIMER_12

#define USE_LIB_TIMER12_CH0	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER12_PRESCALER			10
#define TIMER12_FREQ					500

/********** Timer10 CH0 *********/
///// PA6,PF8
#if USE_LIB_TIMER12_CH0
#define TIMER12_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER12_CH0_GPIO_PORT		GPIOA
#define TIMER12_CH0_GPIO_PIN		GPIO_PIN_6
#endif

#endif
/*****************************************/
/************* TIMER13 Config ************/
/*****************************************/
#if USE_LIB_TIMER_13

#define USE_LIB_TIMER13_CH0	1

//分频和周期配置 (PRESCALER * FREQ 必须大于(主频/65536))
#define TIMER13_PRESCALER			10
#define TIMER13_FREQ					500

/********** Timer10 CH0 *********/
///// PA7,PF9
#if USE_LIB_TIMER13_CH0
#define TIMER13_CH0_GPIO_RCU		RCU_GPIOA
#define TIMER13_CH0_GPIO_PORT		GPIOA
#define TIMER13_CH0_GPIO_PIN		GPIO_PIN_7
#endif

#endif


#endif