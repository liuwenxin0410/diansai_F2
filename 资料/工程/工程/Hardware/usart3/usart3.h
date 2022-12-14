/**
  *************************************************************************************************************************
  * @file    usart3.h
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   串口3.h文件配置
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __USART3_H
#define	__USART3_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "myconfig.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/

/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void Usart3_Init(u32 Bound);

#endif /* __USART3_H */

/*****************************************************END OF FILE*********************************************************/	
