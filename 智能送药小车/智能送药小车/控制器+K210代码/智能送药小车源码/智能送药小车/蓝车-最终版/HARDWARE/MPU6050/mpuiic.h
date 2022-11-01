#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32F103开发板
//MPU6050 IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/18
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	   		   
//外设相关用宏定义

#define  _mpuD                         3            //SDA引脚号
#define  _mpuC                         4            //SCL引脚号
#define  GPIO_Pin_mpu_SDA              GPIO_Pin_3   //配置SDA引脚,与上面引脚号对应
#define  GPIO_Pin_mpu_SCL              GPIO_Pin_4   //配置SCL引脚与上面引脚号对应					 
					 
#define  _mpuGPIOA                     0            //配置GPIO端口,配置哪个就定义为1，其他为0
#define  _mpuGPIOB                     1 
#define  _mpuGPIOC                     0
#define  _mpuGPIOD                     0
#define  _mpuGPIOE                     0
#define  _mpuGPIOF                     0
#define  _mpuGPIOG                     0				 

#define  _mpusdasizeL                  1            //若SDA引脚号小于等于7，此处写1；_oledsdasizeH写0.   
#define  _mpusdasizeH                  0            //若SDA引脚号大于等于8，此处写1；_oledsdasizeL写0.

#if   _mpusdasizeL 
#define  _mpunumL                      4*_mpuD
#define  _mpunumH                      4*(_mpuD-8)
#define  _mpunum                       _mpunumL     //SDA引脚小于等于7配置为_olednumL，SDA引脚号大于等于8配置为_olednumH
#define  _mpuK                         0X0000000F 
#define  _mpuCRK                       CRL          //SDA引脚号<=8,配置为CRL;引脚号>=8,配置为CRH
#define  _mpuKL                        ~(_mpuK<<(4*_mpuD))
#define  _mpuKH                        ~(_mpuK<<(4*(_mpuD-8)))
#define  _mpuKK                        _mpuKL       //SDA引脚号<=8,配置为_oledKL ;引脚号>=8,配置为_oledKH 
#elif _mpusdasizeH
#define  _mpunumL                      4*_mpuD
#define  _mpunumH                      4*(_mpuD-8)
#define  _mpunum                       _mpunumH     //SDA引脚小于等于7配置为_olednumL，SDA引脚号大于等于8配置为_olednumH
#define  _mpuK                         0X0000000F 
#define  _mpuCRK                       CRH          //SDA引脚号<=8,配置为CRL;引脚号>=8,配置为CRH
#define  _mpuKL                        ~(_mpuK<<(4*_mpuD))
#define  _mpuKH                        ~(_mpuK<<(4*(_mpuD-8)))
#define  _mpuKK                        _mpuKH       //SDA引脚号<=8,配置为_oledKL ;引脚号>=8,配置为_oledKH
#endif
					 
#if _mpuGPIOA                                      //GPIOA
#define  GPIO_mpuPort                 GPIOA
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOA
//IO操作函数	 
#define MPU_IIC_SCL    PAout(_mpuC) //SCL           //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PAout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PAin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOB                                      //GPIOB		                               			 
#define  GPIO_mpuPort                 GPIOB
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOB
//IO操作函数	 
#define MPU_IIC_SCL    PBout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PBout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PBin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}						 
					 
#elif _mpuGPIOC                                      //GPIOC		                               			 
#define  GPIO_mpuPort                 GPIOC
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOC
//IO操作函数	 
#define MPU_IIC_SCL    PCout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PCout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PCin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOD                                      //GPIOD		                               			 
#define  GPIO_mpuPort                 GPIOD
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOD
//IO操作函数	 
#define MPU_IIC_SCL    PDout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PDout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PDin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOE                                      //GPIOE		                               			 
#define  GPIO_mpuPort                 GPIOE
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOE
//IO操作函数	 
#define MPU_IIC_SCL    PEout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PEout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PEin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOF                                      //GPIOF		                               			 
#define  GPIO_mpuPort                 GPIOF
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOF
//IO操作函数	 
#define MPU_IIC_SCL    PFout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PFout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PFin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}

#elif _mpuGPIOG                                      //GPIOG		                               			 
#define  GPIO_mpuPort                 GPIOG
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOG
//IO操作函数	 
#define MPU_IIC_SCL    PGout(_mpuC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define MPU_IIC_SDA    PGout(_mpuD) //SDA	          //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define MPU_READ_SDA   PGin(_mpuD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}

#endif

////IO方向设置
//#define MPU_SDA_IN()   {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
//#define MPU_SDA_OUT()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}

////IO操作函数	 
//#define MPU_IIC_SCL     PBout(4) //SCL
//#define MPU_IIC_SDA     PBout(3) //SDA	
//#define MPU_READ_SDA   	PBin(3) //SDA	

////#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
////#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

////#define IIC_SCL    PBout(8) //SCL
////#define IIC_SDA    PBout(9) //SDA	 
////#define READ_SDA   PBin(9)  //输入SDA 



//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















