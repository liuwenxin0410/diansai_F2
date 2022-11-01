/**
  *************************************************************************************************************************
  * @file    encoder.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   ������.c�ļ�����
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "encoder.h"
/* ���� -----------------------------------------------------------------------------------------------------------------*/


/**
 * ������:TIM2_Encoder_Init
 * ����:��ʱ��2����������
 * ����:��
 * ���:��
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
 * ������:TIM4_Encoder_Init
 * ����:��ʱ��4����������
 * ����:��
 * ���:��
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
 * ������:Read_Pluse
 * ����:�����ȡ����
 * ����:Timx=(2,4)
 * ���:��Ӧ��ʱ����ȡ��������ֵ
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
 * ������:TIM2_IRQHandler
 * ����:��ʱ��2�жϷ�����
 * ����:��
 * ���:��
 */
void TIM2_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
 {
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
 }
}

/**
 * ������:TIM4_IRQHandler
 * ����:��ʱ��4�жϷ�����
 * ����:��
 * ���:��
 */
void TIM4_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
 {
  TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
 }
}

/*****************************************************END OF FILE*********************************************************/	
