#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
/* ��ɫ0 �� PC10*/
#define led0_port                      GPIOC                       
#define led0_pin                       GPIO_Pin_10
#define RCC_APBxPeriph_GPIOx_led0      RCC_APB2Periph_GPIOC

/* ��ɫ1 �� PC11*/
#define led1_port                      GPIOC
#define led1_pin                       GPIO_Pin_11 
#define RCC_APBxPeriph_GPIOx_led1      RCC_APB2Periph_GPIOC 
 
/* ��ɫ2 �� PC12*/
#define led2_port                      GPIOC
#define led2_pin                       GPIO_Pin_12 
#define RCC_APBxPeriph_GPIOx_led2      RCC_APB2Periph_GPIOC 


#define Red_led                           PCout(10)	// PA8  ���
#define Greeen_led                           PCout(11)	// PD2	�Ƶ�
#define Yellow_led                          PCout(12)	// PD2	�Ƶ�


#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬
#define LED0_TOGGLE		 digitalToggle(led0_port,led0_pin)
#define LED1_TOGGLE		 digitalToggle(led1_port,led1_pin)
#define LED2_TOGGLE		 digitalToggle(led2_port,led2_pin)

void LED_Init(void);//��ʼ��

		 				    
#endif

