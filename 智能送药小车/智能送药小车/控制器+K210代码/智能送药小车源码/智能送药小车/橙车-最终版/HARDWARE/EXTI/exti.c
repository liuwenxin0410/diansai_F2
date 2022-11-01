#include "exti.h"
extern uint8_t room1_flag,room2_flag;
extern float pitch,roll,yaw;
extern float left_speed,right_speed,speed;
extern uint8_t MV_xunji[5];
extern uint8_t MV_num;
extern uint8_t K210_num[3];
int basic_pwm=1500,trun_pwm=300,trun_pwm2=300,trun_pwm3=1500;
int turn_time1=300;
int speed_pid=0,turn_pid=0;//PID
int exp_speed=30;//期望速度
float exp_yaw=0;//期望角度
int flag_yaw=0;//
uint8_t left_turn_flag=0,xunji_flag=0;//转向标志,循迹标志
uint8_t left_turn_flag1=0,right_turn_flag1=0,still_flag=0;
uint8_t stop_flag=0;
uint8_t sekuai_flag=0;

int time_openmv=0;
/********中端*********/
uint8_t zhongduan_count=0; 
uint8_t zhongduan_num=0;
uint8_t zhongduan_left=0,zhongduan_right=0,zhongduan_left2=0,zhongduan_right2=0;
uint8_t zhongduan_find=0;
uint8_t room3_flag=0;
extern uint8_t k210_num_ok;
uint8_t exp_num=0;
uint8_t zhongdaun_turn=0;
uint8_t shibie_o=0;
uint8_t jishi_flag=0;
/********远端*********/
uint8_t lukou3_turnflag=0,lukou4_turnflag=0;
uint8_t lukou3_left=0,lukou3_right=0,lukou4_left,lukou4_right=0;
uint8_t lukou3_end=0,lukou4_end=0;
/*********双车********/
extern uint8_t shuagche_turnflag;
extern uint8_t qidong_1;

/***********编码器路口2***********/
uint32_t left_encoder=0,right_encoder=0;
uint32_t zd_encoder=0,zd_encoder2=0,zd_encoder3; 
uint8_t zdlukou2_fanhui=0;
uint8_t lukou2_start=0;
uint32_t lukou2_startencoder=0;
extern u8 data1[10];
int fasong_num2=0;
uint8_t zdfanhuix=0;
uint8_t lukou_count=0;

/***********发挥2*************/
extern uint8_t yd_trunflag;
extern uint8_t room4_flag;
uint8_t lukou3_encoderflag=0;
int lukou3_encoder=0;
uint8_t lukou4_encoderflag=0,lukou4zisuo=0;
int lukou4_encoder=0;
uint8_t lukou5_encoderflag=0,lukou5zisuo=0;
int lukou5_encoder=0;
uint8_t lukou_1flag=0,lukou_2flag=0;
uint8_t xxfanhui=0,xxfanhui_trun=0;
int xxfanhui_encoder=0;
uint8_t xxfanhui1=0;

uint8_t xxfanhui2=0;//积分
int xxencoder2=0;
uint8_t xxzisuo=0;
uint8_t xx_zong=0;
int xx_zongencoder=0;

/*******************基础3***********************/
extern uint8_t fahui3;
/*********************近端病房重写***********************/
/*************1号病房**************/
uint8_t jinduan1_flag=0,jinduan1zisuo=0;
int jinduan1_encoder=0;
uint8_t jinduan1_flag2=0,jinduan1zisuo2=0;
int jinduan1_encoder2=0;
uint8_t jinduan1_flag3=0,jinduan1zisuo3=0;
int jinduan1_encoder3=0;
uint8_t jinduan1_flag4=0,jinduan1zisuo4=0;
int jinduan1_encoder4=0;
/*****************病房1路程宏**********************/
int jd1jifen1=10500,jd1jifen1fanhui=8000;
int jd1jifen2=5000,jd1jifen2fanhui=5000;
/*************2号病房**************/
uint8_t jinduan2_flag=0,jinduan2zisuo=0;
int jinduan2_encoder=0;
uint8_t jinduan2_flag2=0,jinduan2zisuo2=0;
int jinduan2_encoder2=0;
uint8_t jinduan2_flag3=0,jinduan2zisuo3=0;
int jinduan2_encoder3=0;
uint8_t jinduan2_flag4=0,jinduan2zisuo4=0;
int jinduan2_encoder4=0;
/*****************病房2路程宏**********************/
int jd2jifen1=10500,jd2jifen1fanhui=8000;
int jd2jifen2=5000,jd2jifen2fanhui=5000;

