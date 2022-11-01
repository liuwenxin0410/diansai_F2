#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f10x.h"
#include "delay.h"
//GPIO��
#define HCSR04_PORT GPIOA  
#define HCSR04 RCC_APB2Periph_GPIOA
#define HCSR04_TRIG GPIO_Pin_8
#define HCSR04_ECHO GPIO_Pin_11 //ֻ��FT����
#define TRIG_Send PAout(8)
#define ECHO_Reci PAin(11)
 //��ʱ����
#define TIMX TIM7             
#define RCC_APB1Periph_TIMX RCC_APB1Periph_TIM7
#define TIMX_IRQn TIM7_IRQn   
#define TIMX_IRQHandler TIM7_IRQHandler

void HCSR04_Init(void);        //��������ʼ��
float Hcsr04GetLength(void);   //���������
void Measure_cm(void);
#endif
