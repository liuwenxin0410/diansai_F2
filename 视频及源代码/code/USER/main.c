#include "sys.h"
#include "delay.h"
#include "led.h"
#include "PWM.h"
#include "car.h"
#include "usart.h"
#include <string.h>
#include <math.h>

char source[10];  //�洢���ڻ�������

//�����������������ͬ��������ƫ���Ҫ���н���
#define speed_left 30  //��������
#define  speed_right 27  //��������

u16 num=0;  //�洢�ַ�ת���ε�����


//��������ƫ�������ٺ���
void run(void)
{
	  GO();
		if(num<100)  //��⵽��ƫ
		{
		  TIM_SetCompare1(TIM4,speed_right-num);   //���ּ���
	    TIM_SetCompare2(TIM4,speed_left+num);   //���ּ���
		}
		if(num>=100)  //��⵽��ƫ
		{
			TIM_SetCompare1(TIM4,speed_right+num-100);  //���ּ���
	    TIM_SetCompare2(TIM4,speed_left-num-100);  //���ּ���
		}
}


int simple_atoi(char *source) //�ַ���ת����
{
	int length = strlen(source); //���㳤��
	int sum = 0;
	int i;
	
		for(i=0;i<length;i++) 
	  {
		  sum += (source[i]-'0') * pow(10,length-1-i); //�ַ�ת���ֲ��ϲ�
	  }
	
	for(i=0;i<length;i++) source[i]=0;//��������
	return sum;
}

 void DELAY(unsigned int xms)  //��������ԭ�ӵ���ʱ������protues�����д������⣬���Բ�����д��ʱ����ԼΪ10ms����ʱ
{
	unsigned int j;
	for( ;xms>0;xms--)
	 for(j=1400;j>0;j--);
}


int main(void)
{			 
  u16 t;  
	u16 len;	
	delay_init();  //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(19200);	 //���ڳ�ʼ��Ϊ19200
	GPIO_init_CAR();
	LED_Init();
     
	//��ʼ������
		TIM4_PWM_Init(899,10);  //��ʼ��PWM  8k hz
		TIM_SetCompare1(TIM4,speed_left);  
	  TIM_SetCompare2(TIM4,speed_right);  
	
	while(1)
    {
			 if(USART_RX_STA&0x8000)
			{					   
				len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
				
				for(t=0;t<len;t++)
			  {
				  source[t]=USART_RX_BUF[t];  //��BUF�Ĵ�������ת�Ƶ�source����
			  }
				num = simple_atoi(source);  //��������
				USART_RX_STA=0;
			}	
				
			run();  //��������ƫ��

	}
}
