#ifndef __DUOJI_H
#define	__DUOJI_H


#include "stm32f10x.h"

//������ز��ú궨��
//1.ʱ�ӳ�ʼ��
#define   RCC_APB2Periph_pwmGPIOx           RCC_APB2Periph_GPIOC
#define   RCC_APB2Periph_pwmTIMx            RCC_APB2Periph_TIM8
//2.�˿ں����ų�ʼ�����ɲ��������ֲ��������
#define   pwmGPIO_Pin_x1                    GPIO_Pin_6          //�����������,TIM8,ͨ��1
#define   pwmGPIO_Pin_x2                    GPIO_Pin_7          //�����������,TIM8,ͨ��2
#define   pwmGPIO_Pin_x3                    GPIO_Pin_8          //�����������,TIM8,ͨ��3
#define   pwmGPIO_Pin_x4                    GPIO_Pin_9          //�����������,TIM8,ͨ��4

#define   pwmGPIOx                          GPIOC                //���ö˿�
#define   pwmTIMx                           TIM8
//Ĭ�ϲ���ͨ��1��4����ȥ�������޸�

void PWM_Init_TIM8(void);
	
#endif 

