#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
//float Kp,Kd;
int X_PID(float calcu,float measure,float KPX,float KDX,float KIX);//左右平衡

int Y_Vertical_PID(float calcu2,float measure2,float KPX2,float KDX2,float KIX2);//直立环
	
int Y_SPEED_PWM(float calcu3,float measure3,float KPX3,float KDX3,float KIX3);//速度环

int Y_TURN_PID(float calcu4,float measure4,float KPX4,float KDX4,float KIX4);  //转向环

#endif

