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
int exp_speed=30;//�����ٶ�
float exp_yaw=0;//�����Ƕ�
int flag_yaw=0;//
uint8_t left_turn_flag=0,xunji_flag=0;//ת���־,ѭ����־
uint8_t left_turn_flag1=0,right_turn_flag1=0,still_flag=0;
uint8_t stop_flag=0;
uint8_t sekuai_flag=0;

int time_openmv=0;
/********�ж�*********/
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
/********Զ��*********/
uint8_t lukou3_turnflag=0,lukou4_turnflag=0;
uint8_t lukou3_left=0,lukou3_right=0,lukou4_left,lukou4_right=0;
uint8_t lukou3_end=0,lukou4_end=0;
/*********˫��********/
extern uint8_t shuagche_turnflag;
extern uint8_t qidong_1;

/***********������·��2***********/
uint32_t left_encoder=0,right_encoder=0;
uint32_t zd_encoder=0,zd_encoder2=0,zd_encoder3; 
uint8_t zdlukou2_fanhui=0;
uint8_t lukou2_start=0;
uint32_t lukou2_startencoder=0;
extern u8 data1[10];
int fasong_num2=0;
uint8_t zdfanhuix=0;
uint8_t lukou_count=0;

/***********����2*************/
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

uint8_t xxfanhui2=0;//����
int xxencoder2=0;
uint8_t xxzisuo=0;
uint8_t xx_zong=0;
int xx_zongencoder=0;

/*******************����3***********************/
extern uint8_t fahui3;
/*********************���˲�����д***********************/
/*************1�Ų���**************/
uint8_t jinduan1_flag=0,jinduan1zisuo=0;
int jinduan1_encoder=0;
uint8_t jinduan1_flag2=0,jinduan1zisuo2=0;
int jinduan1_encoder2=0;
uint8_t jinduan1_flag3=0,jinduan1zisuo3=0;
int jinduan1_encoder3=0;
uint8_t jinduan1_flag4=0,jinduan1zisuo4=0;
int jinduan1_encoder4=0;
/*****************����1·�̺�**********************/
int jd1jifen1=10500,jd1jifen1fanhui=8000;
int jd1jifen2=5000,jd1jifen2fanhui=5000;
/*************2�Ų���**************/
uint8_t jinduan2_flag=0,jinduan2zisuo=0;
int jinduan2_encoder=0;
uint8_t jinduan2_flag2=0,jinduan2zisuo2=0;
int jinduan2_encoder2=0;
uint8_t jinduan2_flag3=0,jinduan2zisuo3=0;
int jinduan2_encoder3=0;
uint8_t jinduan2_flag4=0,jinduan2zisuo4=0;
int jinduan2_encoder4=0;
/*****************����2·�̺�**********************/
int jd2jifen1=10500,jd2jifen1fanhui=8000;
int jd2jifen2=5000,jd2jifen2fanhui=5000;

/*****************Զ��·�̺�**********************/
int ydjifen1=34800,ydjifen1fanhui=32500;//����������������·��
int ydjifen2=12000,ydjifen2fanhui=12000;//�ӵ�����·�ڵ����ĸ�·��
int ydjifen3=5300,ydjifen3fanhui=4800;//�ӵ��ĸ�·�ڵ�ҩ��

/*****************�ж˶�·�̺�**********************/
int zdjifen1=22900,zdjifen1fanhui=20500;//�����������ڶ���·��
int zdjifen2=5000,zdjifen2fanhui=5000;//�ӵڶ���·�ڵ�ҩ��

/*****************����1�ж˺�**********************/
int lukou2_hengxian=9950;//10100
int lukou2_banxian=5000;



/**********************�ĳȳ�**************************/
uint8_t cclukou2_trunflag=0,cclukou2_zisuo=0;
int cc_encoder=0;
extern uint8_t start_flag;
uint8_t exp_posflag=0,exp_posflagzisuo=0;
int exp_pos_encoder=0;
extern uint8_t fahui2_flag;
void EXTI9_5_IRQHandler(void)
{ 
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//һ���ж�
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
		EXTI_ClearITPendingBit(EXTI_Line5);//����жϱ�־λ	
	}
	
}

