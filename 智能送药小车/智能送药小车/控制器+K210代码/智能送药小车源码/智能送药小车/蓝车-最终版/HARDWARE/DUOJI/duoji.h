#ifndef __DUOJI_H
#define	__DUOJI_H


#include "stm32f10x.h"

//外设相关采用宏定义
//1.时钟初始化
#define   RCC_APB2Periph_pwmGPIOx           RCC_APB2Periph_GPIOC
#define   RCC_APB2Periph_pwmTIMx            RCC_APB2Periph_TIM8
//2.端口和引脚初始化，可查阅数据手册进行配置
#define   pwmGPIO_Pin_x1                    GPIO_Pin_6          //复用输出引脚,TIM8,通道1
#define   pwmGPIO_Pin_x2                    GPIO_Pin_7          //复用输出引脚,TIM8,通道2
#define   pwmGPIO_Pin_x3                    GPIO_Pin_8          //复用输出引脚,TIM8,通道3
#define   pwmGPIO_Pin_x4                    GPIO_Pin_9          //复用输出引脚,TIM8,通道4

#define   pwmGPIOx                          GPIOC                //复用端口
#define   pwmTIMx                           TIM8
//默认采用通道1和4，可去函数中修改

void PWM_Init_TIM8(void);
	
#endif 

