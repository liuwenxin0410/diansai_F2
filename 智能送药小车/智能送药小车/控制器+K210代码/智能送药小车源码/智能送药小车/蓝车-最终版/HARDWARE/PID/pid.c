#include "pid.h"
#include "oled.h"
float Speed_err,Speed_last_err;  //�˴������ϴ����
float Speed_err_difference,Speed_last_err_difference;  //���Ĳ�ֵ
float Speed_S=0;
float Right_err,Right_last_err;  //�˴������ϴ����
float Right_err_difference;  //���Ĳ�ֵ	


float Speed_err2,Speed_last_err2;  //�˴������ϴ����
float Speed_err_difference2,Speed_last_err_difference2;  //���Ĳ�ֵ
float Speed_S2=0;

float Speed_err3,Speed_last_err3;  //�˴������ϴ����
float Speed_err_difference3,Speed_last_err_difference3;  //���Ĳ�ֵ
float Speed_S3=0;

float Speed_err4,Speed_last_err4;  //�˴������ϴ����
float Speed_err_difference4,Speed_last_err_difference4;  //���Ĳ�ֵ
float Speed_S4=0;

/*Kp=4000,�ȷ���*/

int X_PID(float calcu,float measure,float KPX,float KDX,float KIX)  //����ƽ��
{
	float a=0.7;
	int pwm;

	Speed_err = calcu-measure;               //���

	Speed_err_difference = Speed_err - Speed_last_err;   //���Ĳ�ֵ
	
	Speed_err_difference = (1-a)*Speed_err+a*Speed_last_err_difference;
	
	Speed_S= Speed_S+Speed_err;

	Speed_last_err = Speed_err;                    //�˴�����¼Ϊ���ϴ���
	
	Speed_last_err_difference= Speed_err_difference;
	
	pwm=KPX*Speed_err + KDX*Speed_err_difference + KIX*Speed_S; //���

	return pwm;//��� = kpP+kdD
}



int Y_Vertical_PID(float calcu2,float measure2,float KPX2,float KDX2,float KIX2)  //ֱ����
{
	float a2=0.7;
	int pwm1;

	Speed_err2 = calcu2-measure2;               //���

	Speed_err_difference2 = Speed_err2 - Speed_last_err2;   //���Ĳ�ֵ
	 	
	Speed_S2=Speed_S2+Speed_err2;
//	
//	if(Speed_S2>200)
//	{
//		Speed_S2=200;
//	}
//	if(Speed_S2<-200)
//	{
//		Speed_S2=-200;
//	}
	
	Speed_last_err2 = Speed_err2;                    //�˴�����¼Ϊ���ϴ���
	
	Speed_last_err_difference2= Speed_err_difference2;
	
	pwm1= KPX2*Speed_err2 + KDX2*Speed_err_difference2 + KIX2*Speed_S2; //��� = kpP+kdD
	
	return pwm1;
}


int Y_SPEED_PWM(float calcu3,float measure3,float KPX3,float KDX3,float KIX3)  //�ٶȻ�
{
	float a3=0.7;
	int pwm3;

	Speed_err3 = calcu3-measure3;               //���
	
	Speed_err_difference3 = Speed_err3 - Speed_last_err3;   //���Ĳ�ֵ
	
	Speed_err3 = (1-a3)*Speed_err3+a3*Speed_last_err3;
	
	Speed_S3= Speed_S3+Speed_err3;
	
	if(Speed_S3>500)
	{
		Speed_S3=500;
	}
	if(Speed_S3<-500)
	{
		Speed_S3=-500;
	}
	
	Speed_last_err3 = Speed_err3;                    //�˴�����¼Ϊ���ϴ���
	
	Speed_last_err_difference3= Speed_err_difference3;
	
	pwm3= KPX3*Speed_err3 + KDX3*Speed_err_difference3 + KIX3*Speed_S3; //��� = kpP+kdD
	
	return pwm3; //��� = kpP+kdD	
	
}



int Y_TURN_PID(float calcu4,float measure4,float KPX4,float KDX4,float KIX4)  //ת��
{
	float a4=0.7;
	int pwm4;
	
	Speed_err4 = calcu4-measure4;               //���

  //if(Speed_err4>180 || Speed_err4<-180) Speed_err4=Speed_last_err4; //����bug������������� 2021.7.23	
	
	Speed_err_difference4 = Speed_err4 - Speed_last_err4;   //���Ĳ�ֵ
	
	Speed_S4= Speed_S4+Speed_err4;
	
	Speed_last_err4 = Speed_err4;                    //�˴�����¼Ϊ���ϴ���
	
	Speed_last_err_difference4= Speed_err_difference4;
	
	pwm4= KPX4*Speed_err4 + KDX4*Speed_err_difference4 + KIX4*Speed_S4; //��� = kpP+kdD
	
	return pwm4; //��� = kpP+kdD	
	
	
}

