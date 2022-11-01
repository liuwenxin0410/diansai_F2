#include "hcsr04.h"

u16 overcount=0; //�������
extern struct MenuItem* MenuPoint;       //�ṹ�����
extern short selectItem;
extern struct MenuItem Setmenu2[3];
//�򿪶�ʱ��
void OpenTimeForHc(void)
{
		//���������
		TIM_SetCounter(TIMX,0);
		overcount=0;
		TIM_Cmd(TIMX,ENABLE);
}

//�رն�ʱ��
void CloseTimeForHc(void)
{
		TIM_Cmd(TIMX,DISABLE);
}

//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
		u32 t=0;
		t=overcount*1000;
		t+=TIM_GetCounter(TIMX);
		//��������0
		TIMX->CNT=0;
		delay_ms(1);
	
		return t;
}


//��������ʼ��
void HCSR04_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
	
	  delay_init();
		RCC_APB2PeriphClockCmd(HCSR04,ENABLE);              //����trig��echo�ӿ�ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMX,ENABLE); //������ʱ��ʱ��
		//trig��-�������
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin=HCSR04_TRIG;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
		//echo��-�������루ֻ��FT���ţ�
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=HCSR04_ECHO;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);
	
		//��ʱ��TIMX��ʼ��
		TIM_DeInit(TIMX);
		TIM_TimeBaseInitStruct.TIM_Period=1000-1;
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIMX,&TIM_TimeBaseInitStruct);
		
		//��ʱ���ж�����_�����ж�
		TIM_ITConfig(TIMX,TIM_IT_Update,ENABLE);
		//�ж�����
		NVIC_InitStruct.NVIC_IRQChannel=TIMX_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStruct);
		//�رն�ʱ��ʹ��
		TIM_Cmd(TIMX,DISABLE);
}


//���������
float Hcsr04GetLength(void)
{
		u32 t=0;
		int i=0;
		float lengthTemp=0;
		float sum=0;
		while(i!=5)
		{
			
				TRIG_Send=1;         //�����źţ���Ϊ�����ź�
				delay_ms(1);         //�ߵ�ƽ�źų���10us
				TRIG_Send=0;         //�����źţ���Ϊ�����ź�
				while(ECHO_Reci==0); //�ȴ������ź�
				OpenTimeForHc();     //�����źŵ�����������ʱ������
				i=i+1;               //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
				while(ECHO_Reci==1); //�ȴ������ź���ʧ
				CloseTimeForHc();  
				t=GetEchoTimer();           //��ȡTIM2����ֵ��ͬʱ��������ź�ʱ��
				lengthTemp=((float)t/58.0); //ͨ�������źż������
				sum+=lengthTemp;
		}
		lengthTemp=sum/5;
		return lengthTemp;  //����
}


//��ʱ���жϣ��������źźܳ�ʱ������ֵ��������ж����������������
void TIMX_IRQHandler(void)
{
		if(TIM_GetITStatus(TIMX,TIM_IT_Update)!=RESET)
		{
				//����жϱ�־λ
				TIM_ClearITPendingBit(TIMX,TIM_IT_Update);
				overcount++;
		}
}
