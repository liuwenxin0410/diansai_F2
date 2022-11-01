#include "usart.h"
uint8_t room1_flag=0,room2_flag=0;
uint8_t MV_xunji[5]={0,0,0,0,0};
uint8_t MV_num=0;
uint8_t K210_num[3]={0,0,0};
uint8_t shibie_flag1=0,shibie_flag2=0,shibie_flag3=0,shibie_flag4=0;
uint8_t shibie_flag5=0,shibie_flag6=0,shibie_flag7=0,shibie_flag8=0;
uint8_t shibie_flag11=0,shibie_flag22=0,shibie_flag33=0,shibie_flag44=0;
uint8_t shibie_flag55=0,shibie_flag66=0,shibie_flag77=0,shibie_flag88=0,shibie_flagnn=0;
/*循迹标志*/
extern uint8_t xunji_flag;
extern uint8_t left_turn_flag1,right_turn_flag1;
extern uint8_t stop_flag;
extern uint8_t still_flag;
extern uint8_t sekuai_flag;

/**********中端**********/
extern uint8_t zhongduan_count;
extern uint8_t zhongduan_num;
extern uint8_t shibie_ok=0;
extern uint8_t k210_num_ok;
extern uint8_t room3_flag;
extern int time_openmv;
extern uint8_t exp_num;
extern uint8_t jishi_flag;
/**********双车************/
uint8_t qidong_1=0;
uint8_t shuagche_turnflag=0;
uint8_t fasong_num=0;
u8 data1[10]={0XFE,0,0X90,0X91,0X02,0X00,1,0,0,0XFF};
/**************编码器********/
extern uint8_t zdlukou2_fanhui;
/*************大BUG**************/
//uint8_t num_zisuo=0;
/*************发挥1************/
uint8_t yd_trunflag=0;
int yuanduan_count=0,yuanduan_num=0;
uint8_t room4_flag=0;
/***********基础3**************/
uint8_t fahui3=0;
/*************改橙车*************/
uint8_t fahui2_flag=0;
extern	u8 data0[10];
uint8_t start_flag=0;

