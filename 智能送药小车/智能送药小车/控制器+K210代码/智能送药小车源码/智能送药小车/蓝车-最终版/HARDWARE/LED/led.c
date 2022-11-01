#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini�SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APBxPeriph_GPIOx_led0|RCC_APBxPeriph_GPIOx_led1|RCC_APBxPeriph_GPIOx_led2, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = led0_pin;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(led0_port, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8

 GPIO_InitStructure.GPIO_Pin = led1_pin;				 //LED1-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(led1_port, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
 GPIO_InitStructure.GPIO_Pin = led2_pin;				 //LED2-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(led2_port, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8

 GPIO_SetBits(led0_port,led0_pin); 						 //PD.2 �����
 GPIO_SetBits(led1_port,led1_pin); 						 //PD.2 ����� 
 GPIO_SetBits(led2_port,led2_pin); 						 //PD.2 �����  
}
 
