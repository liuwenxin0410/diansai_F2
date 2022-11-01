/**
  *************************************************************************************************************************
  * @file    motor.h
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   tb6612模块.h文件配置
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __MOTOR_H
#define	__MOTOR_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"

/* 定义 -----------------------------------------------------------------------------------------------------------------*/
#define M_left_IN1   PBout(12)
#define M_left_IN2	 PBout(13)
#define M_right_IN3  PBout(14)
#define M_right_IN4  PBout(15)

#define PWM_MAX  4500

typedef enum
{
  FORWARD,
	BACK,
	STOP
}MotorDIR_Choose;

/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void Motor_GPIO_Init(void);
void Motor_Left_DIR(MotorDIR_Choose Direction);
void Motor_Right_DIR(MotorDIR_Choose Direction);
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM);
void set_motor_enable(void);
void set_motor_disable(void);

#endif /* __MOTOR_H */

/*****************************************************END OF FILE*********************************************************/	
