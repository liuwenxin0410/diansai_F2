/**
  *************************************************************************************************************************
  * @file    tim1.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   定时器配置PWM.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "tim1.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/


/**
 * 函数名:TIM1_PWM_Init(uint16_t Psc,uint16_t Per)
 * 描述:定时器1输出pwm配置函数
 * 输入:Psc-自动重装载值 Per-预分频值
 * 输出:无
 */
void TIM1_PWM_Init(uint16_t Psc,uint16_t Per)
{
	GPIO_InitTypeDef 					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef         TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_TIM1|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=Per;
	TIM_TimeBaseInitStructure.TIM_Prescaler=Psc;
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}


/*****************************************************END OF FILE*********************************************************/	
