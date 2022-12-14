/**
  *************************************************************************************************************************
  * @file    systick.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   滴答定时器.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "systick.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/



/**
 * 函数名:SysTick_Init
 * 描述:滴答定时器初始化-1ms中断
 * 输入:无
 * 输出:无
 */
void SysTick_Init(void)	 
{	
	if(SysTick_Config(SystemCoreClock/1000))//1ms中断
	{
	  while(1);
	}
	SysTick->CTRL |=~SysTick_CTRL_ENABLE_Msk;//开启定时器	
}
    								   



/*****************************************************END OF FILE*********************************************************/	
