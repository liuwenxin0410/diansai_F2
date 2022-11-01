/**
  *************************************************************************************************************************
  * @file    infrared.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   红外传感器模块.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "infrared.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/

/**
 * 函数名:Infrafred_GPIO_Init
 * 描述:红外传感器对应gpio配置
 * 输入:无
 * 输出:无
 */
void Infrafred_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruture);
}

/**
 * 函数名:LoadOrNot
 * 描述:检测药品装载
 * 输入:无
 * 输出:0-等待 1-装药 2-取药
 */
uint8_t LoadOrNot(void)
{
  static uint8_t load_flag;
	
	if(DRUG_Testing==1)//装载药品完成
	{
	 load_flag=1;
		return 1;
	}
	else if(DRUG_Testing==0)
	{
	  if(load_flag==1)//取药完成
		{
		  return 2;
		}
	}
  return 0;
}


/*****************************************************END OF FILE*********************************************************/	