/*************识别次数*****************/
extern uint16_t num_count;
extern uint8_t X_exp;
extern uint8_t jinduan,yuanduan;
extern uint8_t start_flag1;
/* 串口1中断服务函数*/
void DEBUG_USART_IRQHandler(void)
{
	static uint8_t date1[5],i_k=0;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{	
		date1[i_k++]=USART_ReceiveData(DEBUG_USARTx);
		if(date1[0]!=0xfe) i_k=0; 
		if((i_k==5)&&(date1[4]!=0xff)) i_k=0;
		if(i_k==5)
		{
			num_count++;
			if(num_count>60000)
			{
				num_count=0;
			}
			K210_num[0]=date1[1];  //num
			K210_num[1]=date1[2];  //x
			K210_num[2]=date1[3];  //y
			if(K210_num[0]==1)//1
			{
				 if(shibie_ok==0)
				{
					shibie_flag1++;
					if(shibie_flag1==10)
					{
						start_flag1=1;
						shibie_ok=1;
						k210_num_ok=1;
						OLED_Clear();
//						while(KEY0==1)
//						{
//							OLED_zhengshu_2wei(30,0,k210_num_ok,2);
//						}
//						delay_ms(1000);
//						room1_start();
						USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, DISABLE);
					}
				}					
			}
			else if(K210_num[0]==2)//2
			{
				if(shibie_ok==0)
				{
					shibie_flag2++;
					if(shibie_flag2==10)
					{
						start_flag1=1;
						shibie_ok=1;
						k210_num_ok=2;
						OLED_Clear();
//						while(KEY0==1)
//						{
//							OLED_zhengshu_2wei(30,0,k210_num_ok,2);
//						}
//						delay_ms(1000);
//						room2_start();	
						USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, DISABLE);	
					}	
				}					
			}
			else if(K210_num[0]==3)//3
			{
				shibie_flag33++;
				if(k210_num_ok==3)
				{
					shibie_flagnn=shibie_flag33;
				}
				if(shibie_ok==0)
				{
					shibie_flag3++;
					if(shibie_flag3>=25)
					{
						  start_flag1=1;
						  shibie_ok=1;
							k210_num_ok=3;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			} 
			else if(K210_num[0]==4)//4
			{
				shibie_flag44++;
				if(k210_num_ok==4)
				{
					shibie_flagnn=shibie_flag44;
				}
				if(shibie_ok==0)
				{
					shibie_flag4++;
					if(shibie_flag4>=25)
					{
						  shibie_ok=1;
							k210_num_ok=4;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			} 
			else if(K210_num[0]==5)//5
			{
				shibie_flag55++;
				if(k210_num_ok==5)
				{
					shibie_flagnn=shibie_flag55;
				}
				if(shibie_ok==0)
				{
					shibie_flag5++;
					if(shibie_flag5>=25)
					{
						  shibie_ok=1;
							k210_num_ok=5;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			} 	
			else if(K210_num[0]==6)//6
			{
				shibie_flag66++;
				if(k210_num_ok==6)
				{
					shibie_flagnn=shibie_flag66;
				}
				if(shibie_ok==0)
				{
					shibie_flag6++;
					if(shibie_flag6>=25)
					{
						  shibie_ok=1;
							k210_num_ok=6;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			} 
			else if(K210_num[0]==7)//7
			{
				shibie_flag77++;
				if(k210_num_ok==7)
				{
					shibie_flagnn=shibie_flag77;
				}
				if(shibie_ok==0)
				{
					shibie_flag7++;
					if(shibie_flag7>=25)
					{
						  shibie_ok=1;
							k210_num_ok=7;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			}	
			else if(K210_num[0]==8)//8
			{
				shibie_flag88++;
				if(k210_num_ok==8)
				{
					shibie_flagnn=shibie_flag88;
				}
				if(shibie_ok==0)
				{
					shibie_flag8++;
					if(shibie_flag8>=25)
					{
						  shibie_ok=1;
							k210_num_ok=8;
						  X_exp=date1[2];
						  K210_num[0]=0;
						  if(date1[2]<60)
							{
								yd_trunflag=0;
							}
							else
							{
								yd_trunflag=1;
							}

					 }	
				}
				//K210_num[0]=0;
			}	
		}			
	}	 
}

	






/*串口3中断服务函数*/
void DEBUG_USART3_IRQHandler(void)
{
	static uint8_t date3[4],i_m=0;
  if(USART_GetITStatus(DEBUG_USART3x,USART_IT_RXNE)!=RESET)
   {		
		 date3[i_m++]=USART_ReceiveData(DEBUG_USART3x);
		 if(date3[0]!=0xfe) i_m=0; 
		 if((i_m==4)&&(date3[3]!=0xff)) i_m=0;
		 if(i_m==4)
		 {
				MV_xunji[0]=(date3[1]&0X10)>>4;
				MV_xunji[1]=(date3[1]&0X08)>>3;
				MV_xunji[2]=(date3[1]&0X04)>>2;
				MV_xunji[3]=(date3[1]&0X02)>>1;	
				MV_xunji[4]=(date3[1]&0X01)>>0;
				MV_num=date3[2];
				if(((MV_xunji[0]==1)&&(MV_xunji[3]==1))||((MV_xunji[0]==1)&&(MV_xunji[4]==1))
					||((MV_xunji[1]==1)&&(MV_xunji[3]==1))||((MV_xunji[1]==1)&&(MV_xunji[4]==1))||
				((MV_xunji[0]==1)&&(MV_xunji[4]==1))||((MV_xunji[0]==1)&&(MV_xunji[1]==1)||
				((MV_xunji[3]==1)&&(MV_xunji[4]==1))))
				{
					if(jishi_flag==0)
					{
						zhongduan_count++;
					}
					jishi_flag=1;
					if(time_openmv>=300)
					{
						time_openmv=0;
            zhongduan_count++;
					  K210_num[0]=0;
					}
				}
			  if(date3[2]>=4)
				{
					if(room1_flag==1)
					{	
            if(sekuai_flag==1)
						{						
              room1_usart();
							sekuai_flag=0;
						}
            if(sekuai_flag==2)
						{						
              room1_usart();
							sekuai_flag=0;
						}
					}
					else if(room2_flag==1)
					{					
						if(sekuai_flag==1)
						{						
							room2_usart();
							sekuai_flag=0;
						}
           if(sekuai_flag==2)
					 {						
              room2_usart();
							sekuai_flag=0;
						}
					}
					else if(room3_flag==1)
					{
						if(sekuai_flag==1)
						{						
							room3_usart();
							sekuai_flag=0;
						}
           if(sekuai_flag==2)
					 {						
              room3_usart();
							sekuai_flag=0;
						}						
					}			
				}
		 } 		 
   }	
}	

void room1_usart(void)
{
		if(still_flag!=1)
		{	
			Load(0,0);
			Red_led=0;
			while(KEY0==0);
			Red_led=1;						
//			Load(-2000,2000);
//			delay_ms(1000);
			Load(-2000,2000);
			delay_ms(1000);	
			delay_ms(570);
//			Load(0,0);
		}
		else
		{					
			Load(0,0);
			delay_ms(50);
			Load(1000,1000);
			delay_ms(500);
			Load(0,0);
			Greeen_led=0;
			while(1);
		}	
}
void room1_start(void)
{
		Load(1500,1500);
		xunji_flag=1;
		left_turn_flag1=1;
    room1_flag=1;	
}

void room2_usart(void)
{
		if(still_flag!=1)
		{	
			Load(0,0);
			Red_led=0;
			while(KEY0==0);;
			Red_led=1;						
//			Load(-2000,2000);
//			delay_ms(1000);
			Load(-2000,2000);
			delay_ms(1000);	
			delay_ms(570);
//			Load(0,0);
		}
		else
		{					
			Load(0,0);
			delay_ms(50);
			Load(1000,1000);
			delay_ms(500);
			Load(0,0);
			Greeen_led=0;
			while(1);
		}	
}

void room2_start(void)
{
		Load(1500,1500);
		xunji_flag=1;
		right_turn_flag1=1;	
    room2_flag=1;	
}

void room3_usart(void)
{
//		if(still_flag!=1)
//		{	
//			Load(0,0);
//			Red_led=0;
//			while(KEY0==0)
//			{
//				//data1[8]=5;
//				data1[7]=shuagche_turnflag;
//				Usart2_Send_function(10,data1);
//				delay_ms(5);			
//			}
//			Red_led=1;
////			data1[8]=5;
////			if(qidong_1==1)
////			{
//			  data1[8]=5;
//				for(fasong_num=0;fasong_num<200;fasong_num++)
//				{
//					Usart2_Send_function(10,data1);
//					delay_ms(5);
//				}	
////			}				
//			Load(-2000,2000);
//			delay_ms(1000);	
//			delay_ms(570);
//			zdlukou2_fanhui=1;
//		}
//		else
//		{					
//			Load(0,0);
//			delay_ms(50);
//			Load(1000,1000);
//			delay_ms(500);
//			Load(0,0);
//			Greeen_led=0;
//			while(1);
//		}	
}

void room3_start(void)
{
	  Load(1500,1500);
		xunji_flag=1;
    room3_flag=1;	
}

void room4_start(void)
{
		Load(1500,1500);
		xunji_flag=1;
    room4_flag=1;	
}
/*串口2中断服务函数*/
void DEBUG_USART2_IRQHandler(void)
{
  uint8_t ucTemp;
	static uint8_t date2[10]; 
  static	int  j=0,m=4,i=0;
  if(USART_GetITStatus(DEBUG_USART2x,USART_IT_RXNE)!=RESET)
  {		   
		date2[i++]=USART_ReceiveData(DEBUG_USART2x);	//接收数据
		if(date2[0]!=0xfe) i=0;             		  //判断第一个帧头
	  if((i==10)&&(date2[9]!=0xff)) i=0;    		//判断帧尾		
		if(i==10)                           			//代表一组数据传输完毕
		{
			 i=0;
			 fahui2_flag=date2[1];//蓝车改橙车
			 data0[1]=1;
			 Usart2_Send_function(10,data0);
			 qidong_1=date2[6];		
			 shuagche_turnflag=date2[7];
			 start_flag=date2[8];			
			 fahui3=date2[1];
					
		}		
  }	
}

void Usart2_Send_function(int length1,u8 *data)
{
	static int  usart_i; 
	for(usart_i=0;usart_i<length1;usart_i++)
	{
		Usart_SendByte(DEBUG_USART2x,data[usart_i]);
	}
}










static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
static void NVIC2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
static void NVIC3_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART3_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}


void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USART2x, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC2_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USART2x, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USART2x, ENABLE);	    
}

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART3_GPIO_APBxClkCmd(DEBUG_USART3_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART3_APBxClkCmd(DEBUG_USART3_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART3_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART3_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USART3x, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC3_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USART3x, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USART3x, ENABLE);	    
}

/*****************  发送一个字节 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** 发送8位的数组 ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///重定向c库函数printf到串口，重定向后可使用printf函数，相对于电脑而言
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
	//单片机发送数据到串口，串口连接到电脑，电脑可以显示
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函,相对于电脑而言
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
	//电脑发送数据到单片机，在中断服务函数中单片机再发给电脑显示
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE)==RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}












