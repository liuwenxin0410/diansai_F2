/**
  *************************************************************************************************************************
  * @file    pid.h
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   pid�㷨.h�ļ�����
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __PID_H 
#define	__PID_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"

/* ���� -----------------------------------------------------------------------------------------------------------------*/
typedef struct
{
  float Location_Kp;//λ�û���Kp
	float Location_Ki;//λ�û���Ki
	float Location_Kd;//λ�û���Kd
	float Location_Error;//λ�û���ƫ��
	float Location_ErrorLast;//λ�û�����һ��ƫ��
	float Location_Integral;//λ�û��Ļ���ֵ
	float Location_Target_Val;//λ�û�������ֵ
	float Location_Actual_Val;//λ�û���ʵ��ֵ
	int   Location_Out;//λ�û������

	float Velocity_Kp;//�ٶȻ���Kp
	float Velocity_Ki;//�ٶȻ���Ki
	float Velocity_Kd;//�ٶȻ���Kd
	float Velocity_Error;//�ٶȻ���ƫ��
	float Velocity_ErrorLast;//�ٶȻ�����һ��ƫ��
	float Velocity_Integral;//�ٶȻ��Ļ�����
	float Velocity_Target_Val;//�ٶȻ�������ֵ
	float Velocity_Actual_Val;//�ٶȻ���ʵ��ֵ
	int   Velocity_Out;//�ٶȻ������
	
}PID_InitTypedef;



/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/
extern PID_InitTypedef PID;

void  PID_Param_Init(void);
float LocationRing_PID_Realize(float Location_Actual_Val);
float VelocityRing_PID_Realize(float Velocity_Actual_Val);

#endif /* __PID_H */

/*****************************************************END OF FILE*********************************************************/	
