#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
/* 颜色0 红 PC10*/
#define led0_port                      GPIOC                       
#define led0_pin                       GPIO_Pin_10
#define RCC_APBxPeriph_GPIOx_led0      RCC_APB2Periph_GPIOC

/* 颜色1 绿 PC11*/
#define led1_port                      GPIOC
#define led1_pin                       GPIO_Pin_11 
#define RCC_APBxPeriph_GPIOx_led1      RCC_APB2Periph_GPIOC 
 
/* 颜色2 蓝 PC12*/
#define led2_port                      GPIOC
#define led2_pin                       GPIO_Pin_12 
#define RCC_APBxPeriph_GPIOx_led2      RCC_APB2Periph_GPIOC 


#define Red_led                           PCout(10)	// PA8  红灯
#define Greeen_led                           PCout(11)	// PD2	黄灯
#define Yellow_led                          PCout(12)	// PD2	黄灯


#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态
#define LED0_TOGGLE		 digitalToggle(led0_port,led0_pin)
#define LED1_TOGGLE		 digitalToggle(led1_port,led1_pin)
#define LED2_TOGGLE		 digitalToggle(led2_port,led2_pin)

void LED_Init(void);//初始化

		 				    
#endif

