#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
/* 下 */
#define key_xia_port                  GPIOA                       
#define key_xia_pin                   GPIO_Pin_11
#define RCC_APBxPeriph_GPIOx_xia      RCC_APB2Periph_GPIOA

/* 返回 */
#define key_fanhui_port               GPIOC
#define key_fanhui_pin                GPIO_Pin_2 
#define RCC_APBxPeriph_GPIOx_fanhui   RCC_APB2Periph_GPIOC 
 
/* 确认 */
#define key_queren_port               GPIOC
#define key_queren_pin                GPIO_Pin_0 
#define RCC_APBxPeriph_GPIOx_queren   RCC_APB2Periph_GPIOC  
 
 
#define KEY0    GPIO_ReadInputDataBit(key_xia_port,key_xia_pin)//读取按键0
#define KEY1    GPIO_ReadInputDataBit(key_fanhui_port,key_fanhui_pin)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(key_queren_port,key_queren_pin)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
