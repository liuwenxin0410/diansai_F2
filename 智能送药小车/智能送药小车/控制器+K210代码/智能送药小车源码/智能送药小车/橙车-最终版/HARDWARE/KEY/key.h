#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
/* �� */
#define key_xia_port                  GPIOA                       
#define key_xia_pin                   GPIO_Pin_11
#define RCC_APBxPeriph_GPIOx_xia      RCC_APB2Periph_GPIOA

/* ���� */
#define key_fanhui_port               GPIOC
#define key_fanhui_pin                GPIO_Pin_2 
#define RCC_APBxPeriph_GPIOx_fanhui   RCC_APB2Periph_GPIOC 
 
/* ȷ�� */
#define key_queren_port               GPIOC
#define key_queren_pin                GPIO_Pin_0 
#define RCC_APBxPeriph_GPIOx_queren   RCC_APB2Periph_GPIOC  
 
 
#define KEY0    GPIO_ReadInputDataBit(key_xia_port,key_xia_pin)//��ȡ����0
#define KEY1    GPIO_ReadInputDataBit(key_fanhui_port,key_fanhui_pin)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(key_queren_port,key_queren_pin)//��ȡ����2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
