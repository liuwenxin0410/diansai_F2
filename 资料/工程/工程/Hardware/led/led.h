/**
  *************************************************************************************************************************
  * @file    led.h
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   led模块.h文件配置
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __LED_H
#define	__LED_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/
#define LED_RED  		PBout(3)
#define LED_GREEN  	PBout(4)
#define LED_YELLOW  PBout(5)




/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void LED_GPIO_Config(void);

#endif /* __LED_H */

/*****************************************************END OF FILE*********************************************************/	
