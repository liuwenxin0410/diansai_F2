#include "pid.h"
#include "oled.h"
float Speed_err,Speed_last_err;  //此次误差和上次误差
float Speed_err_difference,Speed_last_err_difference;  //误差的差值
float Speed_S=0;
float Right_err,Right_last_err;  //此次误差和上次误差
float Right_err_difference;  //误差的差值	


float Speed_err2,Speed_last_err2;  //此次误差和上次误差
float Speed_err_difference2,Speed_last_err_difference2;  //误差的差值
float Speed_S2=0;

float Speed_err3,Speed_last_err3;  //此次误差和上次误差
float Speed_err_difference3,Speed_last_err_difference3;  //误差的差值
float Speed_S3=0;

float Speed_err4,Speed_last_err4;  //此次误差和上次误差
float Speed_err_difference4,Speed_last_err_difference4;  //误差的差值
float Speed_S4=0;

/*Kp=4000,等幅振荡*/

int X_PID(float calcu,float measure,float KPX,float KDX,float KIX)  //左右平衡
{
	float a=0.7;
	int pwm;

	Speed_err = calcu-measure;               //误差

	Speed_err_difference = Speed_err - Speed_last_err;   //误差的差值
	
	Speed_err_difference = (1-a)*Speed_err+a*Speed_last_err_difference;
	
	Speed_S= Speed_S+Speed_err;

	Speed_last_err = Speed_err;                    //此次误差记录为“上次误差”
	
	Speed_last_err_difference= Speed_err_difference;
	
	pwm=KPX*Speed_err + KDX*Speed_err_difference + KIX*Speed_S; //结果

	return pwm;//结果 = kpP+kdD
}



int Y_Vertical_PID(float calcu2,float measure2,float KPX2,float KDX2,float KIX2)  //直立环
{
	float a2=0.7;
	int pwm1;

	Speed_err2 = calcu2-measure2;               //误差

	Speed_err_difference2 = Speed_err2 - Speed_last_err2;   //误差的差值
	 	
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
	
	Speed_last_err2 = Speed_err2;                    //此次误差记录为“上次误差”
	
	Speed_last_err_difference2= Speed_err_difference2;
	
	pwm1= KPX2*Speed_err2 + KDX2*Speed_err_difference2 + KIX2*Speed_S2; //结果 = kpP+kdD
	
	return pwm1;
}


int Y_SPEED_PWM(float calcu3,float measure3,float KPX3,float KDX3,float KIX3)  //速度环
{
	float a3=0.7;
	int pwm3;

	Speed_err3 = calcu3-measure3;               //误差
	
	Speed_err_difference3 = Speed_err3 - Speed_last_err3;   //误差的差值
	
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
	
	Speed_last_err3 = Speed_err3;                    //此次误差记录为“上次误差”
	
	Speed_last_err_difference3= Speed_err_difference3;
	
	pwm3= KPX3*Speed_err3 + KDX3*Speed_err_difference3 + KIX3*Speed_S3; //结果 = kpP+kdD
	
	return pwm3; //结果 = kpP+kdD	
	
}



int Y_TURN_PID(float calcu4,float measure4,float KPX4,float KDX4,float KIX4)  //转向环
{
	float a4=0.7;
	int pwm4;
	
	Speed_err4 = calcu4-measure4;               //误差

  //if(Speed_err4>180 || Speed_err4<-180) Speed_err4=Speed_last_err4; //出现bug则舍弃本次误差 2021.7.23	
	
	Speed_err_difference4 = Speed_err4 - Speed_last_err4;   //误差的差值
	
	Speed_S4= Speed_S4+Speed_err4;
	
	Speed_last_err4 = Speed_err4;                    //此次误差记录为“上次误差”
	
	Speed_last_err_difference4= Speed_err_difference4;
	
	pwm4= KPX4*Speed_err4 + KDX4*Speed_err_difference4 + KIX4*Speed_S4; //结果 = kpP+kdD
	
	return pwm4; //结果 = kpP+kdD	
	
	
}

