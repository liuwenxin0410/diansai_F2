#include "duoji.h"  

void PWM_Init_TIM8(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_pwmGPIOx | RCC_APB2Periph_pwmTIMx | RCC_APB2Periph_AFIO,ENABLE);//����ʱ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//��ʼ��GPIO--PA8��PA11Ϊ�����������
	GPIO_InitStruct.GPIO_Pin=pwmGPIO_Pin_x1 |pwmGPIO_Pin_x2 |pwmGPIO_Pin_x3 |pwmGPIO_Pin_x4;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(pwmGPIOx,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//��ʼ����ʱ����
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=19999;
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;
	TIM_TimeBaseInit(pwmTIMx,&TIM_TimeBaseInitStruct);/*��2��*///TIM1
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//��ʼ������Ƚ�
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC1Init(pwmTIMx,&TIM_OCInitStruct);
	TIM_OC2Init(pwmTIMx,&TIM_OCInitStruct);
	TIM_OC3Init(pwmTIMx,&TIM_OCInitStruct);
	TIM_OC4Init(pwmTIMx,&TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(pwmTIMx,ENABLE);//�߼���ʱ��ר��--MOE�����ʹ��
	
	TIM_OC1PreloadConfig(pwmTIMx,TIM_OCPreload_Enable);/*��3��*///ENABLE//OC1Ԥװ�ؼĴ���ʹ��
	TIM_OC2PreloadConfig(pwmTIMx,TIM_OCPreload_Enable);/*��3��*///ENABLE//OC1Ԥװ�ؼĴ���ʹ��
	TIM_OC3PreloadConfig(pwmTIMx,TIM_OCPreload_Enable);/*��3��*///ENABLE//OC1Ԥװ�ؼĴ���ʹ��
	TIM_OC4PreloadConfig(pwmTIMx,TIM_OCPreload_Enable);//ENABLE//OC4Ԥװ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(pwmTIMx,ENABLE);//TIM1��ARR��Ԥװ�ؼĴ���ʹ��
	//TIM_SetCompare4(TIM8,1400);
	TIM_Cmd(pwmTIMx,ENABLE);//����ʱ����
}


