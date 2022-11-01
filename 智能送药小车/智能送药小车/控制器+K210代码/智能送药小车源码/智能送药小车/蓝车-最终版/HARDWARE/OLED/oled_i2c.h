 #ifndef __OLEDIIC_H
#define __OLEDIIC_H
#include "sys.h"

//外设相关用宏定义

#define  _oledD                         4           //SDA引脚号
#define  _oledC                         5           //SCL引脚号
#define  GPIO_Pin_oledSDA               GPIO_Pin_4  //配置SDA引脚,与上面引脚号对应
#define  GPIO_Pin_oledSCL               GPIO_Pin_5  //配置SCL引脚与上面引脚号对应

#define  _oledGPIOA                     0           //配置GPIO端口,配置哪个就定义为1，其他为0
#define  _oledGPIOB                     0 
#define  _oledGPIOC                     1
#define  _oledGPIOD                     0
#define  _oledGPIOE                     0
#define  _oledGPIOF                     0
#define  _oledGPIOG                     0

#define  _oledsdasizeL                  1           //若SDA引脚号小于等于7，此处写1；_oledsdasizeH写0.   
#define  _oledsdasizeH                  0           //若SDA引脚号大于等于8，此处写1；_oledsdasizeL写0.

/*      下面不需要配置                下面不需要配置             下面不需要配置      下面不需要配置                         */
/*      下面不需要配置                下面不需要配置             下面不需要配置      下面不需要配置                         */
/*      下面不需要配置                下面不需要配置             下面不需要配置      下面不需要配置                         */
#if   _oledsdasizeL 
#define  _olednumL                      4*_oledD
#define  _olednumH                      4*(_oledD-8)
#define  _olednum                       _olednumL   //SDA引脚小于等于7配置为_olednumL，SDA引脚号大于等于8配置为_olednumH
#define  _oledK                         0X0000000F 
#define  _oledCRK                       CRL         //SDA引脚号<=8,配置为CRL;引脚号>=8,配置为CRH
#define  _oledKL                        ~(_oledK<<(4*_oledD))
#define  _oledKH                        ~(_oledK<<(4*(_oledD-8)))
#define  _oledKK                        _oledKL        //SDA引脚号<=8,配置为_oledKL ;引脚号>=8,配置为_oledKH 
#elif _oledsdasizeH
#define  _olednumL                      4*_oledD
#define  _olednumH                      4*(_oledD-8)
#define  _olednum                       _olednumH   //SDA引脚小于等于7配置为_olednumL，SDA引脚号大于等于8配置为_olednumH
#define  _oledK                         0X0000000F 
#define  _oledCRK                       CRH         //SDA引脚号<=8,配置为CRL;引脚号>=8,配置为CRH
#define  _oledKL                        ~(_oledK<<(4*_oledD))
#define  _oledKH                        ~(_oledK<<(4*(_oledD-8)))
#define  _oledKK                        _oledKH        //SDA引脚号<=8,配置为_oledKL ;引脚号>=8,配置为_oledKH
#endif


#if _oledGPIOA                                      //GPIOA
#define  GPIO_oledPort                 GPIOA
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOA
//IO操作函数	 
#define IIC_SCL    PAout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PAout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PAin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOB                                                        //GPIOB
#define  GPIO_oledPort                 GPIOB
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOB
//IO操作函数	 
#define IIC_SCL    PBout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PBout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PBin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOC                                                        //GPIOC
#define  GPIO_oledPort                 GPIOC
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOC
//IO操作函数	 
#define IIC_SCL    PCout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PCout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PCin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOD                                                       //GPIOD
#define  GPIO_oledPort                 GPIOD
#define  RCC_APB2_Periph_oledGPIO      RCC_APB2Periph_GPIOD
//IO操作函数	 
#define IIC_SCL    PDout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PDout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PDin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOE                                                        //GPIOE
#define  GPIO_oledPort                 GPIOE
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOE
//IO操作函数	 
#define IIC_SCL    PEout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PEout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PEin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}
 
#elif _oledGPIOF                                                        //GPIOF
#define  GPIO_oledPort                 GPIOF
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOF
//IO操作函数	 
#define IIC_SCL    PFout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PFout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PFin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#elif _oledGPIOG                                                        //GPIOG
#define  GPIO_oledPort                 GPIOG
#define  RCC_APB2_oledPeriph_GPIO      RCC_APB2Periph_GPIOG
//IO操作函数	 
#define IIC_SCL    PGout(_oledC) //SCL             //这里只需修改GPIO口，即改成PBout(_C)、PCout(_C)等
#define IIC_SDA    PGout(_oledD) //SDA	           //这里只需修改GPIO口，即改成PBout(_D))、PCout(_D))等
#define READ_SDA   PGin(_oledD)  //输入SDA         //这里只需修改GPIO口，即改成PBin(_D)、PCin(_D)等
//IO方向设置
#define SDA_IN()  {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)8<<_olednum;}
#define SDA_OUT() {GPIO_oledPort->_oledCRK&=_oledKK;GPIO_oledPort->_oledCRK|=(u32)3<<_olednum;}

#endif

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	

void OLED_WR_Byte(u8 dat,u8 mode);
#endif

