#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32F103������
//MPU6050 IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/18
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	   		   
//��������ú궨��

#define  _mpuD                         3            //SDA���ź�
#define  _mpuC                         4            //SCL���ź�
#define  GPIO_Pin_mpu_SDA              GPIO_Pin_3   //����SDA����,���������źŶ�Ӧ
#define  GPIO_Pin_mpu_SCL              GPIO_Pin_4   //����SCL�������������źŶ�Ӧ					 
					 
#define  _mpuGPIOA                     0            //����GPIO�˿�,�����ĸ��Ͷ���Ϊ1������Ϊ0
#define  _mpuGPIOB                     1 
#define  _mpuGPIOC                     0
#define  _mpuGPIOD                     0
#define  _mpuGPIOE                     0
#define  _mpuGPIOF                     0
#define  _mpuGPIOG                     0				 

#define  _mpusdasizeL                  1            //��SDA���ź�С�ڵ���7���˴�д1��_oledsdasizeHд0.   
#define  _mpusdasizeH                  0            //��SDA���źŴ��ڵ���8���˴�д1��_oledsdasizeLд0.

#if   _mpusdasizeL 
#define  _mpunumL                      4*_mpuD
#define  _mpunumH                      4*(_mpuD-8)
#define  _mpunum                       _mpunumL     //SDA����С�ڵ���7����Ϊ_olednumL��SDA���źŴ��ڵ���8����Ϊ_olednumH
#define  _mpuK                         0X0000000F 
#define  _mpuCRK                       CRL          //SDA���ź�<=8,����ΪCRL;���ź�>=8,����ΪCRH
#define  _mpuKL                        ~(_mpuK<<(4*_mpuD))
#define  _mpuKH                        ~(_mpuK<<(4*(_mpuD-8)))
#define  _mpuKK                        _mpuKL       //SDA���ź�<=8,����Ϊ_oledKL ;���ź�>=8,����Ϊ_oledKH 
#elif _mpusdasizeH
#define  _mpunumL                      4*_mpuD
#define  _mpunumH                      4*(_mpuD-8)
#define  _mpunum                       _mpunumH     //SDA����С�ڵ���7����Ϊ_olednumL��SDA���źŴ��ڵ���8����Ϊ_olednumH
#define  _mpuK                         0X0000000F 
#define  _mpuCRK                       CRH          //SDA���ź�<=8,����ΪCRL;���ź�>=8,����ΪCRH
#define  _mpuKL                        ~(_mpuK<<(4*_mpuD))
#define  _mpuKH                        ~(_mpuK<<(4*(_mpuD-8)))
#define  _mpuKK                        _mpuKH       //SDA���ź�<=8,����Ϊ_oledKL ;���ź�>=8,����Ϊ_oledKH
#endif
					 
#if _mpuGPIOA                                      //GPIOA
#define  GPIO_mpuPort                 GPIOA
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOA
//IO��������	 
#define MPU_IIC_SCL    PAout(_mpuC) //SCL           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PAout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PAin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOB                                      //GPIOB		                               			 
#define  GPIO_mpuPort                 GPIOB
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOB
//IO��������	 
#define MPU_IIC_SCL    PBout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PBout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PBin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}						 
					 
#elif _mpuGPIOC                                      //GPIOC		                               			 
#define  GPIO_mpuPort                 GPIOC
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOC
//IO��������	 
#define MPU_IIC_SCL    PCout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PCout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PCin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOD                                      //GPIOD		                               			 
#define  GPIO_mpuPort                 GPIOD
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOD
//IO��������	 
#define MPU_IIC_SCL    PDout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PDout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PDin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOE                                      //GPIOE		                               			 
#define  GPIO_mpuPort                 GPIOE
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOE
//IO��������	 
#define MPU_IIC_SCL    PEout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PEout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PEin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}					 
					 
#elif _mpuGPIOF                                      //GPIOF		                               			 
#define  GPIO_mpuPort                 GPIOF
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOF
//IO��������	 
#define MPU_IIC_SCL    PFout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PFout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PFin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}

#elif _mpuGPIOG                                      //GPIOG		                               			 
#define  GPIO_mpuPort                 GPIOG
#define  RCC_APB2_Periph_mpuGPIO      RCC_APB2Periph_GPIOG
//IO��������	 
#define MPU_IIC_SCL    PGout(_mpuC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define MPU_IIC_SDA    PGout(_mpuD) //SDA	          //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define MPU_READ_SDA   PGin(_mpuD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define MPU_SDA_IN()  {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)8<<_mpunum;}
#define MPU_SDA_OUT() {GPIO_mpuPort->_mpuCRK&=_mpuKK;GPIO_mpuPort->_mpuCRK|=(u32)3<<_mpunum;}

#endif

////IO��������
//#define MPU_SDA_IN()   {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
//#define MPU_SDA_OUT()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}

////IO��������	 
//#define MPU_IIC_SCL     PBout(4) //SCL
//#define MPU_IIC_SDA     PBout(3) //SDA	
//#define MPU_READ_SDA   	PBin(3) //SDA	

////#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
////#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

////#define IIC_SCL    PBout(8) //SCL
////#define IIC_SDA    PBout(9) //SDA	 
////#define READ_SDA   PBin(9)  //����SDA 



//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















