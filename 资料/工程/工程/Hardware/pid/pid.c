/**
  *************************************************************************************************************************
  * @file    pid.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   pid�㷨.c�ļ�����
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "pid.h"
/* ���� -----------------------------------------------------------------------------------------------------------------*/
PID_InitTypedef PID;

/**
 * ������:PID_Param_Init
 * ����:PID������ʼ
 * ����:��
 * ���:��
 */
void  PID_Param_Init(void)
{
  /*λ�û���PID*/
	PID.Location_Target_Val=0.0;
	PID.Location_Actual_Val=0.0;
	PID.Location_Kp=0.0;
	PID.Location_Ki=0.0;
	PID.Location_Kd=0.0;
	PID.Location_Integral=0.0;
	PID.Location_Error=0.0;
	PID.Location_ErrorLast=0.0;
	PID.Location_Out=0;
	
	/*�ٶȻ���PID*/
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
 * ������:LocationRing_PID_Realize
 * ����:λ�û�PID��ʵ��
 * ����:Location_Actual_Val:��������ʵ��ֵ
 * ���:λ�û�PID�����ֵ
 */
float LocationRing_PID_Realize(float Location_Actual_Val)
{ 
  //1.����ƫ��
	PID.Location_Error=PID.Location_Target_Val-Location_Actual_Val;
	//2.�ۼ�ƫ��
	PID.Location_Integral+=PID.Location_Error;
	//3.PID�㷨ʵ��
	PID.Location_Actual_Val=PID.Location_Kp*PID.Location_Error+PID.Location_Ki*PID.Location_Integral+PID.Location_Kd*(PID.Location_Error-PID.Location_ErrorLast);
	//4.ƫ��Ĵ���
	PID.Location_ErrorLast=PID.Location_Error;
	//5.����λ�û�����õ������ֵ
	return PID.Location_Actual_Val;  
}

/**
 * ������:LocationRing_PID_Realize
 * ����:�ٶȻ�PID��ʵ��
 * ����:Location_Actual_Val:��������ʵ��ֵ
 * ���:�ٶȻ�PID�����ֵ
 */
float VelocityRing_PID_Realize(float Velocity_Actual_Val)
{ 
  //1.����ƫ��
	PID.Velocity_Error=PID.Velocity_Target_Val-Velocity_Actual_Val;
	
	//2.������е���
	if((PID.Velocity_Error<0.5f)&&(PID.Velocity_Error>-0.5f))
	{
	 PID.Velocity_Error=0.0f;
	}
	
	//3.�ۼ�ƫ��
	PID.Velocity_Integral+=PID.Velocity_Error;
	
	//4.�����޷� (�޷�ֵ��ȷ��:PWM_MAX��PID.Velocity_Ki)
	PID.Velocity_Integral=(PID.Velocity_Integral>10000)?PID.Velocity_Integral=10000:((PID.Velocity_Integral<-10000)?PID.Velocity_Integral=-10000:PID.Velocity_Integral);
	
	//5.PID�㷨ʵ��
	PID.Velocity_Actual_Val=PID.Velocity_Kp*PID.Velocity_Error+PID.Velocity_Ki*PID.Velocity_Integral+PID.Velocity_Kd*(PID.Velocity_Error-PID.Velocity_ErrorLast);
	
	//6.ƫ��Ĵ���
	PID.Velocity_ErrorLast=PID.Velocity_Error;
	
	
	//7.�����ٶȻ�����õ������ֵ
	return PID.Velocity_Actual_Val;  
}

/*****************************************************END OF FILE*********************************************************/	
