#ifndef  _EXTI_H
#define  _EXTI_H

#include "sys.h" 
#include "pid.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
//������غ궨��
//1.mpu6050�ж����ų�ʼ����

#define   mpuexti_GPIOx                    GPIOB                 //�����ж϶˿�
#define   RCC_APB2Periph_mpuextiGPIOx      (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)   //�ж϶˿�ʱ��
#define   mpuexti_GPIO_Pin_x               GPIO_Pin_5             //�����ж�����

//2.�ж������ú�
#define   mpuexti_GPIO_PortSourceGPIOx     GPIO_PortSourceGPIOB   //�ж�Դ�˿�
#define   mpuexti_GPIO_PinSourcex          GPIO_PinSource5        //�ж�Դ����
#define   mpuexti_Linex                    EXTI_Line5           //�ж���

void room1(void);
void room2(void);
void room3(void);
void room4(void);
void MPU6050_EXTI_Init(void);
#endif


