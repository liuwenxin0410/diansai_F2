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

/* ���� -----------------------------------------------------------------------------------------------------------------*/

//������������ֱ��ʣ�����
#define RESOLUTION  13

//������Ƶ֮��ķֱ��� 
#define RESOLUTION_TOTAL  13*4

//���ٵ���ļ��ٱ�
#define REDUCTION_RATIO  30

//��̥�뾶
#define WHEEL_R    3.25

//����
#define CAR_LENGTH    25

//����90�ľ���
#define SPIN_90_DISTANCE    0.25*3.14*9

//���־���
#define TWO_WHEEL_DISTANCE     18

//��������ת��
#define MOTOR_SPEED_MAX  160  //��λ160rpm��1s���ܵ�������53cm

//PID�ļ�������
#define PID_COMPUTATION_PERIOD  10//��λ��ms

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


/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/
extern Param_InitTypeDef Param;
extern Flag_InitTypeDef  Flag;

float LocationRing_Out(void);
float VelocityRing_Out(void);
void LocationRing_VelocityRing_Control(void);
void Car_Tracking(uint16_t TargetDistance);
void Car_Spin(SpinDIR_Choose Direction);


#endif /* __MYCONFIG_H */

/*****************************************************END OF FILE*********************************************************/	
