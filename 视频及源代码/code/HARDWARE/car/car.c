#include "car.h"

void GO(void)  //ǰ��
{
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
	
}

void stop(void)
{
	AIN1=1;
	AIN2=1;
	BIN1=1;
	BIN2=1;
}

void back(void)
{
	AIN1=0;
	AIN2=1;
	BIN1=1;
	BIN2=0;
}

void left(void)
{
	AIN1=0;
	AIN2=0;
	BIN1=1;
	BIN2=0;
}


void right(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=0;
	BIN2=0;
}

void right1(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
}

void GPIO_init_CAR(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;				 //����PA4~7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��PA4~7
  GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);						 //PA4~7�����
}
