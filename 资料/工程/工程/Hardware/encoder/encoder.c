/**
  *************************************************************************************************************************
  * @file    encoder.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   编码器.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "encoder.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/


/**
 * 函数名:TIM2_Encoder_Init
 * 描述:定时器2编码器配置
 * 输入:无
 * 输出:无
 */
void TIM2_Encoder_Init(void)
{
 	GPIO_InitTypeDef 					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef         TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM2,0);
	
	TIM_Cmd(TIM2,ENABLE);
}


/**
 * 函数名:TIM4_Encoder_Init
 * 描述:定时器4编码器配置
 * 输入:无
 * 输出:无
 */
void TIM4_Encoder_Init(void)
{
 	GPIO_InitTypeDef 					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef         TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM4,0);
	
	TIM_Cmd(TIM4,ENABLE);
}


/**
 * 函数名:Read_Pluse
 * 描述:脉冲读取函数
 * 输入:Timx=(2,4)
 * 输出:对应定时器读取到的脉冲值
 */
int Read_Pluse(int Timx)
{
  int value;
	switch (Timx)
	{
	  case 2:value=(short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0); break;
		case 4:value=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;
		default:break;
	}
	return value;
}


/**
 * 函数名:TIM2_IRQHandler
 * 描述:定时器2中断服务函数
 * 输入:无
 * 输出:无
 */
void TIM2_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
 {
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
 }
}

/**
 * 函数名:TIM4_IRQHandler
 * 描述:定时器4中断服务函数
 * 输入:无
 * 输出:无
 */
void TIM4_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
 {
  TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
 }
}

/*****************************************************END OF FILE*********************************************************/	
