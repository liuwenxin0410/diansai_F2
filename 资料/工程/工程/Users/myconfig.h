/**
  *************************************************************************************************************************
  * @file    myconfig.h
  * @author  AMKL
  * @version V1.0
  * @date    2022-09-22
  * @brief   STM32F103C8T6
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __MYCONFIG_H
#define	__MYCONFIG_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include 	"stm32f10x.h"
#include 	"systick.h"
#include	"nvic.h"
#include  "infrared.h"
#include  "encoder.h"
#include  "usart1.h"
#include  "usart2.h"
#include  "usart3.h"
#include  "motor.h"
#include  "tim1.h"
#include  "tim3.h"
#include  "pid.h"
#include 	"led.h"
#include 	"sys.h"

/* 定义 -----------------------------------------------------------------------------------------------------------------*/

//编码器的物理分辨率，线数
#define RESOLUTION  13

//经过倍频之后的分辨率 
#define RESOLUTION_TOTAL  13*4

//减速电机的减速比
#define REDUCTION_RATIO  30

//轮胎半径
#define WHEEL_R    3.25

//车长
#define CAR_LENGTH    25

//自旋90的距离
#define SPIN_90_DISTANCE    0.25*3.14*9

//俩轮距离
#define TWO_WHEEL_DISTANCE     18

//电机的最大转速
#define MOTOR_SPEED_MAX  160  //单位160rpm，1s能跑的最大距离53cm

//PID的计算周期
#define PID_COMPUTATION_PERIOD  10//单位是ms

typedef struct
{
  long    Sigma_Motor1Pluse;
	long    Sigma_Motor2Pluse;
	short   UnitTime_Motor1Pluse;
	short   UnitTime_Motor2Pluse;
	float   Distance_Motor1Curret;
	float   Distance_Motor2Curret;
	float   Distance_TargetThreshold;
	uint16_t Motor1_PWM;
	uint16_t Motor2_PWM;
	uint8_t  Send_Step;
	uint8_t  Back_Step;
	uint16_t Line_TempOut;
}Param_InitTypeDef;

typedef struct
{
	uint8_t Is_EnMOTOR;
	uint8_t Start_Line;
	uint8_t Stop_Car;
	uint8_t Run_Step;
	uint8_t Start_Spin;
	uint8_t Success_Spin;
}Flag_InitTypeDef;

typedef enum
{
  LEFT_90,
	RIGHT_90,
	SPIN_180
}SpinDIR_Choose;


/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
extern Param_InitTypeDef Param;
extern Flag_InitTypeDef  Flag;

float LocationRing_Out(void);
float VelocityRing_Out(void);
void LocationRing_VelocityRing_Control(void);
void Car_Tracking(uint16_t TargetDistance);
void Car_Spin(SpinDIR_Choose Direction);


#endif /* __MYCONFIG_H */

/*****************************************************END OF FILE*********************************************************/	
