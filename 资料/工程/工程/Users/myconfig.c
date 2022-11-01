/**
  *************************************************************************************************************************
  * @file    myconfig.c
  * @author  AMKL
  * @version V1.0
  * @date    2022-09-22
  * @brief   STM32F103C8T6  
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"

/* 定义 -----------------------------------------------------------------------------------------------------------------*/
Param_InitTypeDef Param;
Flag_InitTypeDef  Flag;

/**
 * 函数名:LocationRing_Out
 * 描述:位置环的输出函数
 * 输入:无
 * 输出:速度环的期望值
 */
float LocationRing_Out(void)
{
 float ExpectVelocity=0.0;
	
	PID.Location_Actual_Val=Param.Sigma_Motor1Pluse;//将累计脉冲数传递给位置环的实际值
	
	ExpectVelocity=LocationRing_PID_Realize(PID.Location_Actual_Val);//得到期望的速度
	
	ExpectVelocity=(ExpectVelocity>MOTOR_SPEED_MAX)?MOTOR_SPEED_MAX:(ExpectVelocity<-MOTOR_SPEED_MAX)?(-MOTOR_SPEED_MAX):ExpectVelocity;//进行的速度限幅
	
	return ExpectVelocity;
}

/**
 * 函数名:VelocityRing_Out
 * 描述:速度环的输出函数
 * 输入:无
 * 输出:PWM
 */
float VelocityRing_Out(void)
{
  float EcpectPWM=0.0;
	
	PID.Velocity_Actual_Val=(Param.UnitTime_Motor1Pluse/(RESOLUTION_TOTAL*REDUCTION_RATIO*PID_COMPUTATION_PERIOD))*1000*60;//将读取到的单位时间内的脉冲数转为单位为rpm
	
	EcpectPWM=VelocityRing_PID_Realize(PID.Velocity_Actual_Val);//得到了期望速度
	
	return EcpectPWM	;
}	

/**
 * 函数名:LocationRing_VelocityRing_Control
 * 描述:串级pid的控制
 * 输入:无
 * 输出:无
 */
void LocationRing_VelocityRing_Control(void)
{
  PID.Velocity_Target_Val=LocationRing_Out();
	
	PID.Velocity_Out=VelocityRing_Out(); 
}

/**
 * 函数名:Car_Tracking
 * 描述:直行巡线
 * 输入:无
 * 输出:无
 */
void Car_Tracking(uint16_t TargetDistance)
{
  Flag.Stop_Car=0;
  Flag.Start_Line=1;	
	Flag.Start_Spin=0;
	Flag.Success_Spin=0;
	Param.UnitTime_Motor1Pluse=0;
	Param.UnitTime_Motor2Pluse=0;
	Param.Sigma_Motor1Pluse=0;
	Param.Sigma_Motor2Pluse=0;
	
	
	//1.将目标距离赋值给目标距离阈值
  Param.Distance_TargetThreshold=TargetDistance;
	
	//2.将目标距离转化为脉冲数 距离/周长得到需要转的圈数×一圈所需的脉冲数，得到了期望的脉冲数
	PID.Location_Target_Val=((TargetDistance/(2*3.14*WHEEL_R))*(RESOLUTION_TOTAL*REDUCTION_RATIO));
	
	//3.使能电机
	set_motor_enable();
}

/**
 * 函数名:Car_Spin
 * 描述:转弯
 * 输入:Direction=(LEFT_90/RIGHT_90/SPIN_180)
 * 输出:无
 */
void Car_Spin(SpinDIR_Choose Direction)
{
  Flag.Stop_Car=0;
  Flag.Start_Line=0;	
	Flag.Start_Spin=1;
	Flag.Success_Spin=0;
	Param.UnitTime_Motor1Pluse=0;
	Param.UnitTime_Motor2Pluse=0;
	Param.Sigma_Motor1Pluse=0;
	Param.Sigma_Motor2Pluse=0; 
	
	if(LEFT_90==Direction)
	{
	  PID.Location_Target_Val=((SPIN_90_DISTANCE/(2*3.14*WHEEL_R))*(RESOLUTION_TOTAL*REDUCTION_RATIO));
		Motor_Left_DIR(BACK);
		Motor_Right_DIR(FORWARD);
	}
	else if(RIGHT_90==Direction)
	{
	  PID.Location_Target_Val=((SPIN_90_DISTANCE/(2*3.14*WHEEL_R))*(RESOLUTION_TOTAL*REDUCTION_RATIO));
		Motor_Left_DIR(FORWARD);
		Motor_Right_DIR(BACK);	 
	}
	else if(SPIN_180==Direction)
	{
	  PID.Location_Target_Val=2*((SPIN_90_DISTANCE/(2*3.14*WHEEL_R))*(RESOLUTION_TOTAL*REDUCTION_RATIO));
		Motor_Left_DIR(FORWARD);
		Motor_Right_DIR(BACK);	 	 
	}	

	set_motor_enable();	
}

