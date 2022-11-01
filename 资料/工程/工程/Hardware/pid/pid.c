/**
  *************************************************************************************************************************
  * @file    pid.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   pid算法.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "pid.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/
PID_InitTypedef PID;

/**
 * 函数名:PID_Param_Init
 * 描述:PID参数初始
 * 输入:无
 * 输出:无
 */
void  PID_Param_Init(void)
{
  /*位置环的PID*/
	PID.Location_Target_Val=0.0;
	PID.Location_Actual_Val=0.0;
	PID.Location_Kp=0.0;
	PID.Location_Ki=0.0;
	PID.Location_Kd=0.0;
	PID.Location_Integral=0.0;
	PID.Location_Error=0.0;
	PID.Location_ErrorLast=0.0;
	PID.Location_Out=0;
	
	/*速度环的PID*/
	PID.Velocity_Target_Val=0.0;
	PID.Velocity_Actual_Val=0.0;
	PID.Velocity_Kp=0.0;
	PID.Velocity_Ki=0.0;
	PID.Velocity_Kd=0.0;
	PID.Velocity_Integral=0.0;
	PID.Velocity_Error=0.0;
	PID.Velocity_ErrorLast=0.0;
	PID.Velocity_Out=0;
}

/**
 * 函数名:LocationRing_PID_Realize
 * 描述:位置环PID的实现
 * 输入:Location_Actual_Val:测量到的实际值
 * 输出:位置环PID的输出值
 */
float LocationRing_PID_Realize(float Location_Actual_Val)
{ 
  //1.计算偏差
	PID.Location_Error=PID.Location_Target_Val-Location_Actual_Val;
	//2.累计偏差
	PID.Location_Integral+=PID.Location_Error;
	//3.PID算法实现
	PID.Location_Actual_Val=PID.Location_Kp*PID.Location_Error+PID.Location_Ki*PID.Location_Integral+PID.Location_Kd*(PID.Location_Error-PID.Location_ErrorLast);
	//4.偏差的传递
	PID.Location_ErrorLast=PID.Location_Error;
	//5.返回位置环计算得到的输出值
	return PID.Location_Actual_Val;  
}

/**
 * 函数名:LocationRing_PID_Realize
 * 描述:速度环PID的实现
 * 输入:Location_Actual_Val:测量到的实际值
 * 输出:速度环PID的输出值
 */
float VelocityRing_PID_Realize(float Velocity_Actual_Val)
{ 
  //1.计算偏差
	PID.Velocity_Error=PID.Velocity_Target_Val-Velocity_Actual_Val;
	
	//2.消除机械误差
	if((PID.Velocity_Error<0.5f)&&(PID.Velocity_Error>-0.5f))
	{
	 PID.Velocity_Error=0.0f;
	}
	
	//3.累计偏差
	PID.Velocity_Integral+=PID.Velocity_Error;
	
	//4.积分限幅 (限幅值的确定:PWM_MAX÷PID.Velocity_Ki)
	PID.Velocity_Integral=(PID.Velocity_Integral>10000)?PID.Velocity_Integral=10000:((PID.Velocity_Integral<-10000)?PID.Velocity_Integral=-10000:PID.Velocity_Integral);
	
	//5.PID算法实现
	PID.Velocity_Actual_Val=PID.Velocity_Kp*PID.Velocity_Error+PID.Velocity_Ki*PID.Velocity_Integral+PID.Velocity_Kd*(PID.Velocity_Error-PID.Velocity_ErrorLast);
	
	//6.偏差的传递
	PID.Velocity_ErrorLast=PID.Velocity_Error;
	
	
	//7.返回速度环计算得到的输出值
	return PID.Velocity_Actual_Val;  
}

/*****************************************************END OF FILE*********************************************************/	
