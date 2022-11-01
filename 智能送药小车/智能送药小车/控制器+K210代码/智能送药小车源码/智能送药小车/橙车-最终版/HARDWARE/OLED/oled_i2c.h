 #ifndef __OLEDIIC_H
#define __OLEDIIC_H
#include "sys.h"

//��������ú궨��

#define  _oledD                         4           //SDA���ź�
#define  _oledC                         5           //SCL���ź�
#define  GPIO_Pin_oledSDA               GPIO_Pin_4  //����SDA����,���������źŶ�Ӧ
#define  GPIO_Pin_oledSCL               GPIO_Pin_5  //����SCL�������������źŶ�Ӧ

#define  _oledGPIOA                     0           //����GPIO�˿�,�����ĸ��Ͷ���Ϊ1������Ϊ0
#define  _oledGPIOB                     0 
#define  _oledGPIOC                     1
#define  _oledGPIOD                     0
#define  _oledGPIOE                     0
#define  _oledGPIOF                     0
#define  _oledGPIOG                     0

#define  _oledsdasizeL                  1           //��SDA���ź�С�ڵ���7���˴�д1��_oledsdasizeHд0.   
#define  _oledsdasizeH                  0           //��SDA���źŴ��ڵ���8���˴�д1��_oledsdasizeLд0.

/*      ���治��Ҫ����                ���治��Ҫ����             ���治��Ҫ����      ���治��Ҫ����                         */
/*      ���治��Ҫ����                ���治��Ҫ����             ���治��Ҫ����      ���治��Ҫ����                         */
/*      ���治��Ҫ����                ���治��Ҫ����             ���治��Ҫ����      ���治��Ҫ����                         */
#if   _oledsdasizeL 
#define  _olednumL                      4*_oledD
#define  _olednumH                      4*(_oledD-8)
#define  _olednum                       _olednumL   //SDA����С�ڵ���7����Ϊ_olednumL��SDA���źŴ��ڵ���8����Ϊ_olednumH
#define  _oledK                         0X0000000F 
#define  _oledCRK                       CRL         //SDA���ź�<=8,����ΪCRL;���ź�>=8,����ΪCRH
#define  _oledKL                        ~(_oledK<<(4*_oledD))
#define  _oledKH                        ~(_oledK<<(4*(_oledD-8)))
#define  _oledKK                        _oledKL        //SDA���ź�<=8,����Ϊ_oledKL ;���ź�>=8,����Ϊ_oledKH 
#elif _oledsdasizeH
#define  _olednumL                      4*_oledD
#define  _olednumH                      4*(_oledD-8)
#define  _olednum                       _olednumH   //SDA����С�ڵ���7����Ϊ_olednumL��SDA���źŴ��ڵ���8����Ϊ_olednumH
#define  _oledK                         0X0000000F 
#define  _oledCRK                       CRH         //SDA���ź�<=8,����ΪCRL;���ź�>=8,����ΪCRH
#define  _oledKL                        ~(_oledK<<(4*_oledD))
#define  _oledKH                        ~(_oledK<<(4*(_oledD-8)))
#define  _oledKK                        _oledKH        //SDA���ź�<=8,����Ϊ_oledKL ;���ź�>=8,����Ϊ_oledKH
#endif


#if _oledGPIOA                                      //GPIOA
#define  GPIO_oledPort                 GPIOA
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOA
//IO��������	 
#define IIC_SCL    PAout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PAout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PAin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOB                                                        //GPIOB
#define  GPIO_oledPort                 GPIOB
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOB
//IO��������	 
#define IIC_SCL    PBout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PBout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PBin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOC                                                        //GPIOC
#define  GPIO_oledPort                 GPIOC
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOC
//IO��������	 
#define IIC_SCL    PCout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PCout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PCin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOD                                                       //GPIOD
#define  GPIO_oledPort                 GPIOD
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOD
//IO��������	 
#define IIC_SCL    PDout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PDout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PDin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOE                                                        //GPIOE
#define  GPIO_oledPort                 GPIOE
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOE
//IO��������	 
#define IIC_SCL    PEout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PEout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PEin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}
 
#elif _oledGPIOF                                                        //GPIOF
#define  GPIO_oledPort                 GPIOF
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOF
//IO��������	 
#define IIC_SCL    PFout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PFout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PFin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOG                                                        //GPIOG
#define  GPIO_oledPort                 GPIOG
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOG
//IO��������	 
#define IIC_SCL    PGout(_oledC) //SCL             //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_C)��PCout(_C)��
#define IIC_SDA    PGout(_oledD) //SDA	           //����ֻ���޸�GPIO�ڣ����ĳ�PBout(_D))��PCout(_D))��
#define READ_SDA   PGin(_oledD)  //����SDA         //����ֻ���޸�GPIO�ڣ����ĳ�PBin(_D)��PCin(_D)��
//IO��������
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#endif

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	

void OLED_WR_Byte(u8 dat,u8 mode);
#endif

