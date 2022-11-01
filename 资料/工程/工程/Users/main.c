/**
  ******************************************************************************
  * @file    main.c
  * @author  AMKL
  * @version V1.0
  * @date    2022-09-28
  * @brief   2021��ȫ����ѧ��������ƾ���F��-������ҩС��
  ******************************************************************************
  * @attention
  *
  * ������:STM32F103C8T6��Сϵͳ��
	* ����ʶ��:K210
	* ·��ʶ��:OpenMV4Plus
	* ������:TB6612FNG
	* ��  ��:ֱ�����ٵ��-13�ߣ����ٱ�30
	* ��  Դ:DC12V
	* ��������: RealView MDK-ARM uVision5
  *	C������ : ARMCC
	*
  ******************************************************************************
  */ 
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"

/* ���� -----------------------------------------------------------------------------------------------------------------*/
uint8_t TargerNum;
uint8_t RoadLineCheck[2]={0,0};
uint8_t RoadLine;

/**
 * ������:main  
 * ����:������
 * ����:��
 * ���:��
 */
int main(void)
{
	SysTick_Init();//�δ�ʱ����ʼ��	
	NVIC_Config();//�ж����ȼ�����2
	Usart1_Init(115200);//115200-8-N-1
	Usart2_Init(115200);//115200-8-N-1
	Usart3_Init(115200);//115200-8-N-1
	Tim3_Init();//��ʱ��3-10ms��ʱ
	TIM1_PWM_Init(0,7199);//10khz�������
	TIM2_Encoder_Init();//��ʱ��2����������
	TIM4_Encoder_Init();//��ʱ��4����������
	LED_GPIO_Config();//LEDģ���Ӧgpio��ʼ��
	Motor_GPIO_Init();//�����Ӧ���ų�ʼ��
	Infrafred_GPIO_Init();//���⴫����ģ���Ӧgpio��ʼ��
	while(1)
	{
		if(Flag.Run_Step==0)
		{
			//1.�ڴ����жϷ�������ʵʱ��ȡʶ�𵽵�Ŀ�겡����TargerNum
			//2.���ҩ��װ��
			while(LoadOrNot()==0);
			//3.���ղ�ʶ��Ŀ�겡���Żش�������ͷ���Ա���ʶ��ƥ��
			//4.����Ŀ�겡����(��Ϊ3��-1�ţ�2�ţ��ǽ���)������TargetNum������RoadLineCheck[0]=(1/2/3)��Flag.Run_Step=1;		
		}
		else if(Flag.Run_Step==1)//��ʼ���У���ҩ/����
		{
		  if(LoadOrNot()==1)//��ǰΪ��ҩ
			{
			 if(RoadLineCheck[0]==1)//1�Ų������̶�·��
			 {
			   RoadLine=1;//���䷵��·��
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3); //�����һ��ʮ��·������
									 Param.Send_Step=1;
					 break;
					 case 1: 
									if(Flag.Stop_Car==1)
									{
									 Car_Spin(LEFT_90);//������ת
									 Param.Send_Step=2;
									}
					 break;
					 case 2: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//ֱ�е�ҩ��
									 Param.Send_Step=3;
									}
					 break;
					 case 3: 
									if(Flag.Stop_Car==1)
									{
										LED_RED=1;//��ҩ��ɣ�������ƣ��ȴ�ȡҩ
									}
					 break;								
					 default:break;				   
				 }
			 }
			 			 else if(RoadLineCheck[0]==2)//2�Ų������̶�·��
			 {
			   RoadLine=2;//���䷵��·��
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3); //�����һ��ʮ��·������
									 Param.Send_Step=1;
					 break;
					 case 1: 
									if(Flag.Stop_Car==1)
									{
									 Car_Spin(RIGHT_90);//��ת
									 Param.Send_Step=2;
									}
					 break;
					 case 2: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//ֱ�е�ҩ��
									 Param.Send_Step=3;
									}
					 break;
					 case 3: 
									if(Flag.Stop_Car==1)
									{
										LED_RED=1;//��ҩ��ɣ�������ƣ��ȴ�ȡҩ
									}
					 break;								
					 default:break;				   
				 }				 
			 }
			 else //�ǽ���
			 {	
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3+90-25-12); //ֱ�е��ڶ���ʮ��·��ǰ���ȴ�ʶ��
									 Param.Send_Step=1;
					 break;	
					 case 1: 
									if(Flag.Stop_Car==1)
									{
										//��ʼʶ��ƥ�䣬���������1��ʶ�����ж˵����  2.ʶ�����ж˵��ұ�  3.δʶ����Զ��
										/*
										 1��ʶ�����ж˵���� 
											Param.Send_Step=6;
											RoadLine=3;//���䷵��·��
										  Car_Tracking(12+25); //�ʶ��ľ��룬����ڶ���ʮ��·�ڵ����ģ�����ת��
										 2��ʶ�����ж˵��ұ� 
											Param.Send_Step=6;
											RoadLine=4;//���䷵��·��
										  Car_Tracking(12+25); //�ʶ��ľ��룬����ڶ���ʮ��·�ڵ����ģ�����ת��		
										 3��δʶ�� 
											Param.Send_Step=2;
										  Car_Tracking(12+25+90-25-12); //����T��·��ǰ�ȴ�ʶ��										
										*/
									}
					 break;		
					 case 2: 
						       if(Flag.Stop_Car==1)//��ʼ����ʶ��ƥ�䣬�������1.��ת2.��ת
									 {
										/*
										 1��ʶ������� 
											Param.Send_Step=3;
											RoadLineCheck[0]=4;//�����һ������·�ߵ�У��λ
										  Car_Tracking(12+25); //�ʶ��ľ��룬����ڶ���ʮ��·�ڵ����ģ�����ת��
										 2��ʶ�����ұ� 
											Param.Send_Step=3;
											RoadLineCheck[0]=6;//�����һ������·�ߵ�У��λ
										  Car_Tracking(12+25); //�ʶ��ľ��룬����ڶ���ʮ��·�ڵ����ģ�����ת��										
										*/									  									 
									 }
					 break;		
					 case 3: 
									if(Flag.Stop_Car==1)
									{
									  if(RoadLineCheck[0]==4)//��ת
										{
										 Car_Spin(LEFT_90);
										 Param.Send_Step=4;										 
										}
										else if(RoadLineCheck[0]==6)//��ת
										{
										 Car_Spin(RIGHT_90);
										 Param.Send_Step=4;										 
										}
									}
					 break;
					 case 4: 
									if(Flag.Success_Spin==1)
									{
										Car_Tracking(90-25-12);//�����˵ڶ���T��·��ǰ������ʶ��
										Param.Send_Step=5;	
									}
					 break;		
					 case 5: 
									if(Flag.Stop_Car==1)
									{
										//��ʼ����ʶ��ƥ�䣬�������1.��ת2.��ת
									  /*
										 1��ʶ������� 
											Param.Send_Step=6;
											RoadLineCheck[1]=1;//����ڶ�������·�ߵ�У��λ
											RoadLine=RoadLineCheck[0]+RoadLineCheck[1];//���䷵��·��
										  Car_Tracking(12+25); //�ʶ��ľ��룬������ת��
										 2��ʶ�����ұ� 
											Param.Send_Step=6;
											RoadLineCheck[1]=2;//����ڶ�������·�ߵ�У��λ
											RoadLine=RoadLineCheck[0]+RoadLineCheck[1];
										  Car_Tracking(12+25); //�ʶ��ľ��룬����ת��										
										*/	
									}
					 break;	
					 case 6: 
									if(Flag.Stop_Car==1)
									{
									  if(RoadLine==3||RoadLine==5||RoadLine==8)//��ת
										{
										 Car_Spin(LEFT_90);
										 Param.Send_Step=7;										 
										}
										else if(RoadLine==4||RoadLine==6||RoadLine==7)//��ת
										{
										 Car_Spin(RIGHT_90);
										 Param.Send_Step=7;										 
										}
									}
					 break;		
					 case 7: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//ֱ�е�ҩ��
									 Param.Send_Step=8;
									}
					 break;		
					 case 8: 
									if(Flag.Stop_Car==1)
									{
										LED_RED;
									}
					 break;											
					 default:break;						 
				 }					 
			 }			
		 }
 		  else if(LoadOrNot()==2)//��ǰΪ����ҩ��
			{
				if(RoadLine==1)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�ʮ��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3);//ֱ�е�ҩ��
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN=1;
										}								
						break;											
						default:break;
					}
				}
				else if(RoadLine==2)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�ʮ��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3);//ֱ�е�ҩ��
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN=1;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==3)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�ʮ��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90);//ֱ�е�ҩ��
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN=1;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==4)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�ʮ��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90);//ֱ�е�ҩ��
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN=1;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==5)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�T��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(90);//ֱ�е�����;�еĵڶ���T��·������
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=5;
										}								
						break;	
						case 5: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90+90);//ֱ�е���ҩ��
											Param.Back_Step=6;
										}								
						break;	
						case 6: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==6)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�T��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(90);//ֱ�е�����;�еĵڶ���T��·������
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=5;
										}								
						break;	
						case 5: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90+90);//ֱ�е���ҩ��
											Param.Back_Step=6;
										}								
						break;	
						case 6: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==7)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�T��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(90);//ֱ�е�����;�еĵڶ���T��·������
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=5;
										}								
						break;	
						case 5: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90+90);//ֱ�е���ҩ��
											Param.Back_Step=6;
										}								
						break;	
						case 6: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN;
										}								
						break;											
						default:break;
					}
				}	
				else if(RoadLine==8)
				{
				  switch(Param.Back_Step)
					{
						case 0: 
						        Car_Spin(SPIN_180);
										LED_RED=0;
										Param.Back_Step=1;
						break;
						case 1: 
										if(Flag.Success_Spin==1)
										{
											Car_Tracking(15+40-12-3);//ֱ�е�T��·������
											Param.Back_Step=2;
										}
						break;
						case 2: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(RIGHT_90);
											Param.Back_Step=3;
										}								
						break;	
						case 3: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(90);//ֱ�е�����;�еĵڶ���T��·������
											Param.Back_Step=4;
										}								
						break;
						case 4: 
						        if(Flag.Stop_Car==1)
										{
											Car_Spin(LEFT_90);
											Param.Back_Step=5;
										}								
						break;	
						case 5: 
						        if(Flag.Success_Spin==1)
										{
											Car_Tracking(12+60+15-3+90+90);//ֱ�е���ҩ��
											Param.Back_Step=6;
										}								
						break;	
						case 6: 
						        if(Flag.Stop_Car==1)
										{
											LED_GREEN;
										}								
						break;											
						default:break;
					}
				}						
			}	 
		}				
	}
}
/*****************************************************END OF FILE*********************************************************/	