void room1(void)
{
			if(xunji_flag==1)	//ѭ����־	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//��ƫ��ת
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//��ƫ��ת
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//��ƫ��ת
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//��ƫ��ת
				}
				if(jinduan1_flag==0)//��ʼ����
				{
					jinduan1_encoder=jinduan1_encoder+(left_speed+right_speed)/2;	
				}
				if(jinduan1_encoder>=jd1jifen1)//�����һ��·��
				{
					jinduan1_flag=1;//�رջ���
					if(jinduan1zisuo==0)//����
					{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);//��ת
							delay_ms(800);
						  jinduan1zisuo=1;
							jinduan1_flag2=1;
					}
				}
				if(jinduan1_flag2==1)//���ﲡ������
				{
					jinduan1_encoder2=jinduan1_encoder2+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder2>=jd1jifen2)//�Ƿ񵽴�ҩ��
				{
					jinduan1_flag2=0;
					if(jinduan1zisuo2==0)//����
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)//�ȴ�ж��ҩƷ
						{	
							
						}
						Red_led=1;
						delay_ms(500);
						Load(-2000,2000);//����
						delay_ms(1000);	
						delay_ms(400);
						jinduan1zisuo2=1;
						jinduan1_flag3=1;//��ʼ���ػ���
					}					
				}
				if(jinduan1_flag3==1)//��ʼ��¼��·��1�Ļ���
				{
					jinduan1_encoder3=jinduan1_encoder3+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder3>=jd1jifen2fanhui)//�Ӳ�����·�ڵĻ���
				{
					jinduan1_flag3=0;//�رջ���
					if(jinduan1zisuo3==0)//����
					{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);//��ת
							delay_ms(500);
						  jinduan1zisuo3=1;
							jinduan1_flag4=1;//��ʼ����						
					}				
				}
				if(jinduan1_flag4==1)//��ʼ���ػ���
				{
					jinduan1_encoder4=jinduan1_encoder4+(left_speed+right_speed)/2;
				}
				if(jinduan1_encoder4>=jd1jifen1fanhui)//�ܷ���
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
			if(xunji_flag==1)	//ѭ����־	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//��ƫ��ת
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//��ƫ��ת
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//��ƫ��ת
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//��ƫ��ת
				}
				if(jinduan2_flag==0)//��ʼ����
				{
					jinduan2_encoder=jinduan2_encoder+(left_speed+right_speed)/2;	
				}
				if(jinduan2_encoder>=jd2jifen1)//�����һ��·��
				{
					jinduan2_flag=1;//�رջ���
					if(jinduan2zisuo==0)//����
					{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);//��ת
							delay_ms(500);
						  jinduan2zisuo=1;
							jinduan2_flag2=1;
					}
				}
				if(jinduan2_flag2==1)//���ﲡ������
				{
					jinduan2_encoder2=jinduan2_encoder2+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder2>=jd2jifen2)//�Ƿ񵽴�ҩ��
				{
					jinduan2_flag2=0;
					if(jinduan2zisuo2==0)//����
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)//�ȴ�ж��ҩƷ
						{	
							
						}
						Red_led=1;
						delay_ms(500);
						Load(-2000,2000);//����
						delay_ms(1000);	
						delay_ms(400);
						jinduan2zisuo2=1;
						jinduan2_flag3=1;//��ʼ���ػ���
					}					
				}
				if(jinduan2_flag3==1)//��ʼ��¼��·��1�Ļ���
				{
					jinduan2_encoder3=jinduan2_encoder3+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder3>=jd2jifen2fanhui)//�Ӳ�����·�ڵĻ���
				{
					jinduan2_flag3=0;//�رջ���
					if(jinduan2zisuo3==0)//����
					{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);//תת
							delay_ms(800);
						  jinduan2zisuo3=1;
							jinduan2_flag4=1;//��ʼ����						
					}				
				}
				if(jinduan2_flag4==1)//��ʼ���ػ���
				{
					jinduan2_encoder4=jinduan2_encoder4+(left_speed+right_speed)/2;
				}
				if(jinduan2_encoder4>=jd2jifen1fanhui)//�ܷ���
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
			if(xunji_flag==1)	//ѭ����־	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//��ƫ��ת
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//��ƫ��ת
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//��ƫ��ת
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//��ƫ��ת
				}
				if(zd_encoder<18000)
				{
					K210_num[0]=0;
				}
				if((K210_num[0]==k210_num_ok)&&(zd_encoder>18000))//�ڶ���·���Ƿ�ʶ��Ŀ������
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
				if(zd_encoder>=zdjifen1)//����ڶ���·��**23380********/
				{
					lukou_count=1;//������
					if(zhongdaun_turn==0)//����
					{
						if(qidong_1!=1)
						{
								if(exp_num==k210_num_ok)//ʶ��Ŀ�����֣���ת
								{	
									Load(0,0);
									delay_ms(200);
									Load(2000,-2000);
									delay_ms(800);//900��800
									zhongduan_right=0;
									zhongduan_right2=1;						
								}
								else//û��ʶ�𵽣���ת
								{
									Load(0,0);
									delay_ms(200);
									Load(-2000,2000);
									delay_ms(800);
									zhongduan_left=0;
									zhongduan_left2=1;							
								}
								lukou2_start=1;//��ʼ��¼��ֹͣ����·��
								zhongdaun_turn=1;//׼����ֹͣ��
						}
						else//˫��
						{
							if(shuagche_turnflag==2)//��ת
							{
									Load(0,0);
									delay_ms(200);
									Load(2000,-2000);
									delay_ms(800);//900��800							
							}
							else if(shuagche_turnflag==3)//��ת
							{
									Load(0,0);
									delay_ms(200);
									Load(-2000,2000);
									delay_ms(800);								
							}
							cclukou2_trunflag=1;//����1˫��
							zhongdaun_turn=1;//׼����ֹͣ��
						}						
					}
				}
				if(lukou2_start==1)//·��2��ʼ��¼·��****5800******/
				{
					lukou2_startencoder=lukou2_startencoder+(left_speed+right_speed)/2;
					if(lukou2_startencoder>=zdjifen2)//ֹͣ
					{
						Load(0,0);
						Red_led=0;
						while(KEY0==0)
						{	
							
						}
						Red_led=1;
						delay_ms(200);
						Load(-2000,2000);//����
						delay_ms(1000);	
						delay_ms(400);
						lukou2_start=0;//����
						zdlukou2_fanhui=1;//׼����¼����·��2����ֵ
					}
				}
				if(zdlukou2_fanhui==1)//·��2����ת��*****5500*****/
				{
					zd_encoder2=zd_encoder2+(left_speed+right_speed)/2;  //��ʼ��¼
					if(zd_encoder2>=zdjifen2fanhui)
					{
						if(zhongduan_left2==1)//����ʱ��ת
						{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);
							zhongduan_left2=0;//����					
						}	
						else//����ʱ��ת
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);
							zhongduan_right2=0;//����          
						}	
						zdfanhuix=1;
						zdlukou2_fanhui=0;//����
					}
				}
				if(zdfanhuix==1)//�ܷ���**********/
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

				if(cclukou2_trunflag==1)//����1
				{
					cc_encoder=cc_encoder+(left_speed+right_speed)/2;
				}
				if(cc_encoder>=lukou2_banxian)//����1 ·��2��ͣ����
				{
					cclukou2_trunflag=0;
					if(cclukou2_zisuo==0)
					{
						Load(0,0);
						Yellow_led=0;
						while(start_flag!=5);//��ʼȥĿ��ҩ��
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
				if(exp_pos_encoder>=lukou2_hengxian)//����1���ж�����������
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
			if(xunji_flag==1)	//ѭ����־	
			{				
					if((MV_xunji[2]==1)&&(MV_xunji[1]==0)&&(MV_xunji[3]==0))
				{
				  
					Load(speed_pid,speed_pid);
				}
				else if((MV_xunji[1]==1)&&(MV_xunji[0]==0))
				{
						Load(speed_pid-speed_pid*0.1,speed_pid+speed_pid*0.1);//��ƫ��ת
				}
				else if(MV_xunji[0]==1)
				{
						Load(speed_pid-speed_pid*0.2,speed_pid+speed_pid*0.2);//��ƫ��ת
				}
			///////////////////
				else if((MV_xunji[3]==1)&&(MV_xunji[4]==0))
				{
						Load(speed_pid+speed_pid*0.1,speed_pid-speed_pid*0.1);//��ƫ��ת
				}	
				else if(MV_xunji[4]==1)
				{
						Load(speed_pid+speed_pid*0.2,speed_pid-speed_pid*0.2);//��ƫ��ת
				}
        if(lukou4_encoder<2500)
        {
					K210_num[0]=0;
				}
				if((K210_num[0]==k210_num_ok)&&(lukou4_encoder>3000))//���ĸ�·���Ƿ�ʶ��Ŀ������
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
				if(lukou3_encoder>=ydjifen1)//���������·��****35900******/**************/
				{
					K210_num[0]=0;
					lukou3_encoderflag=1;//������
					if(zhongdaun_turn==0)//����
					{
						if(yd_trunflag==1)//Ŀ���������ұߣ���ת
						{	
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900��800							
						}
						else//û��ʶ�𵽣���ת
						{
							Load(0,0);
							delay_ms(200);
							Load(-2000,2000);
							delay_ms(500);						
						}
						lukou4_encoderflag=1;//��ʼ��¼��ֹͣ����·��
						zhongdaun_turn=1;//׼����ֹͣ��
				  }
				}
				if(lukou4_encoderflag==1)//������·�ڵ����ĸ�·�ڼ���
				{
					lukou4_encoder=lukou4_encoder+(left_speed+right_speed)/2;
				}
				if(lukou4_encoder>=ydjifen2)/**********13050���߶�***********************/
				{
					lukou4_encoderflag=0;
					if(lukou4zisuo==0)
					{
						if(exp_num==k210_num_ok)//ʶ��Ŀ�����֣���ת
						{	
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900��800	
              xxfanhui_trun=1;							
						}
						else//û��ʶ�𵽣���ת
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
				if(lukou5_encoderflag==1)/**********4-5·�ڻ���**********/
				{
					lukou5_encoder=lukou5_encoder+(left_speed+right_speed)/2;
				}
				if(lukou5_encoder>=ydjifen3)/********5800***********///����
				{
					if(lukou5zisuo==0)//����
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
							Load(-2000,2000);//����
							delay_ms(1000);	
							delay_ms(200);
							lukou5zisuo=1;
							xxfanhui=1;
						}
						else//����2
						{
							Load(0,0);
							Red_led=0;
							while(1);						
						}
					}
				}
				if(xxfanhui==1)//��һ�η���
				{
					xxfanhui_encoder=xxfanhui_encoder+(left_speed+right_speed)/2;
				}
				if(xxfanhui_encoder>=ydjifen3fanhui)//����1
				{
					xxfanhui=0;
					if(xxfanhui1==0)
					{
						if(xxfanhui_trun==0)//������ת
						{
							Load(0,0);
							delay_ms(200);
							Load(2000,-2000);
							delay_ms(500);//900��800
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
				if(xxfanhui2==1)//����2����
				{
					xxencoder2=xxencoder2+(left_speed+right_speed)/2;
				}
				if(xxencoder2>=ydjifen2fanhui)//���߷��ػ���
				{
					xxfanhui2=0;
					if(xxzisuo==0)
					{
						if(yd_trunflag==1)//������ת
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
							delay_ms(500);//900��800							
						}
						xx_zong=1;
						xxzisuo=1;
					}
					
				}
        if(xx_zong==1)//�ܷ��̻���
				{
					xx_zongencoder=xx_zongencoder+(left_speed+right_speed)/2;
				}
				if(xx_zongencoder>=ydjifen1fanhui)//�ܷ���1-35900
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_mpuextiGPIOx,ENABLE);//����ʱ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;/**��1��**///GPIO_Mode_AF_PP
	GPIO_InitStruct.GPIO_Pin=mpuexti_GPIO_Pin_x;//PB5����Ϊ��������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(mpuexti_GPIOx,&GPIO_InitStruct);	
	
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* �����ж�Դ������1 */
  NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;//��Ҫ����
  /* ������ռ���ȼ� */
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
  /* ���������ȼ� */
  NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

	
	GPIO_EXTILineConfig(mpuexti_GPIO_PortSourceGPIOx,mpuexti_GPIO_PinSourcex);//
	
	EXTI_InitStruct.EXTI_Line=mpuexti_Linex;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
}




