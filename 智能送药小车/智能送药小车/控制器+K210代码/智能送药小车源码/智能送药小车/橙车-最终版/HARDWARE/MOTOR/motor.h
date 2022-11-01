#ifndef  _MOTOR_H
#define  _MOTOR_H

#include "sys.h" 
#include "pwm.h"


#define PWM_MAX  7200
#define PWM_MIN  -7200

#define Ain1  PBout(12)
#define Ain2  PBout(13)

#define Bin1  PBout(14)
#define Bin2  PBout(15)







void Motor_Init(void);/*¡¾5¡¿*/
void Limit(int *motoA,int *motoB);
int GFP_abs(int p);
void Load(int moto1,int moto2);
#endif

