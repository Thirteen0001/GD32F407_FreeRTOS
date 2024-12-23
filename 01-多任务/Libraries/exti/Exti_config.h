#ifndef __EXTI_CONFIG_H__
#define __EXTI_CONFIG_H__


#define USE_LIB_EXTI_0	0
#define USE_LIB_EXTI_1	0
#define USE_LIB_EXTI_2	0
#define USE_LIB_EXTI_3	0
#define USE_LIB_EXTI_4	0
#define USE_LIB_EXTI_5	0
#define USE_LIB_EXTI_6	0
#define USE_LIB_EXTI_7	0
#define USE_LIB_EXTI_8	0
#define USE_LIB_EXTI_9	0
#define USE_LIB_EXTI_10	0
#define USE_LIB_EXTI_11	0
#define USE_LIB_EXTI_12	0
#define USE_LIB_EXTI_13	0
#define USE_LIB_EXTI_14	0
#define USE_LIB_EXTI_15	0


/************ EXTI 0 Config ****************/
#if USE_LIB_EXTI_0
//// ”≤¥•∑¢/»Ì¥•∑¢
#define EXTI0_SOFT_TRIG		0
#if EXTI0_SOFT_TRIG == 0
#define EXTI0_GPIO_RCU		RCU_GPIOC
#define EXTI0_GPIO_PORT		GPIOC
#define EXTI0_SRC			EXTI_SOURCE_GPIOC

#define EXTI0_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI0_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI0_NVIC				2, 2
#endif

/************ EXTI 1 Config ****************/
#if USE_LIB_EXTI_1
#define EXTI1_SOFT_TRIG		0
#if EXTI1_SOFT_TRIG == 0
#define EXTI1_GPIO_RCU		RCU_GPIOC
#define EXTI1_GPIO_PORT		GPIOC
#define EXTI1_SRC					EXTI_SOURCE_GPIOC

#define EXTI1_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI1_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI1_NVIC				2, 2
#endif

/************ EXTI 2 Config ****************/
#if USE_LIB_EXTI_2
#define EXTI2_SOFT_TRIG		0
#if EXTI2_SOFT_TRIG == 0
#define EXTI2_GPIO_RCU		RCU_GPIOC
#define EXTI2_GPIO_PORT		GPIOC
#define EXTI2_SRC					EXTI_SOURCE_GPIOC

#define EXTI2_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI2_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI2_NVIC				2, 2
#endif

/************ EXTI 3 Config ****************/
#if USE_LIB_EXTI_3
#define EXTI3_SOFT_TRIG		0
#if EXTI3_SOFT_TRIG == 0
#define EXTI3_GPIO_RCU		RCU_GPIOC
#define EXTI3_GPIO_PORT		GPIOC
#define EXTI3_SRC					EXTI_SOURCE_GPIOC

#define EXTI3_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI3_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI3_NVIC				2, 2
#endif

/************ EXTI 4 Config ****************/
#if USE_LIB_EXTI_4
#define EXTI4_SOFT_TRIG		0
#if EXTI4_SOFT_TRIG == 0
#define EXTI4_GPIO_RCU		RCU_GPIOC
#define EXTI4_GPIO_PORT		GPIOC
#define EXTI4_SRC					EXTI_SOURCE_GPIOC

#define EXTI4_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI4_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI4_NVIC				2, 2
#endif


/************ EXTI 5 Config ****************/
#if USE_LIB_EXTI_5
#define EXTI5_SOFT_TRIG		0
#if EXTI5_SOFT_TRIG == 0
#define EXTI5_GPIO_RCU		RCU_GPIOC
#define EXTI5_GPIO_PORT		GPIOC
#define EXTI5_SRC					EXTI_SOURCE_GPIOC

#define EXTI5_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI5_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI5_NVIC				2, 2
#endif


/************ EXTI 6 Config ****************/
#if USE_LIB_EXTI_6
#define EXTI6_SOFT_TRIG		0
#if EXTI6_SOFT_TRIG == 0
#define EXTI6_GPIO_RCU		RCU_GPIOC
#define EXTI6_GPIO_PORT		GPIOC
#define EXTI6_SRC					EXTI_SOURCE_GPIOC

#define EXTI6_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI6_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI6_NVIC				2, 2
#endif


/************ EXTI 7 Config ****************/
#if USE_LIB_EXTI_7
#define EXTI7_SOFT_TRIG		0
#if EXTI7_SOFT_TRIG == 0
#define EXTI7_GPIO_RCU		RCU_GPIOC
#define EXTI7_GPIO_PORT		GPIOC
#define EXTI7_SRC					EXTI_SOURCE_GPIOC

