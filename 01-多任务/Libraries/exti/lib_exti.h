#ifndef __LIB_lib_exti_H__
#define __LIB_lib_exti_H__

#include "gd32f4xx.h"
#include "Exti_config.h"

void lib_exti_init();


#if USE_LIB_EXTI_0
extern void lib_exti0_on_trig();
#if EXTI0_SOFT_TRIG
void lib_exti0_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_1
extern void lib_exti1_on_trig();
#if EXTI1_SOFT_TRIG
void lib_exti1_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_2
extern void lib_exti2_on_trig();
#if EXTI2_SOFT_TRIG
void lib_exti2_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_3
extern void lib_exti3_on_trig();
#if EXTI3_SOFT_TRIG
void lib_exti3_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_4
extern void lib_exti4_on_trig();
#if EXTI4_SOFT_TRIG
void lib_exti4_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_5
extern void lib_exti5_on_trig();
#if EXTI5_SOFT_TRIG
void lib_exti5_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_6
extern void lib_exti6_on_trig();
#if EXTI6_SOFT_TRIG
void lib_exti6_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_7
extern void lib_exti7_on_trig();
#if EXTI7_SOFT_TRIG
void lib_exti7_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_8
extern void lib_exti8_on_trig();
#if EXTI8_SOFT_TRIG
void lib_exti8_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_9
extern void lib_exti9_on_trig();
#if EXTI9_SOFT_TRIG
void lib_exti9_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_10
extern void lib_exti10_on_trig();
#if EXTI10_SOFT_TRIG
void lib_exti10_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_11
extern void lib_exti11_on_trig();
#if EXTI11_SOFT_TRIG
void lib_exti11_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_12
extern void lib_exti12_on_trig();
#if EXTI12_SOFT_TRIG
void lib_exti12_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_13
extern void lib_exti13_on_trig();
#if EXTI13_SOFT_TRIG
void lib_exti13_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_14
extern void lib_exti14_on_trig();
#if EXTI14_SOFT_TRIG
void lib_exti14_soft_trig();
#endif
#endif

#if USE_LIB_EXTI_15
extern void lib_exti15_on_trig();
#if EXTI15_SOFT_TRIG
void lib_exti15_soft_trig();
#endif
#endif




#endif