/**
 * 函数名:TIM3_IRQHandler
 * 描述:定时3中断服务函数-10ms定时基准
 * 输入:无
 * 输出:无
 */
void TIM3_IRQHandler(void)
{
	uint8_t stop_time_cnt,spin_time_cnt;
	long    average_pluse;
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
	  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
		//1.获取单位时间内脉冲数
		Param.UnitTime_Motor1Pluse = -Read_Pluse(2);
		Param.UnitTime_Motor2Pluse = Read_Pluse(4);
		
		//2.更新累计脉冲数
		Param.Sigma_Motor1Pluse+=Param.UnitTime_Motor1Pluse;
		Param.Sigma_Motor2Pluse+=Param.UnitTime_Motor2Pluse;
		
		//3.更新小车当前的行驶距离=(周期内累计脉冲/((车轮走一圈产生的脉冲数)*(车轮周长)))
		Param.Distance_Motor1Curret=Param.Sigma_Motor1Pluse/((RESOLUTION_TOTAL*REDUCTION_RATIO)*(2*3.14*WHEEL_R));
		
		//4.巡线环，获取openMV巡线对应的情况产生的对应输出值Line_TempOut
		/*
		为了便于上下文理解，先预想出各种情况的对应方案
		直线-Line_TempOut=0;
		左转-Line_TempOut=1800;
		右转-Line_TempOut=-1800;
		*/
		
		//5.判断是否开启巡线功能
		if(Flag.Start_Line==1)
		{
		  //判断是否到了目标距离的最小阈值，到达即开始停车
			if((Param.Distance_Motor1Curret<=Param.Distance_TargetThreshold+CAR_LENGTH)&&(Param.Distance_Motor1Curret>=Param.Distance_TargetThreshold-CAR_LENGTH))
			{
			  if(++stop_time_cnt==200)//2S
				{
				  stop_time_cnt=0;
					Flag.Start_Line=0;
					Flag.Stop_Car=1;
					set_motor_disable();
				}
			}
			else
			{
			  stop_time_cnt=0;
				Flag.Stop_Car=0;
			}
			//判断电机是否启动
			if(Flag.Is_EnMOTOR==1)
			{
			  LocationRing_VelocityRing_Control();
				//解决车未走直线或者打滑的情况导致的俩轮累计脉冲数不相等的情况
				if(Param.Line_TempOut==0)
				{
					average_pluse=(Param.Sigma_Motor1Pluse+Param.Sigma_Motor2Pluse)/2;
					Param.Sigma_Motor1Pluse=Param.Sigma_Motor2Pluse=average_pluse;				 
				}
			}
			//巡线补偿
			Param.Motor1_PWM=PID.Velocity_Out-Param.Line_TempOut;
			Param.Motor2_PWM=PID.Velocity_Out+Param.Line_TempOut;
			
			(Param.Motor1_PWM>0)?Motor_Left_DIR(FORWARD):Motor_Left_DIR(BACK);
			(Param.Motor2_PWM>0)?Motor_Right_DIR(FORWARD):Motor_Right_DIR(BACK);
			
			Load_Motor_PWM(Param.Motor1_PWM,Param.Motor2_PWM);
		}
		//6.判断是否开启转弯功能
		if(Flag.Start_Spin==1)
		{
		  //判断是否启动电机
			if(Flag.Is_EnMOTOR==1)
			{
			  LocationRing_VelocityRing_Control();
				Param.Motor1_PWM=PID.Velocity_Out;
				Param.Motor2_PWM=PID.Velocity_Out;
			}
			if(++spin_time_cnt==200)
			{
			  spin_time_cnt=0;
				Flag.Start_Spin=0;
				Flag.Success_Spin=1;
				Param.Motor1_PWM=0;
				Param.Motor2_PWM=0;
			}
			Load_Motor_PWM(Param.Motor1_PWM,Param.Motor2_PWM);
		}		
	}
}

/*****************************************************END OF FILE*********************************************************/	
