#include "sys.h"
#include "delay.h"
#include "led.h"
#include "PWM.h"
#include "car.h"
#include "usart.h"
#include <string.h>
#include <math.h>

char source[10];
#define speed_left 47
#define  speed_right 50
u16 num=0;

void run(void)
{
	  GO();
		if(num<100)
		{
			if(num==50) LED0 = 1;
			if(num==20) LED0 = 0;
		  TIM_SetCompare1(TIM4,speed_left-num);  
	    TIM_SetCompare2(TIM4,speed_right+num); 
		}
//		if(num>=100)
//		{
//			if(num==150) LED0 = 1;
//			if(num==120) LED0 = 0;
//			TIM_SetCompare1(TIM4,speed_left+num-100);  
//	    TIM_SetCompare2(TIM4,speed_right-num-100);
//		}
}


int simple_atoi(char *source) //字符串转整形
{
	int length = strlen(source); //计算长度
	int sum = 0;
	int i;
	if(source[0]=='-')//如果为负数
	{
	  for(i=0;i<length;i++) 
	  {
		  sum += (source[i+1]-'0') * pow(10,length-2-i); //字符转数字并合并
			sum = -sum;
	  }
	}
	else //如果不为负数
	{
		for(i=0;i<length;i++) 
	  {
		  sum += (source[i]-'0') * pow(10,length-1-i); //字符转数字并合并
	  }
	}
	
	for(i=0;i<length;i++) source[i]=0;//清零数组
	return sum;
}

 void DELAY(unsigned int xms)  //由于正点原子的延时函数在protues运用中存在问题，所以才有手写延时，大约为10ms级延时
{
	unsigned int j;
	for( ;xms>0;xms--)
	 for(j=1400;j>0;j--);
}


int main(void)
{			 
  u16 t;  
	u16 len;	
	delay_init();  //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(19200);	 //串口初始化为19200
	GPIO_init_CAR();
	LED_Init();
     
	//初始化车速
		TIM4_PWM_Init(899,10);  //初始化PWM  8k hz
		TIM_SetCompare1(TIM4,30);  
	  TIM_SetCompare2(TIM4,30);  
	
	while(1)
    {
			 if(USART_RX_STA&0x8000)
			{					   
				len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
				
				for(t=0;t<len;t++)
			  {
				  source[t]=USART_RX_BUF[t];
			  }
				num = simple_atoi(source);
				USART_RX_STA=0;
			}	
				
			run();

	}
}
