/**
  ******************************************************************************
  * @file    main.c
  * @author  AMKL
  * @version V1.0
  * @date    2022-09-28
  * @brief   2021年全国大学生电子设计竞赛F题-智能送药小车
  ******************************************************************************
  * @attention
  *
  * 主控器:STM32F103C8T6最小系统板
	* 数字识别:K210
	* 路线识别:OpenMV4Plus
	* 驱动器:TB6612FNG
	* 电  机:直流减速电机-13线，减速比30
	* 电  源:DC12V
	* 开发环境: RealView MDK-ARM uVision5
  *	C编译器 : ARMCC
	*
  ******************************************************************************
  */ 
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"

/* 定义 -----------------------------------------------------------------------------------------------------------------*/
uint8_t TargerNum;
uint8_t RoadLineCheck[2]={0,0};
uint8_t RoadLine;

/**
 * 函数名:main  
 * 描述:主函数
 * 输入:无
 * 输出:无
 */
int main(void)
{
	SysTick_Init();//滴答定时器初始化	
	NVIC_Config();//中断优先级分组2
	Usart1_Init(115200);//115200-8-N-1
	Usart2_Init(115200);//115200-8-N-1
	Usart3_Init(115200);//115200-8-N-1
	Tim3_Init();//定时器3-10ms定时
	TIM1_PWM_Init(0,7199);//10khz驱动电机
	TIM2_Encoder_Init();//定时器2编码器配置
	TIM4_Encoder_Init();//定时器4编码器配置
	LED_GPIO_Config();//LED模块对应gpio初始化
	Motor_GPIO_Init();//电机对应引脚初始化
	Infrafred_GPIO_Init();//红外传感器模块对应gpio初始化
	while(1)
	{
		if(Flag.Run_Step==0)
		{
			//1.在串口中断服务函数中实时获取识别到的目标病房，TargerNum
			//2.检测药物装载
			while(LoadOrNot()==0);
			//3.将刚才识别到目标病房号回传给摄像头，以便于识别匹配
			//4.设置目标病房，(分为3种-1号，2号，非近端)，根据TargetNum，设置RoadLineCheck[0]=(1/2/3)。Flag.Run_Step=1;		
		}
		else if(Flag.Run_Step==1)//开始运行，送药/返回
		{
		  if(LoadOrNot()==1)//当前为送药
			{
			 if(RoadLineCheck[0]==1)//1号病房，固定路线
			 {
			   RoadLine=1;//记忆返回路线
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3); //到达第一个十字路口中心
									 Param.Send_Step=1;
					 break;
					 case 1: 
									if(Flag.Stop_Car==1)
									{
									 Car_Spin(LEFT_90);//进行左转
									 Param.Send_Step=2;
									}
					 break;
					 case 2: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//直行到药房
									 Param.Send_Step=3;
									}
					 break;
					 case 3: 
									if(Flag.Stop_Car==1)
									{
										LED_RED=1;//送药完成，点亮红灯，等待取药
									}
					 break;								
					 default:break;				   
				 }
			 }
			 			 else if(RoadLineCheck[0]==2)//2号病房，固定路线
			 {
			   RoadLine=2;//记忆返回路线
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3); //到达第一个十字路口中心
									 Param.Send_Step=1;
					 break;
					 case 1: 
									if(Flag.Stop_Car==1)
									{
									 Car_Spin(RIGHT_90);//右转
									 Param.Send_Step=2;
									}
					 break;
					 case 2: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//直行到药房
									 Param.Send_Step=3;
									}
					 break;
					 case 3: 
									if(Flag.Stop_Car==1)
									{
										LED_RED=1;//送药完成，点亮红灯，等待取药
									}
					 break;								
					 default:break;				   
				 }				 
			 }
			 else //非近端
			 {	
				 switch(Param.Send_Step)
				 {
					 case 0: 
						       Car_Tracking(12+60+15-3+90-25-12); //直行到第二个十字路口前，等待识别
									 Param.Send_Step=1;
					 break;	
					 case 1: 
									if(Flag.Stop_Car==1)
									{
										//开始识别匹配，三种情况，1，识别到在中端的左边  2.识别到在中端的右边  3.未识别在远端
										/*
										 1，识别到在中端的左边 
											Param.Send_Step=6;
											RoadLine=3;//记忆返回路线
										  Car_Tracking(12+25); //填补识别的距离，到达第二个十字路口的中心，进行转弯
										 2，识别到在中端的右边 
											Param.Send_Step=6;
											RoadLine=4;//记忆返回路线
										  Car_Tracking(12+25); //填补识别的距离，到达第二个十字路口的中心，进行转弯		
										 3，未识别 
											Param.Send_Step=2;
										  Car_Tracking(12+25+90-25-12); //到达T型路口前等待识别										
										*/
									}
					 break;		
					 case 2: 
						       if(Flag.Stop_Car==1)//开始进行识别匹配，俩种情况1.左转2.右转
									 {
										/*
										 1，识别到在左边 
											Param.Send_Step=3;
											RoadLineCheck[0]=4;//记忆第一个返回路线的校验位
										  Car_Tracking(12+25); //填补识别的距离，到达第二个十字路口的中心，进行转弯
										 2，识别到在右边 
											Param.Send_Step=3;
											RoadLineCheck[0]=6;//记忆第一个返回路线的校验位
										  Car_Tracking(12+25); //填补识别的距离，到达第二个十字路口的中心，进行转弯										
										*/									  									 
									 }
					 break;		
					 case 3: 
									if(Flag.Stop_Car==1)
									{
									  if(RoadLineCheck[0]==4)//左转
										{
										 Car_Spin(LEFT_90);
										 Param.Send_Step=4;										 
										}
										else if(RoadLineCheck[0]==6)//右转
										{
										 Car_Spin(RIGHT_90);
										 Param.Send_Step=4;										 
										}
									}
					 break;
					 case 4: 
									if(Flag.Success_Spin==1)
									{
										Car_Tracking(90-25-12);//到达了第二个T型路口前，进行识别
										Param.Send_Step=5;	
									}
					 break;		
					 case 5: 
									if(Flag.Stop_Car==1)
									{
										//开始进行识别匹配，俩种情况1.左转2.右转
									  /*
										 1，识别到在左边 
											Param.Send_Step=6;
											RoadLineCheck[1]=1;//记忆第二个返回路线的校验位
											RoadLine=RoadLineCheck[0]+RoadLineCheck[1];//记忆返回路线
										  Car_Tracking(12+25); //填补识别的距离，，进行转弯
										 2，识别到在右边 
											Param.Send_Step=6;
											RoadLineCheck[1]=2;//记忆第二个返回路线的校验位
											RoadLine=RoadLineCheck[0]+RoadLineCheck[1];
										  Car_Tracking(12+25); //填补识别的距离，进行转弯										
										*/	
									}
					 break;	
					 case 6: 
									if(Flag.Stop_Car==1)
									{
									  if(RoadLine==3||RoadLine==5||RoadLine==8)//左转
										{
										 Car_Spin(LEFT_90);
										 Param.Send_Step=7;										 
										}
										else if(RoadLine==4||RoadLine==6||RoadLine==7)//右转
										{
										 Car_Spin(RIGHT_90);
										 Param.Send_Step=7;										 
										}
									}
					 break;		
					 case 7: 
									if(Flag.Success_Spin==1)
									{
									 Car_Tracking(15+40-12-3);//直行到药房
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
 		  else if(LoadOrNot()==2)//当前为返回药房
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
											Car_Tracking(15+40-12-3);//直行到十字路口中心
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
											Car_Tracking(12+60+15-3);//直行到药房
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
											Car_Tracking(15+40-12-3);//直行到十字路口中心
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
											Car_Tracking(12+60+15-3);//直行到药房
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
											Car_Tracking(15+40-12-3);//直行到十字路口中心
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
											Car_Tracking(12+60+15-3+90);//直行到药房
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
											Car_Tracking(15+40-12-3);//直行到十字路口中心
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
											Car_Tracking(12+60+15-3+90);//直行到药房
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
											Car_Tracking(15+40-12-3);//直行到T字路口中心
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
											Car_Tracking(90);//直行到返回途中的第二个T字路口中心
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
											Car_Tracking(12+60+15-3+90+90);//直行到了药房
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
											Car_Tracking(15+40-12-3);//直行到T字路口中心
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
											Car_Tracking(90);//直行到返回途中的第二个T字路口中心
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
											Car_Tracking(12+60+15-3+90+90);//直行到了药房
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
											Car_Tracking(15+40-12-3);//直行到T字路口中心
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
											Car_Tracking(90);//直行到返回途中的第二个T字路口中心
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
											Car_Tracking(12+60+15-3+90+90);//直行到了药房
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
											Car_Tracking(15+40-12-3);//直行到T字路口中心
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
											Car_Tracking(90);//直行到返回途中的第二个T字路口中心
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
											Car_Tracking(12+60+15-3+90+90);//直行到了药房
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
