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

/* ���� -----------------------------------------------------------------------------------------------------------------*/
Param_InitTypeDef Param;
Flag_InitTypeDef  Flag;

/**
 * ������:LocationRing_Out
 * ����:λ�û����������
 * ����:��
 * ���:�ٶȻ�������ֵ
 */
float LocationRing_Out(void)
{
 float ExpectVelocity=0.0;
	
	PID.Location_Actual_Val=Param.Sigma_Motor1Pluse;//���ۼ����������ݸ�λ�û���ʵ��ֵ
	
	ExpectVelocity=LocationRing_PID_Realize(PID.Location_Actual_Val);//�õ��������ٶ�
	
	ExpectVelocity=(ExpectVelocity>MOTOR_SPEED_MAX)?MOTOR_SPEED_MAX:(ExpectVelocity<-MOTOR_SPEED_MAX)?(-MOTOR_SPEED_MAX):ExpectVelocity;//���е��ٶ��޷�
	
	return ExpectVelocity;
}

/**
 * ������:VelocityRing_Out
 * ����:�ٶȻ����������
 * ����:��
 * ���:PWM
 */
float VelocityRing_Out(void)
{
  float EcpectPWM=0.0;
	
	PID.Velocity_Actual_Val=(Param.UnitTime_Motor1Pluse/(RESOLUTION_TOTAL*REDUCTION_RATIO*PID_COMPUTATION_PERIOD))*1000*60;//����ȡ���ĵ�λʱ���ڵ�������תΪ��λΪrpm
	
	EcpectPWM=VelocityRing_PID_Realize(PID.Velocity_Actual_Val);//�õ��������ٶ�
	
	return EcpectPWM	;
}	

/**
 * ������:LocationRing_VelocityRing_Control
 * ����:����pid�Ŀ���
 * ����:��
 * ���:��
 */
void LocationRing_VelocityRing_Control(void)
{
  PID.Velocity_Target_Val=LocationRing_Out();
	
	PID.Velocity_Out=VelocityRing_Out(); 
}

/**
 * ������:Car_Tracking
 * ����:ֱ��Ѳ��
 * ����:��
 * ���:��
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
	
	
	//1.��Ŀ����븳ֵ��Ŀ�������ֵ
  Param.Distance_TargetThreshold=TargetDistance;
	
	//2.��Ŀ�����ת��Ϊ������ ����/�ܳ��õ���Ҫת��Ȧ����һȦ��������������õ���������������
	PID.Location_Target_Val=((TargetDistance/(2*3.14*WHEEL_R))*(RESOLUTION_TOTAL*REDUCTION_RATIO));
	
	//3.ʹ�ܵ��
	set_motor_enable();
}

/**
 * ������:Car_Spin
 * ����:ת��
 * ����:Direction=(LEFT_90/RIGHT_90/SPIN_180)
 * ���:��
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
 * ������:TIM3_IRQHandler
 * ����:��ʱ3�жϷ�����-10ms��ʱ��׼
 * ����:��
 * ���:��
 */
void TIM3_IRQHandler(void)
{
	uint8_t stop_time_cnt,spin_time_cnt;
	long    average_pluse;
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
	  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
		//1.��ȡ��λʱ����������
		Param.UnitTime_Motor1Pluse = -Read_Pluse(2);
		Param.UnitTime_Motor2Pluse = Read_Pluse(4);
		
		//2.�����ۼ�������
		Param.Sigma_Motor1Pluse+=Param.UnitTime_Motor1Pluse;
		Param.Sigma_Motor2Pluse+=Param.UnitTime_Motor2Pluse;
		
		//3.����С����ǰ����ʻ����=(�������ۼ�����/((������һȦ������������)*(�����ܳ�)))
		Param.Distance_Motor1Curret=Param.Sigma_Motor1Pluse/((RESOLUTION_TOTAL*REDUCTION_RATIO)*(2*3.14*WHEEL_R));
		
		//4.Ѳ�߻�����ȡopenMVѲ�߶�Ӧ����������Ķ�Ӧ���ֵLine_TempOut
		/*
		Ϊ�˱�����������⣬��Ԥ�����������Ķ�Ӧ����
		ֱ��-Line_TempOut=0;
		��ת-Line_TempOut=1800;
		��ת-Line_TempOut=-1800;
		*/
		
		//5.�ж��Ƿ���Ѳ�߹���
		if(Flag.Start_Line==1)
		{
		  //�ж��Ƿ���Ŀ��������С��ֵ�����Ｔ��ʼͣ��
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
			//�жϵ���Ƿ�����
			if(Flag.Is_EnMOTOR==1)
			{
			  LocationRing_VelocityRing_Control();
				//�����δ��ֱ�߻��ߴ򻬵�������µ������ۼ�����������ȵ����
				if(Param.Line_TempOut==0)
				{
					average_pluse=(Param.Sigma_Motor1Pluse+Param.Sigma_Motor2Pluse)/2;
					Param.Sigma_Motor1Pluse=Param.Sigma_Motor2Pluse=average_pluse;				 
				}
			}
			//Ѳ�߲���
			Param.Motor1_PWM=PID.Velocity_Out-Param.Line_TempOut;
			Param.Motor2_PWM=PID.Velocity_Out+Param.Line_TempOut;
			
			(Param.Motor1_PWM>0)?Motor_Left_DIR(FORWARD):Motor_Left_DIR(BACK);
			(Param.Motor2_PWM>0)?Motor_Right_DIR(FORWARD):Motor_Right_DIR(BACK);
			
			Load_Motor_PWM(Param.Motor1_PWM,Param.Motor2_PWM);
		}
		//6.�ж��Ƿ���ת�书��
		if(Flag.Start_Spin==1)
		{
		  //�ж��Ƿ��������
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
