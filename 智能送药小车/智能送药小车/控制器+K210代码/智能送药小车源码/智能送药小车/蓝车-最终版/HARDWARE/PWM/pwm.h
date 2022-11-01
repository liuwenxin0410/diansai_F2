#ifndef  _PWM_H
#define  _PWM_H

#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM4

#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_Period            7199
#define            GENERAL_TIM_Prescaler         0
// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH1_PORT          GPIOB
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 输出比较通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH2_PORT          GPIOB
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7

//// TIM3 输出比较通道3
//#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
//#define            GENERAL_TIM_CH3_PORT          GPIOB
//#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_8

//// TIM3 输出比较通道4
//#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
//#define            GENERAL_TIM_CH4_PORT          GPIOB
//#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_9


/**************************函数声明********************************/

void GENERAL_TIM_Init(void);
#endif

