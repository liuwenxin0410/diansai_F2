/**
  *************************************************************************************************************************
  * @file    motor.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   tb6612模块.c文件配置
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "motor.h"
#include "myconfig.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/


/**
 * 函数名:Motor_GPIO_Init
 * 描述:电机对应GPIO引脚初始化
 * 输入:无
 * 输出:无
 */
void Motor_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
}


/**
 * 函数名:Motor_Left_DIR
 * 描述:左轮电机控制函数
 * 输入:Direction=(FORWARD,BACK,STOP)
 * 输出:无
 */
void Motor_Left_DIR(MotorDIR_Choose Direction)
{
  if(FORWARD==Direction)
	{
		M_left_IN1=1;
		M_left_IN2=0;
	}
	else if(BACK==Direction)
	{
		M_left_IN1=0;
		M_left_IN2=1;	 
	}
	else if(STOP==Direction)
	{
		M_left_IN1=0;
		M_left_IN2=0;	 
	}  
}

/**
 * 函数名:Motor_Right_DIR
 * 描述:右轮电机控制函数
 * 输入:Direction=(FORWARD,BACK,STOP)
 * 输出:无
 */
void Motor_Right_DIR(MotorDIR_Choose Direction)
{
  if(FORWARD==Direction)
	{
		M_right_IN3=1;
		M_right_IN4=0;
	}
	else if(BACK==Direction)
	{
		M_right_IN3=0;
		M_right_IN4=1;	 
	}
	else if(STOP==Direction)
	{
		M_right_IN3=0;
		M_right_IN4=0;	 
	}  
}

/**
 * 函数名:Load_Motor_PWM
 * 描述:更新PWM,并将其写定时器
 * 输入:MOTOR1_PWM-左轮电机计算得出的PWM值，MOTOR2_PWM-右轮电机计算得出的PWM值
 * 输出:无
 */
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM)
{
  MOTOR1_PWM=(MOTOR1_PWM>0)?MOTOR1_PWM:(-MOTOR1_PWM);
	MOTOR2_PWM=(MOTOR2_PWM>0)?MOTOR2_PWM:(-MOTOR2_PWM);
	
  MOTOR1_PWM=(MOTOR1_PWM>PWM_MAX)?PWM_MAX:MOTOR1_PWM;
	MOTOR2_PWM=(MOTOR2_PWM>PWM_MAX)?PWM_MAX:MOTOR1_PWM;	
	
	TIM_SetCompare1(TIM1,MOTOR1_PWM);
	TIM_SetCompare4(TIM1,MOTOR2_PWM);
}


/**
 * 函数名:set_motor_enable
 * 描述:使能电机
 * 输入:无
 * 输出:无
 */
void set_motor_enable(void)
{
  Flag.Is_EnMOTOR=1;
	TIM_CCxCmd(TIM1,TIM_Channel_1, TIM_CCx_Enable);
	TIM_CCxCmd(TIM1,TIM_Channel_4, TIM_CCx_Enable);	
}

/**
 * 函数名:set_motor_disable
 * 描述:失能电机
 * 输入:无
 * 输出:无
 */
void set_motor_disable(void)
{
  Flag.Is_EnMOTOR=0;
	TIM_CCxCmd(TIM1,TIM_Channel_1, TIM_CCx_Disable);
	TIM_CCxCmd(TIM1,TIM_Channel_4, TIM_CCx_Disable);	
}



/*****************************************************END OF FILE*********************************************************/	
