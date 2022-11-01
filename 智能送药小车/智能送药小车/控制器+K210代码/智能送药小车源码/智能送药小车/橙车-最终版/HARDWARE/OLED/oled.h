#ifndef __OLED_H
#define __OLED_H
#include "oled_i2c.h"
#include "delay.h"

int  OLED_Command(unsigned char Command);
int  OLED_Data(unsigned char Data);
void OLED_Fill(unsigned char fill_Data);//ȫ����䣬��ʵ�����������(0x00  0xff)
void OLED_SetPos(unsigned char x, unsigned char y); //������ʼ������
void OLED_ON(void);
void OLED_OFF(void);	//��OLED����
void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾһλ����
int Num_Digit(int num);//������λ����������λ��
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//��ʾBMPͼ

//���³���
void OLED_Init(void);
void OLED_Clear(void);//����

void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//��ʾ����,x+16(0-127),y(0-6);

void OLED_ShowNum55(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��һ����ʾ��λ���������� 
void OLED_ShowNum44(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��һ����ʾ��λ���������� 
void OLED_ShowNum33(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��һ����ʾ��λ����������

//TextSize -- �ַ���С(1:6*8 ; 2:8*16)
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//��ʾ�ַ���
/*�ÿո񸲸�*/
//OLED_ShowStr(0,0,"456789",2);//��ʾ�ַ���
//OLED_ShowStr(0,0,"1234  ",2);//��ʾ�ַ���	

void OLED_ShowAngle(float pitch,float roll);//�����ŵ�С���Ƕ���ʾ������-12.3
void OLED_Show_pitch_Angle(float pitch);//������С���Ƕ���ʾ������-12.3
void OLED_ShowPWM(int PWMX,int PWMY);//��ʾ��λ���ڴ�������

void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾС��������208�����20.8������û��3λ�����ǰ�油�ո�
void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾС��������2008�����200.8������û��4λ�����ǰ�油�ո�
void OLED_Shownum4(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾС��������20008�����2000.8������û��5λ�����ǰ�油��

void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾ4λ��������0123
void Showfuhaoshu_4wei(int PWMX);//��ʾ��λ����������
void OLED_zhengshu_3wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾ3λ��������012
void Showfuhaoshu_3wei(int PWMX);//��ʾ��λ����������
void OLED_zhengshu_2wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾ2λ��������01
void Showfuhaoshu_2wei(int PWMX);//��ʾ��λ����������

void OLED_Show_xiaoshu2(float pitchm);
void OLED_Show_Real(float Pitchx,float Rollx,float Yawx,float Speedx,float Lengthx,float Timex,float Radiusx);
void OLED_Show_Expect(float Pitche,float Rolle,float Yawe,float Speede,float Lengthe,float Timee,float Radiuse);

#endif
