#ifndef __OLED_H
#define __OLED_H
#include "oled_i2c.h"
#include "delay.h"

int  OLED_Command(unsigned char Command);
int  OLED_Data(unsigned char Data);
void OLED_Fill(unsigned char fill_Data);//全屏填充，可实现清屏或白屏(0x00  0xff)
void OLED_SetPos(unsigned char x, unsigned char y); //设置起始点坐标
void OLED_ON(void);
void OLED_OFF(void);	//让OLED休眠
void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示一位数字
int Num_Digit(int num);//计算五位数以内数字位数
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//显示BMP图

//以下常用
void OLED_Init(void);
void OLED_Clear(void);//清屏

void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//显示汉字,x+16(0-127),y(0-6);

void OLED_ShowNum55(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//在一行显示五位数以内数字 
void OLED_ShowNum44(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//在一行显示四位数以内数字 
void OLED_ShowNum33(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//在一行显示三位数以内数字

//TextSize -- 字符大小(1:6*8 ; 2:8*16)
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//显示字符串
/*用空格覆盖*/
//OLED_ShowStr(0,0,"456789",2);//显示字符串
//OLED_ShowStr(0,0,"1234  ",2);//显示字符串	

void OLED_ShowAngle(float pitch,float roll);//带符号的小数角度显示，例如-12.3
void OLED_Show_pitch_Angle(float pitch);//带符号小数角度显示，例如-12.3
void OLED_ShowPWM(int PWMX,int PWMY);//显示四位以内带符号数

void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示小数，输入208，输出20.8，输入没有3位，输出前面补空格
void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示小数，输入2008，输出200.8，输入没有4位，输出前面补空格
void OLED_Shownum4(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示小数，输入20008，输出2000.8，输入没有5位，输出前面补零

void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示4位整数，例0123
void Showfuhaoshu_4wei(int PWMX);//显示四位带符号整数
void OLED_zhengshu_3wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示3位整数，例012
void Showfuhaoshu_3wei(int PWMX);//显示三位带符号整数
void OLED_zhengshu_2wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示2位整数，例01
void Showfuhaoshu_2wei(int PWMX);//显示二位带符号整数

void OLED_Show_xiaoshu2(float pitchm);
void OLED_Show_Real(float Pitchx,float Rollx,float Yawx,float Speedx,float Lengthx,float Timex,float Radiusx);
void OLED_Show_Expect(float Pitche,float Rolle,float Yawe,float Speede,float Lengthe,float Timee,float Radiuse);

#endif
