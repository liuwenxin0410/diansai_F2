#ifndef  _EXTI_H
#define  _EXTI_H

#include "sys.h" 
#include "pid.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
//外设相关宏定义
//1.mpu6050中断引脚初始化宏

#define   mpuexti_GPIOx                    GPIOB                 //配置中断端口
#define   RCC_APB2Periph_mpuextiGPIOx      (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)   //中断端口时钟
#define   mpuexti_GPIO_Pin_x               GPIO_Pin_5             //配置中断引脚

//2.中断线配置宏
#define   mpuexti_GPIO_PortSourceGPIOx     GPIO_PortSourceGPIOB   //中断源端口
#define   mpuexti_GPIO_PinSourcex          GPIO_PinSource5        //中断源引脚
#define   mpuexti_Linex                    EXTI_Line5           //中断线

void room1(void);
void room2(void);
void room3(void);
void room4(void);
void MPU6050_EXTI_Init(void);
#endif