/*****************远端路程宏**********************/
int ydjifen1=34800,ydjifen1fanhui=32500;//从启动区到第三个路口
int ydjifen2=12000,ydjifen2fanhui=12000;//从第三个路口到第四个路口
int ydjifen3=5300,ydjifen3fanhui=4800;//从第四个路口到药房

/*****************中端端路程宏**********************/
int zdjifen1=22900,zdjifen1fanhui=20500;//从启动区到第二个路口
int zdjifen2=5000,zdjifen2fanhui=5000;//从第二个路口到药房

/*****************发挥1中端宏**********************/
int lukou2_hengxian=9950;//10100
int lukou2_banxian=5000;



/**********************改橙车**************************/
uint8_t cclukou2_trunflag=0,cclukou2_zisuo=0;
int cc_encoder=0;
extern uint8_t start_flag;
uint8_t exp_posflag=0,exp_posflagzisuo=0;
int exp_pos_encoder=0;
extern uint8_t fahui2_flag;
void EXTI9_5_IRQHandler(void)
{ 
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//一级判定
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			left_speed=-Read_Speed(2);
			right_speed=Read_Speed(3);
			speed=(left_speed+right_speed)/2;
			left_encoder=left_encoder+left_speed;
			right_encoder=right_encoder+right_speed;
//			speed_pid=Y_SPEED_PWM(exp_speed,speed,500,0,5);
			if(jishi_flag==1)
			{
			  time_openmv++;				
			}

			speed_pid=3500;
			//turn_pid=Y_TURN_PID(exp_yaw,yaw,-400,0,0);
			//Load(turn_pid,-turn_pid);
			if(room1_flag==1)
			{
        room1();
			}
			else if(room2_flag==1)
			{
        room2();
			}
			if(room3_flag==1)
			{
        room3();
			}
			if(room4_flag==1)
			{
        room4();
			}
		 }			
		EXTI_ClearITPendingBit(EXTI_Line5);//清除中断标志位	
	}
	
}

void room1(void)
{
			if(xunji_flag==1)	//循迹标志	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//左偏右转
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//左偏右转
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//右偏左转
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//右偏左转
				}
				if(jinduan1_flag==0)//开始积分
				{
					jinduan1_encoder=jinduan1_encoder+(left_speed+right_speed)/2;	
				}
				if(jinduan1_encoder>=jd1jifen1)//到达第一个路口
				{
					jinduan1_flag=1;//关闭积分
					if(jinduan1zisuo==0)//自锁
					{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);//左转
							delay_ms(800);
						  jinduan1zisuo=1;
							jinduan1_flag2=1;
					}
				}
				if(jinduan1_flag2==1)//到达病房积分
				{
					jinduan1_encoder2=jinduan1_encoder2+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder2>=jd1jifen2)//是否到达药房
				{
					jinduan1_flag2=0;
					if(jinduan1zisuo2==0)//自锁
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)//等待卸载药品
						{	
							
						}
						Red_led=1;
						delay_ms(500);
						Load(-2000,2000);//返回
						delay_ms(1000);	
						delay_ms(400);
						jinduan1zisuo2=1;
						jinduan1_flag3=1;//开始返回积分
					}					
				}
				if(jinduan1_flag3==1)//开始记录到路口1的积分
				{
					jinduan1_encoder3=jinduan1_encoder3+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder3>=jd1jifen2fanhui)//从病房到路口的积分
				{
					jinduan1_flag3=0;//关闭积分
					if(jinduan1zisuo3==0)//自锁
					{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);//右转
							delay_ms(500);
						  jinduan1zisuo3=1;
							jinduan1_flag4=1;//开始返回						
					}				
				}
				if(jinduan1_flag4==1)//开始返回积分
				{
					jinduan1_encoder4=jinduan1_encoder4+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder4>=jd1jifen1fanhui)//总返回
				{
					jinduan1_flag4=0;
					if(jinduan1zisuo4==0)
					{
						Load(0,0);
						Greeen_led=0;
						while(1);
						jinduan1zisuo4=1;
					}
					
				}

		  }	
}

