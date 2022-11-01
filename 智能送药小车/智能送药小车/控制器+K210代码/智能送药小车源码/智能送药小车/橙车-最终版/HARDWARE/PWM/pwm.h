#ifndef  _PWM_H
#define  _PWM_H

#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM4

#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_Period            7199
#define            GENERAL_TIM_Prescaler         0
// TIM3 ����Ƚ�ͨ��1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH1_PORT          GPIOB
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 ����Ƚ�ͨ��2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH2_PORT          GPIOB
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7

//// TIM3 ����Ƚ�ͨ��3
//#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
//#define            GENERAL_TIM_CH3_PORT          GPIOB
//#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_8

//// TIM3 ����Ƚ�ͨ��4
//#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
//#define            GENERAL_TIM_CH4_PORT          GPIOB
//#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_9


/**************************��������********************************/

void GENERAL_TIM_Init(void);
#endif

