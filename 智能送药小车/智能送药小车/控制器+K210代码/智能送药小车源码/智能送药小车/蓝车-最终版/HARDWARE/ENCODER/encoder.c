#include "encoder.h"


void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_bmq1GPIOx,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_bmq1TIMx,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA0、PA1
	GPIO_InitStruct.GPIO_Pin=bmq1GPIO_Pin_x1 |bmq1GPIO_Pin_x2;
	GPIO_Init(bmq1GPIOx,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(bmq1TIMx,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(bmq1TIMx,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(bmq1TIMx,&TIM_ICInitStruct);
	
	TIM_ITConfig(bmq1TIMx,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
	TIM_SetCounter(bmq1TIMx,0);//清零定时器计数值
	TIM_Cmd(bmq1TIMx,ENABLE);//开启定时器
}


void Encoder_TIM3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_bmq2GPIOx,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_bmq2TIMx,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=bmq2GPIO_Pin_x1 |bmq2GPIO_Pin_x2;
	GPIO_Init(bmq2GPIOx,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(bmq2TIMx,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(bmq2TIMx,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(bmq2TIMx,&TIM_ICInitStruct);
	
	TIM_ClearFlag(bmq2TIMx,TIM_FLAG_Update);
	TIM_ITConfig(bmq2TIMx,TIM_IT_Update,ENABLE);	
	TIM_SetCounter(bmq2TIMx,0);
	TIM_Cmd(bmq2TIMx,ENABLE);
}


/**********************
编码器
速度读取函数
入口参数：定时器
**********************/
int Read_Speed(int TIMx)
{
	int	value_1;
	switch(TIMx)
	{
		case 2:value_1=(short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0);break;//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 3:value_1=(short)TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;
		default:value_1=0;
	}
	return value_1;
}


void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
	
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