void room2(void)
{
			if(xunji_flag==1)	//循迹标志	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//左偏右转
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//左偏右转
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//右偏左转
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//右偏左转
				}
				if(jinduan2_flag==0)//开始积分
				{
					jinduan2_encoder=jinduan2_encoder+(left_speed+right_speed)/2;	
				}
				if(jinduan2_encoder>=jd2jifen1)//到达第一个路口
				{
					jinduan2_flag=1;//关闭积分
					if(jinduan2zisuo==0)//自锁
					{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);//右转
							delay_ms(500);
						  jinduan2zisuo=1;
							jinduan2_flag2=1;
					}
				}
				if(jinduan2_flag2==1)//到达病房积分
				{
					jinduan2_encoder2=jinduan2_encoder2+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder2>=jd2jifen2)//是否到达药房
				{
					jinduan2_flag2=0;
					if(jinduan2zisuo2==0)//自锁
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)//等待卸载药品
						{	
							
						}
						Red_led=1;
						delay_ms(500);
						Load(-2000,2000);//返回
						delay_ms(1000);	
						delay_ms(400);
						jinduan2zisuo2=1;
						jinduan2_flag3=1;//开始返回积分
					}					
				}
				if(jinduan2_flag3==1)//开始记录到路口1的积分
				{
					jinduan2_encoder3=jinduan2_encoder3+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder3>=jd2jifen2fanhui)//从病房到路口的积分
				{
					jinduan2_flag3=0;//关闭积分
					if(jinduan2zisuo3==0)//自锁
					{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);//转转
							delay_ms(800);
						  jinduan2zisuo3=1;
							jinduan2_flag4=1;//开始返回						
					}				
				}
				if(jinduan2_flag4==1)//开始返回积分
				{
					jinduan2_encoder4=jinduan2_encoder4+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder4>=jd2jifen1fanhui)//总返回
				{
					jinduan2_flag4=0;
					if(jinduan2zisuo4==0)
					{
						Load(0,0);
						Greeen_led=0;
						while(1);
						jinduan2zisuo4=1;
					}
					
				}

		  }	
}


