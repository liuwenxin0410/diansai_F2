#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "stm32f10x.h"
//������ص��ú궨��
//1.��ʱ��2���ɲ��������ֲ��޸�
#define   RCC_APB2Periph_bmq1GPIOx       RCC_APB2Periph_GPIOA
#define   RCC_APB1Periph_bmq1TIMx        RCC_APB1Periph_TIM2
#define   bmq1GPIO_Pin_x1                GPIO_Pin_0
#define   bmq1GPIO_Pin_x2                GPIO_Pin_1
#define   bmq1GPIOx                      GPIOA
#define   bmq1TIMx                       TIM2
//2.��ʱ��4���ɲ��������ֲ��޸�
#define   RCC_APB2Periph_bmq2GPIOx       RCC_APB2Periph_GPIOA
#define   RCC_APB1Periph_bmq2TIMx        RCC_APB1Periph_TIM3
#define   bmq2GPIO_Pin_x1                GPIO_Pin_6
#define   bmq2GPIO_Pin_x2                GPIO_Pin_7
#define   bmq2GPIOx                      GPIOA
#define   bmq2TIMx                       TIM3


int Read_Speed(int TIMx);
void Encoder_TIM2_Init(void);
void Encoder_TIM3_Init(void);
#endif


