
/**
  *************************************************************************************************************************
  * @file    tim3.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   tim3定时器模块.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "tim3.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/

/**
 * 函数名:Tim3_Init
 * 描述:定时-10ms
 * 输入:无
 * 输出:无
 */
void Tim3_Init(void)
{
  NVIC_InitTypeDef 					NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}


/*****************************************************END OF FILE*********************************************************/	