void room3(void)
{
			if(xunji_flag==1)	//循迹标志	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//左偏右转
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//左偏右转
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//右偏左转
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//右偏左转
				}
				if(zd_encoder<18000)
				{
					K210_num[0]=0;
				}
				if((K210_num[0]==k210_num_ok)&&(zd_encoder>18000))//第二个路口是否识别到目标数字
				{
					if(shibie_o==0)
					{
            exp_num=k210_num_ok;
						shibie_o=1;
					}
				}
				if(lukou_count==0)
				{
					zd_encoder=zd_encoder+(left_speed+right_speed)/2;					
				}
				if(zd_encoder>=zdjifen1)//到达第二个路口**23380********/
				{
					lukou_count=1;//不计数
					if(zhongdaun_turn==0)//自锁
					{
						if(qidong_1!=1)
						{
								if(exp_num==k210_num_ok)//识别到目标数字，右转
								{	
									Load(0,0);
									delay_ms(200);
									Load(2000,-2000);
									delay_ms(800);//900变800
									zhongduan_right=0;
									zhongduan_right2=1;						
								}
								else//没有识别到，左转
								{
									Load(0,0);
									delay_ms(200);
									Load(-2000,2000);
									delay_ms(800);
									zhongduan_left=0;
									zhongduan_left2=1;							
								}
								lukou2_start=1;//开始记录到停止区的路程
								zhongdaun_turn=1;//准备往停止区
						}
						else//双车
						{
							if(shuagche_turnflag==2)//右转
							{
									Load(0,0);
									delay_ms(200);
									Load(2000,-2000);
									delay_ms(800);//900变800							
							}
							else if(shuagche_turnflag==3)//左转
							{
									Load(0,0);
									delay_ms(200);
									Load(-2000,2000);
									delay_ms(800);								
							}
							cclukou2_trunflag=1;//发挥1双车
							zhongdaun_turn=1;//准备往停止区
						}						
					}
				}
				if(lukou2_start==1)//路口2开始记录路程****5800******/
				{
					lukou2_startencoder=lukou2_startencoder+(left_speed+right_speed)/2;
					if(lukou2_startencoder>=zdjifen2)//停止
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)
						{	
							
						}
						Red_led=1;
						delay_ms(200);
						Load(-2000,2000);//返回
						delay_ms(1000);	
						delay_ms(400);
						lukou2_start=0;//自锁
						zdlukou2_fanhui=1;//准备记录返回路口2的数值
					}
				}
				if(zdlukou2_fanhui==1)//路口2返回转弯*****5500*****/
				{
					zd_encoder2=zd_encoder2+(left_speed+right_speed)/2;  //开始记录
					if(zd_encoder2>=zdjifen2fanhui)
					{
						if(zhongduan_left2==1)//返回时右转
						{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);
							zhongduan_left2=0;//自锁					
						}	
						else//返回时左转
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);
							zhongduan_right2=0;//自锁          
						}	
						zdfanhuix=1;
						zdlukou2_fanhui=0;//自锁
					}
				}
				if(zdfanhuix==1)//总返回**********/
				{
					zd_encoder3=zd_encoder3+(left_speed+right_speed)/2;
					if(zd_encoder3>=zdjifen1fanhui)
					{	
						Load(0,0);
						Greeen_led=0;
						zdfanhuix=0;
						while(1);
					}						
				}

				if(cclukou2_trunflag==1)//发挥1
				{
					cc_encoder=cc_encoder+(left_speed+right_speed)/2;
				}
				if(cc_encoder>=lukou2_banxian)//发挥1 路口2到停车点
				{
					cclukou2_trunflag=0;
					if(cclukou2_zisuo==0)
					{
						Load(0,0);
						Yellow_led=0;
						while(start_flag!=5);//开始去目标药房
						Yellow_led=1;
						Load(-2000,2000);
						delay_ms(1000);
						Load(0,0);
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
						delay_ms(1000);
						Load(-1500,1500);
						cclukou2_zisuo=1;
						exp_posflag=1;					
					}
					
				}
				if(exp_posflag==1)
				{
					exp_pos_encoder=exp_pos_encoder+(left_speed+right_speed)/2;
				}
				if(exp_pos_encoder>=lukou2_hengxian)//发挥1，中端两病房距离
				{
					exp_posflag=0;
					if(exp_posflagzisuo==0)
					{
						Load(0,0);
						Red_led=0;
						while(1);
					}
					
				}

		  }	
}
void room4(void)
{
			if(xunji_flag==1)	//循迹标志	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//左偏右转
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//左偏右转
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//右偏左转
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//右偏左转
				}
        if(lukou4_encoder<2500)
        {
					K210_num[0]=0;
				}
				if((K210_num[0]==k210_num_ok)&&(lukou4_encoder>3000))//第四个路口是否识别到目标数字
				{
					if(shibie_o==0)
					{
            exp_num=k210_num_ok;
						shibie_o=1;
					}
				}
				
				if(lukou3_encoderflag==0)
				{
					lukou3_encoder=lukou3_encoder+(left_speed+right_speed)/2;	
				}
				if(lukou3_encoder>=ydjifen1)//到达第三个路口****35900******/**************/
				{
					K210_num[0]=0;
					lukou3_encoderflag=1;//不计数
					if(zhongdaun_turn==0)//自锁
					{
						if(yd_trunflag==1)//目标数字在右边，右转
						{	
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900变800							
						}
						else//没有识别到，左转
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);						
						}
						lukou4_encoderflag=1;//开始记录到停止区的路程
						zhongdaun_turn=1;//准备往停止区
				  }
				}
				if(lukou4_encoderflag==1)//第三个路口到第四个路口计数
				{
					lukou4_encoder=lukou4_encoder+(left_speed+right_speed)/2;
				}
				if(lukou4_encoder>=ydjifen2)/**********13050横线段***********************/
				{
					lukou4_encoderflag=0;
					if(lukou4zisuo==0)
					{
						if(exp_num==k210_num_ok)//识别到目标数字，右转
						{	
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900变800	
              xxfanhui_trun=1;							
						}
						else//没有识别到，左转
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);	
              xxfanhui_trun=0;							
						}
						lukou5_encoderflag=1;
						lukou4zisuo=1;					
					}						
				}
				if(lukou5_encoderflag==1)/**********4-5路口积分**********/
				{
					lukou5_encoder=lukou5_encoder+(left_speed+right_speed)/2;
				}
				if(lukou5_encoder>=ydjifen3)/********5800***********///到达
				{
					if(lukou5zisuo==0)//自锁
					{
						if(fahui2_flag!=1)
						{
							lukou5_encoderflag=0;
							Load(0,0);
							Red_led=0;
							while(KEY0==0)
							{	
							
							}
							delay_ms(200);
							Red_led=1;
							Load(-2000,2000);//返回
							delay_ms(1000);	
							delay_ms(200);
							lukou5zisuo=1;
							xxfanhui=1;
						}
						else//发挥2
						{
							Load(0,0);
							Red_led=0;
							while(1);						
						}
					}
				}
				if(xxfanhui==1)//第一次返回
				{
					xxfanhui_encoder=xxfanhui_encoder+(left_speed+right_speed)/2;
				}
				if(xxfanhui_encoder>=ydjifen3fanhui)//返程1
				{
					xxfanhui=0;
					if(xxfanhui1==0)
					{
						if(xxfanhui_trun==0)//回来右转
						{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900变800
						}
						else
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);
						}
						xxfanhui1=1;
						xxfanhui2=1;
					}
				}
				if(xxfanhui2==1)//返程2积分
				{
					xxencoder2=xxencoder2+(left_speed+right_speed)/2;
				}
				if(xxencoder2>=ydjifen2fanhui)//横线返回积分
				{
					xxfanhui2=0;
					if(xxzisuo==0)
					{
						if(yd_trunflag==1)//回来左转
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);							
						}
						else
						{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900变800							
						}
						xx_zong=1;
						xxzisuo=1;
					}
					
				}
        if(xx_zong==1)//总返程积分
				{
					xx_zongencoder=xx_zongencoder+(left_speed+right_speed)/2;
				}
				if(xx_zongencoder>=ydjifen1fanhui)//总返程1-35900
				{
						xx_zong=0;
						Load(0,0);
						Greeen_led=0;
						while(1);				
				}

		  }	
}




























void MPU6050_EXTI_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_mpuextiGPIOx,ENABLE);//开启时钟
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;/**【1】**///GPIO_Mode_AF_PP
	GPIO_InitStruct.GPIO_Pin=mpuexti_GPIO_Pin_x;//PB5配置为上拉输入
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(mpuexti_GPIOx,&GPIO_InitStruct);	
	
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置中断源：按键1 */
  NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;//需要更改
  /* 配置抢占优先级 */
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
  /* 配置子优先级 */
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
  /* 使能中断通道 */
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

	
	GPIO_EXTILineConfig(mpuexti_GPIO_PortSourceGPIOx,mpuexti_GPIO_PinSourcex);//
	
	EXTI_InitStruct.EXTI_Line=mpuexti_Linex;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
}