#define EXTI7_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI7_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI7_NVIC				2, 2
#endif



/************ EXTI 8 Config ****************/
#if USE_LIB_EXTI_8
#define EXTI8_SOFT_TRIG		0
#if EXTI8_SOFT_TRIG == 0
#define EXTI8_GPIO_RCU		RCU_GPIOB
#define EXTI8_GPIO_PORT		GPIOB
#define EXTI8_SRC			EXTI_SOURCE_GPIOB

#define EXTI8_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI8_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI8_NVIC			2, 2
#endif



/************ EXTI 9 Config ****************/
#if USE_LIB_EXTI_9
#define EXTI9_SOFT_TRIG		0
#if EXTI9_SOFT_TRIG == 0
#define EXTI9_GPIO_RCU		RCU_GPIOC
#define EXTI9_GPIO_PORT		GPIOC
#define EXTI9_SRC					EXTI_SOURCE_GPIOC

#define EXTI9_GPIO_PUPD		GPIO_PUPD_PULLUP
#define EXTI9_TRIGGER			EXTI_TRIG_BOTH
#endif

#define EXTI9_NVIC				2, 2
#endif


/************ EXTI 10 Config ****************/
#if USE_LIB_EXTI_10
#define EXTI10_SOFT_TRIG		0
#if EXTI10_SOFT_TRIG == 0
#define EXTI10_GPIO_RCU		RCU_GPIOC
#define EXTI10_GPIO_PORT	GPIOC
#define EXTI10_SRC				EXTI_SOURCE_GPIOC

#define EXTI10_GPIO_PUPD	GPIO_PUPD_PULLUP
#define EXTI10_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI10_NVIC				2, 2
#endif


/************ EXTI 11 Config ****************/
#if USE_LIB_EXTI_11
#define EXTI11_SOFT_TRIG		0
#if EXTI11_SOFT_TRIG == 0
#define EXTI11_GPIO_RCU		RCU_GPIOD
#define EXTI11_GPIO_PORT	GPIOD
#define EXTI11_SRC			EXTI_SOURCE_GPIOD

#define EXTI11_GPIO_PUPD	GPIO_PUPD_NONE
#define EXTI11_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI11_NVIC				2, 2
#endif



/************ EXTI 12 Config ****************/
#if USE_LIB_EXTI_12
#define EXTI12_SOFT_TRIG		0
#if EXTI12_SOFT_TRIG == 0
#define EXTI12_GPIO_RCU		RCU_GPIOC
#define EXTI12_GPIO_PORT	GPIOC
#define EXTI12_SRC				EXTI_SOURCE_GPIOC

#define EXTI12_GPIO_PUPD	GPIO_PUPD_PULLUP
#define EXTI12_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI12_NVIC				2, 2
#endif



/************ EXTI 13 Config ****************/
#if USE_LIB_EXTI_13
#define EXTI13_SOFT_TRIG		0
#if EXTI13_SOFT_TRIG == 0
#define EXTI13_GPIO_RCU		RCU_GPIOC
#define EXTI13_GPIO_PORT	GPIOC
#define EXTI13_SRC				EXTI_SOURCE_GPIOC

#define EXTI13_GPIO_PUPD	GPIO_PUPD_PULLUP
#define EXTI13_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI13_NVIC				2, 2
#endif



/************ EXTI 14 Config ****************/
#if USE_LIB_EXTI_14
#define EXTI14_SOFT_TRIG		0
#if EXTI14_SOFT_TRIG == 0
#define EXTI14_GPIO_RCU		RCU_GPIOC
#define EXTI14_GPIO_PORT	GPIOC
#define EXTI14_SRC				EXTI_SOURCE_GPIOC

#define EXTI14_GPIO_PUPD	GPIO_PUPD_PULLUP
#define EXTI14_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI14_NVIC				2, 2
#endif




/************ EXTI 15 Config ****************/
#if USE_LIB_EXTI_15
#define EXTI15_SOFT_TRIG		0
#if EXTI15_SOFT_TRIG == 0
#define EXTI15_GPIO_RCU		RCU_GPIOD
#define EXTI15_GPIO_PORT	GPIOD
#define EXTI15_SRC			EXTI_SOURCE_GPIOD

#define EXTI15_GPIO_PUPD	GPIO_PUPD_NONE
#define EXTI15_TRIGGER		EXTI_TRIG_BOTH
#endif

#define EXTI15_NVIC			2, 2
#endif





#endif