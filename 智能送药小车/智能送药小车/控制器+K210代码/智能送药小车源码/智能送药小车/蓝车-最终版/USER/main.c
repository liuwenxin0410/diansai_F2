#include "sys.h"
#include "hcsr04.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "exti.h"
#include "encoder.h"
#include "duoji.h"
#include "bsp_TiMbase.h" 
#include "menu.h"

/*����������*/
float pitch,roll,yaw,speed;			//�Ƕ�
float left_speed=0,right_speed=0;
short gyrox,gyroy,gyroz;				//������--���ٶ�
short aacx,aacy,aacz;						//���ٶ�

/*��������ͷ����������*/
extern uint8_t MV_xunji[5];
extern uint8_t K210_num[3];
extern uint8_t MV_num;


/*����ִ�б�־*/
extern uint8_t xunji_flag;
extern uint8_t left_turn_flag1;
/*����ִ�б���*/
extern uint8_t zhongduan_count;
uint8_t k210_num_ok=0;

/*����ͨ��С��1*/
int count_send=0;

/*******д��*******/
extern uint32_t left_encoder,right_encoder;
extern uint32_t zd_encoder; 

/**********������Զ��********/
uint16_t num_count=0;
uint8_t start_flag1=0;
uint16_t num_count1=0;
uint8_t X_exp=0;
extern uint8_t shibie_flag33;
uint8_t jinduan=0,yuanduan=0;
extern uint8_t shibie_flagnn;
extern uint8_t fahui2_flag;


/*����˵���������ʱ����*/
extern int menu;
extern struct MenuItem MainMenu[2];        //������
extern struct MenuItem Setmenu1[4]; 
extern struct MenuItem Setmenu2[4]; 
struct MenuItem* MenuPoint = MainMenu;     //�ṹ�����
short selectItem;
int main(void)
{
		u8 key=0;

	 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ�����

	  OLED_Init();           //OLED��ʼ��
	  MPU_Init();            //MPU6050��ʼ��
	  DMP_Init(); 
	  mpu_dmp_init(); 
	
    Motor_Init();					 //�����ʼ��
    GENERAL_TIM_Init();    //��ʱ��4��PWM��ʼ��
	  PWM_Init_TIM8();       //���PWM��ʼ��
	  //ͨ��3��1500�еȣ�1200����//1400
    TIM_SetCompare4(TIM8,1400);
	  Encoder_TIM3_Init();   //������2��ʼ��
	  Encoder_TIM2_Init();   //������1��ʼ��	
	
		LED_Init();            //LED��ʼ��
		KEY_Init();            //������ʼ��
    BEEP_GPIO_Config();    //������
	
	  //HCSR04_Init();         //������ 
	  //BASIC_TIM_Init();    //��ʱ����ʼ��
	
    /***********��ʼ���˵��ȼ�**********/	
		MainMenu[0].ChildrenMenus = Setmenu1;
		MainMenu[1].ChildrenMenus = Setmenu2;
		selectItem =1;	
		//display(MenuPoint,selectItem);

    USART2_Config();		 //����2��ʼ��
		USART1_Config();     //����1��ʼ��	
	  USART3_Config();     //����3��ʼ��
		MPU6050_EXTI_Init();   //�ⲿ�ж�
	  while(1)
    {
			if(start_flag1==1)
			{
				OLED_ShowStr(0,0,"num:",2);
				OLED_zhengshu_2wei(30,0,k210_num_ok,2);
				OLED_zhengshu_2wei(80,0,K210_num[0],2);
				OLED_ShowStr(0,2,"xunji:",2);
				OLED_zhengshu_2wei(80,2,zhongduan_count,2);
				OLED_zhengshu_2wei(0,4,MV_xunji[0],1);
				OLED_zhengshu_2wei(24,4,MV_xunji[1],1);
				OLED_zhengshu_2wei(48,4,MV_xunji[2],1);
				OLED_zhengshu_2wei(72,4,MV_xunji[3],1);
				OLED_zhengshu_2wei(96,4,MV_xunji[4],1);
				OLED_ShowStr(0,6,"hongwai:",2);
				OLED_ShowNum33(80,6,KEY0,2);
			}
			if(start_flag1==0)
			{
				while(KEY0==1)//û�зź���
				{						
					OLED_ShowNum55(0,0,shibie_flagnn,2);
					OLED_ShowStr(40,0,"<",2);
					OLED_zhengshu_2wei(50,0,70,2);
				  OLED_ShowStr(0,4,"exp_num:",2);					
					OLED_ShowNum55(80,4,k210_num_ok,2);
				  OLED_ShowStr(0,6,"Xn:",2);						
					OLED_zhengshu_2wei(30,6,K210_num[1],2);
					OLED_ShowStr(50,6,"Xe:",2);					
					OLED_zhengshu_2wei(80,6,X_exp,2);
					OLED_zhengshu_2wei(100,0,MV_xunji[2],2);
					
				}
				if((k210_num_ok!=1)&&(k210_num_ok!=2))//���ֲ���1��2
				{
					K210_num[0]=0;
					if(shibie_flagnn>=70)
					{
						yuanduan=1;
					}
					else
					{
						jinduan=1;				
					}
					OLED_Clear();				
					delay_ms(500);
					if(yuanduan==1)
					{
						yuanduan=0;
						room4_start();
					}
					if(jinduan==1)
					{
						jinduan=0;
						room3_start();
					}
					start_flag1=1;				
				}
				if(k210_num_ok==1)//������1
				{
					OLED_Clear();				
					delay_ms(500);
					room1_start();
					start_flag1=1;
				}
				if(k210_num_ok==2)//������2
				{
					OLED_Clear();				
					delay_ms(500);
					room2_start();
					start_flag1=1;
				}
		}
	}
}				
			
//OLED_ShowNum55(0,0,left_encoder,2);	
//OLED_ShowNum55(0,2,right_encoder,2);			
			
	
//			Load(-2000,2000);
//			delay_ms(1000);	
//			delay_ms(550);
//			Load(0,0);			
//		  delay_ms(1000);	

			
//			Load(-2000,2000);
//			delay_ms(1000);	
//			delay_ms(900);
//			Load(0,0);			
//				delay_ms(1000);		
			
			
			
			
			
			
			
			
			
//			Yellow_led=0;
//			delay_ms(1000);
//			Yellow_led=1;
//			delay_ms(1000);
			//OLED_Show_pitch_Angle(yaw);

//			OLED_ShowAngle(0,0);
//			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//�Ƕ�,С��
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�����ǣ�����
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//���ٶȣ�
//			printf("%d\n\r",Read_Speed(3));
//			printf("%f\n\r",Hcsr04GetLength());
			//Beep_start();
//			delay_ms(1000);
//			TIM_SetCompare3(TIM8,1000);
//			delay_ms(1000);
//			TIM_SetCompare3(TIM8,1500);
//			delay_ms(1000);
//			TIM_SetCompare3(TIM8,1700);
//			delay_ms(1000);
//			TIM_SetCompare4(TIM8,2000);
//			delay_ms(1000);
//			Load(-3000,3000);
//			delay_ms(1000);
//			delay_ms(1000);
			//Load(0,0);
//			delay_ms(1000);
//			delay_ms(1000);
//			LED0_TOGGLE;
//			delay_ms(1000);
//			LED2=0;
//			LED1=0;
//			LED0=0;
//			delay_ms(1000);







