/**
  *************************************************************************************************************************
  * @file    usart3.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   串口3.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "usart3.h"

/* 定义 -----------------------------------------------------------------------------------------------------------------*/


 /**
 * 函数名:Usart3_Init
 * 描述:串口3初始化
 * 输入:Bound-波特率 
 * 输出:无
 */
void Usart3_Init(u32 Bound)
{
  GPIO_InitTypeDef 		GPIO_InitStructure;
	USART_InitTypeDef		USART_InitStructure;
  NVIC_InitTypeDef 		NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	USART_InitStructure.USART_BaudRate=Bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	
	USART_Init(USART3,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
}
 
/*****************************************************END OF FILE*********************************************************/	
