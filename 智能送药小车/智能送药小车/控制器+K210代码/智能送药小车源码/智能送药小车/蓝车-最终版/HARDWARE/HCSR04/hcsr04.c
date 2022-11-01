#include "hcsr04.h"

u16 overcount=0; //溢出计数
extern struct MenuItem* MenuPoint;       //结构体变量
extern short selectItem;
extern struct MenuItem Setmenu2[3];
//打开定时器
void OpenTimeForHc(void)
{
		//计数器清空
		TIM_SetCounter(TIMX,0);
		overcount=0;
		TIM_Cmd(TIMX,ENABLE);
}

//关闭定时器
void CloseTimeForHc(void)
{
		TIM_Cmd(TIMX,DISABLE);
}

//获取定时器时间
u32 GetEchoTimer(void)
{
		u32 t=0;
		t=overcount*1000;
		t+=TIM_GetCounter(TIMX);
		//计数器清0
		TIMX->CNT=0;
		delay_ms(1);
	
		return t;
}


//超声波初始化
void HCSR04_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
	
	  delay_init();
		RCC_APB2PeriphClockCmd(HCSR04,ENABLE);              //开启trig和echo接口时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMX,ENABLE); //开启定时器时钟
		//trig脚-推挽输出
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin=HCSR04_TRIG;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
		//echo脚-浮空输入（只限FT引脚）
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=HCSR04_ECHO;
		GPIO_Init(HCSR04_PORT,&GPIO_InitStruct);
		GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);
	
		//定时器TIMX初始化
		TIM_DeInit(TIMX);
		TIM_TimeBaseInitStruct.TIM_Period=1000-1;
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIMX,&TIM_TimeBaseInitStruct);
		
		//定时器中断配置_更新中断
		TIM_ITConfig(TIMX,TIM_IT_Update,ENABLE);
		//中断配置
		NVIC_InitStruct.NVIC_IRQChannel=TIMX_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStruct);
		//关闭定时器使能
		TIM_Cmd(TIMX,DISABLE);
}


//超声波测距
float Hcsr04GetLength(void)
{
		u32 t=0;
		int i=0;
		float lengthTemp=0;
		float sum=0;
		while(i!=5)
		{
			
				TRIG_Send=1;         //拉高信号，作为触发信号
				delay_ms(1);         //高电平信号超过10us
				TRIG_Send=0;         //拉低信号，作为触发信号
				while(ECHO_Reci==0); //等待回响信号
				OpenTimeForHc();     //回响信号到来，开启定时器计数
				i=i+1;               //每收到一次回响信号+1，收到5次就计算均值
				while(ECHO_Reci==1); //等待回响信号消失
				CloseTimeForHc();  
				t=GetEchoTimer();           //获取TIM2计数值，同时计算回响信号时间
				lengthTemp=((float)t/58.0); //通过回响信号计算距离
				sum+=lengthTemp;
		}
		lengthTemp=sum/5;
		return lengthTemp;  //厘米
}


//定时器中断（当回响信号很长时，计数值溢出后，用中断来保存溢出次数）
void TIMX_IRQHandler(void)
{
		if(TIM_GetITStatus(TIMX,TIM_IT_Update)!=RESET)
		{
				//清除中断标志位
				TIM_ClearITPendingBit(TIMX,TIM_IT_Update);
				overcount++;
		}
}
