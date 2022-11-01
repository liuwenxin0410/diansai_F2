#include "oled.h"
#include "codetab.h"//oled�ַ���


void OLED_Show_xiaoshu2(float pitchm)
{
	int Pitchm=0;
	unsigned int ge,shi,bai;
  Pitchm=(int)(pitchm*10);
	ge=Pitchm%10;
	shi=(Pitchm%100)/10;
	bai=(Pitchm%1000)/100;
	
		    OLED_ShowSNum(0,2,bai,2);
		    OLED_ShowSNum(8,2,shi,2);
		    OLED_ShowStr(16,2,".",2);
		    OLED_ShowSNum(24,2,ge,2);	

	
}












void OLED_Show_Real(float Pitchx,float Rollx,float Yawx,float Speedx,float Lengthx,float Timex,float Radiusx)
{
	int Pitch,Roll,Yaw,OLED_Speed,OLED_Length,OLED_Time,OLED_Radius;
	Pitch=(int)(Pitchx*10);
	Roll=(int)(Rollx*10);		
	Yaw=(int)(Yawx*10);
  OLED_Speed=(int)(Speedx*10);
  OLED_Length=(int)(Lengthx*10);
  OLED_Time=(int)(Timex*10);
	OLED_Radius=(int)(Radiusx*10);
	
	OLED_ShowStr(24,0,"Real",1);	
  OLED_ShowStr(0,1,"Pitch:",1);	
  OLED_ShowStr(0,2,"Roll:",1);		
  OLED_ShowStr(0,3,"Yaw:",1);		
  OLED_ShowStr(0,4,"Radius:",1);
  OLED_ShowStr(0,5,"Length:",1);		
  OLED_ShowStr(0,6,"Time:",1);	
  OLED_ShowStr(0,7,"Speed:",1);	

	if(Pitch<0)
	{
		OLED_ShowStr(42,1,"-",1);           //��ʾ����
		Pitch=-Pitch;	
	}
	else OLED_ShowStr(42,1," ",1);        //�ڸǸ���
	OLED_Shownum2(48,1,Pitch,1);          //��ʾ������
	
  if(Roll<0)
	{
		OLED_ShowStr(42,2,"-",1);		
		Roll=-Roll;		        
	}
	else OLED_ShowStr(42,2," ",1); 
	OLED_Shownum2(48,2,Roll,1);	          //��ʾ������		
	
  if(Yaw<0)
	{
		OLED_ShowStr(42,3,"-",1);		
		Yaw=-Yaw;		        
	}
	else OLED_ShowStr(42,3," ",1); 
	OLED_Shownum2(48,3,Yaw,1);	          //��ʾ�����		
	
  if(OLED_Speed<0)
	{
		OLED_ShowStr(42,7,"-",1);		
		OLED_Speed=-OLED_Speed;		        
	}
	else OLED_ShowStr(42,7," ",1); 
	OLED_Shownum3(48,7,OLED_Speed,1);	    //��ʾ�뾶		
	
  if(OLED_Length<0)
	{
		OLED_ShowStr(42,5,"-",1);		
		OLED_Length=-OLED_Length;		        
	}
	else OLED_ShowStr(42,5," ",1); 
	OLED_Shownum2(48,5,OLED_Length,1);	  //��ʾ·��		
	
  if(OLED_Time<0)
	{
		OLED_ShowStr(42,6,"-",1);		
		OLED_Time=-OLED_Time;		        
	}
	else OLED_ShowStr(42,6," ",1); 
	OLED_Shownum2(48,6,OLED_Time,1);	    //��ʾʱ��	
	
  if(OLED_Radius<0)
	{
		OLED_ShowStr(42,4,"-",1);		
		OLED_Radius=-OLED_Radius;		        
	}
	else OLED_ShowStr(42,4," ",1); 
	OLED_Shownum2(48,4,OLED_Radius,1);	   //��ʾ�ٶ�	

}

void OLED_Show_Expect(float Pitche,float Rolle,float Yawe,float Speede,float Lengthe,float Timee,float Radiuse)
{
	int Pitch,Roll,Yaw,OLED_Speed,OLED_Length,OLED_Time,OLED_Radius;
	Pitch=(int)(Pitche*10);
	Roll=(int)(Rolle*10);		
	Yaw=(int)(Yawe*10);
  OLED_Speed=(int)(Speede*10);
  OLED_Length=(int)(Lengthe*10);
  OLED_Time=(int)(Timee*10);
	OLED_Radius=(int)(Radiuse*10);
	
	OLED_ShowStr(84,0,"Expect",1);	

	if(Pitch<0)
	{
		OLED_ShowStr(90,1,"-",1);           //��ʾ����
		Pitch=-Pitch;	
	}
	else OLED_ShowStr(90,1," ",1);        //�ڸǸ���
	OLED_Shownum2(96,1,Pitch,1);          //��ʾ������
	
  if(Roll<0)
	{
		OLED_ShowStr(90,2,"-",1);		
		Roll=-Roll;		        
	}
	else OLED_ShowStr(90,2," ",1); 
	OLED_Shownum2(96,2,Roll,1);	          //��ʾ������		
	
  if(Yaw<0)
	{
		OLED_ShowStr(90,3,"-",1);		
		Yaw=-Yaw;		        
	}
	else OLED_ShowStr(90,3," ",1); 
	OLED_Shownum2(96,3,Yaw,1);	          //��ʾ�����		
	
  if(OLED_Speed<0)
	{
		OLED_ShowStr(90,7,"-",1);		
		OLED_Speed=-OLED_Speed;		        
	}
	else OLED_ShowStr(90,7," ",1); 
	OLED_Shownum3(96,7,OLED_Speed,1);	    //��ʾ�뾶		
	
  if(OLED_Length<0)
	{
		OLED_ShowStr(90,5,"-",1);		
		OLED_Length=-OLED_Length;		        
	}
	else OLED_ShowStr(90,5," ",1); 
	OLED_Shownum2(96,5,OLED_Length,1);	  //��ʾ·��		
	
  if(OLED_Time<0)
	{
		OLED_ShowStr(90,6,"-",1);		
		OLED_Time=-OLED_Time;		        
	}
	else OLED_ShowStr(90,6," ",1); 
	OLED_Shownum2(96,6,OLED_Time,1);	    //��ʾʱ��	
	
  if(OLED_Radius<0)
	{
		OLED_ShowStr(90,4,"-",1);		
		OLED_Radius=-OLED_Radius;		        
	}
	else OLED_ShowStr(90,4," ",1); 
	OLED_Shownum2(96,4,OLED_Radius,1);	   //��ʾ�ٶ�	

}


void OLED_ShowPWM(int PWMX,int PWMY)
{
	if(PWMX<0)
	{
		OLED_ShowStr(50,4,"-",2);		//��ʾ����
		PWMX=-PWMX;	
	}
	else OLED_ShowStr(50,4," ",2); //�ڸǸ���
	OLED_Shownum1(58,4,PWMX,2);	    //��ʾ������
	
	if(PWMY<0)
	{
		OLED_ShowStr(50,6,"-",2);		
		PWMY=-PWMY;		        
	}
	else OLED_ShowStr(50,6," ",2); 
	OLED_Shownum1(58,6,PWMY,2);	    //��ʾ������
}
void Showfuhaoshu_4wei(int PWMX)
{
	if(PWMX<0)
	{
		OLED_ShowStr(50,4,"-",2);		//��ʾ����
		PWMX=-PWMX;	
	}
	else OLED_ShowStr(50,4," ",2); //�ڸǸ���
	OLED_Shownum1(58,4,PWMX,2);	    //��ʾ������
}


void OLED_Show_pitch_Angle(float pitch_)
{
	int Pitch;   //Roll
	Pitch=(int)(pitch_*10);
	//Roll=(int)(roll*10);				
	//�Ը��������������ǿ�����ʾ��lcd��

	if(Pitch<0)
	{
		OLED_ShowStr(0,2,"-",2);		//��ʾ����
		Pitch=-Pitch;	
	}
	else OLED_ShowStr(0,2," ",2); //�ڸǸ���
	OLED_Shownum2(8,2,Pitch,2);	    //��ʾ������
	
	
//if(Roll<0)
//	{
//		OLED_ShowStr(0,4,"-",2);		
//		Roll=-Roll;		        
//	}
//	else OLED_ShowStr(0,4," ",2); 
//	OLED_Shownum3(8,4,Roll,2);	    //��ʾ������
	
}


void OLED_ShowAngle(float pitch,float roll)
{
	int Pitch,Roll;   //Roll
	Pitch=(int)(pitch*10);
	Roll=(int)(roll*10);				
	//�Ը��������������ǿ�����ʾ��oled��

	if(Pitch<0)
	{
		OLED_ShowStr(0,2,"-",2);		//��ʾ����
		Pitch=-Pitch;	
	}
	else OLED_ShowStr(0,2," ",2); //�ڸǸ���
	OLED_Shownum2(8,2,Pitch,2);	    //��ʾ������
	
  if(Roll<0)
	{
		OLED_ShowStr(0,4,"-",2);		
		Roll=-Roll;		        
	}
	else OLED_ShowStr(0,4," ",2); 
	OLED_Shownum3(8,4,Roll,2);	    //��ʾ������	
}


void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	
	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+6,y,bai,TextSize);
		OLED_ShowSNum(x+12,y,shi,TextSize);
		OLED_ShowSNum(x+18,y,ge,TextSize);		
	}
		
	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+8,y,bai,TextSize);
		OLED_ShowSNum(x+16,y,shi,TextSize);
		OLED_ShowSNum(x+24,y,ge,TextSize);	
	}
}
void OLED_zhengshu_3wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,bai,TextSize);
		OLED_ShowSNum(x+6,y,shi,TextSize);
		OLED_ShowSNum(x+12,y,ge,TextSize);		
	}
		
	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,bai,TextSize);
		OLED_ShowSNum(x+8,y,shi,TextSize);
		OLED_ShowSNum(x+16,y,ge,TextSize);	
	}
}
void Showfuhaoshu_3wei(int PWMX)
{
	if(PWMX<0)
	{
		OLED_ShowStr(50,4,"-",2);		//��ʾ����
		PWMX=-PWMX;	
	}
	else OLED_ShowStr(50,4," ",2); //�ڸǸ���
	OLED_zhengshu_3wei(58,4,PWMX,2);	    //��ʾ������
}
void OLED_zhengshu_2wei(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi;
	ge=num%10;
	shi=(num%100)/10;
	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,shi,TextSize);
		OLED_ShowSNum(x+6,y,ge,TextSize);		
	}
		
	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,shi,TextSize);
		OLED_ShowSNum(x+8,y,ge,TextSize);	
	}
}
void Showfuhaoshu_2wei(int PWMX)
{
	if(PWMX<0)
	{
		OLED_ShowStr(50,4,"-",2);		//��ʾ����
		PWMX=-PWMX;	
	}
	else OLED_ShowStr(50,4," ",2); //�ڸǸ���
	OLED_zhengshu_2wei(58,4,PWMX,2);	    //��ʾ������
}


void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	
	if(TextSize==1)
	{
		if(bai!=0)
		{
		    OLED_ShowSNum(x,y,bai,TextSize);
		}else OLED_ShowStr(x,y," ",TextSize);
		    OLED_ShowSNum(x+6,y,shi,TextSize);
		    OLED_ShowStr(x+12,y,".",TextSize);
		    OLED_ShowSNum(x+18,y,ge,TextSize);	
	}
		
	if(TextSize==2)
	{
		if(bai!=0)
		{
		    OLED_ShowSNum(x,y,bai,TextSize);
		}
		    OLED_ShowStr(x+12,y,".",TextSize);
		    OLED_ShowSNum(x+18,y,ge,TextSize);	
	}
}


void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	
	if(TextSize==1)
	{
		if(qian!=0)
		{
		    OLED_ShowSNum(x,y,qian,TextSize);
			  OLED_ShowSNum(x+6,y,bai,TextSize);
		}
		if(bai!=0&&qian==0)
		{
			  OLED_ShowStr(x,y," ",TextSize);
		    OLED_ShowSNum(x+6,y,bai,TextSize);
		}
    if(bai==0&&qian==0)	
		{
        OLED_ShowStr(x,y," ",TextSize);
			  OLED_ShowStr(x+6,y," ",TextSize);
		}			
		    OLED_ShowSNum(x+12,y,shi,TextSize);
		    OLED_ShowStr(x+18,y,".",TextSize);
		    OLED_ShowSNum(x+24,y,ge,TextSize);	
	}
		
	if(TextSize==2)
	{
		if(qian!=0)
		{
		    OLED_ShowSNum(x,y,qian,TextSize);
			  OLED_ShowSNum(x+6,y,bai,TextSize);
		}
		if(bai!=0&&qian==0)
		{
			  OLED_ShowStr(x,y," ",TextSize);
		    OLED_ShowSNum(x+6,y,bai,TextSize);
		}	
    if(bai==0&&qian==0)	
		{
        OLED_ShowStr(x,y," ",TextSize);
			  OLED_ShowStr(x+6,y," ",TextSize);
		}		
		OLED_ShowSNum(x+16,y,shi,TextSize);
		OLED_ShowStr(x+24,y,".",TextSize);
		OLED_ShowSNum(x+32,y,ge,TextSize);
	}
}
void OLED_Shownum4(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian,wan;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	wan=(num%100000)/10000;
	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,wan,TextSize);
		OLED_ShowSNum(x+6,y,qian,TextSize);
		OLED_ShowSNum(x+12,y,bai,TextSize);
		OLED_ShowSNum(x+18,y,shi,TextSize);
		OLED_ShowStr(x+24,y,".",TextSize);
		OLED_ShowSNum(x+30,y,ge,TextSize);	
	}
		
	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,wan,TextSize);		
		OLED_ShowSNum(x+8,y,qian,TextSize);
		OLED_ShowSNum(x+16,y,bai,TextSize);
		OLED_ShowSNum(x+24,y,shi,TextSize);
		OLED_ShowStr(x+32,y,".",TextSize);
		OLED_ShowSNum(x+40,y,ge,TextSize);
	}
}



//���ܣ���һ������ʾ��λ����
//zsl 2021.7.21
void OLED_ShowNum55(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian,wan;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	wan=num/10000;
	
	if(TextSize==1)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+6,y,"    ",TextSize);
			}
			break;
			
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+6,y,ge,TextSize);	
        OLED_ShowStr(x+12,y,"   ",TextSize);				
			}
			break;

			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+6,y,shi,TextSize);
				OLED_ShowSNum(x+12,y,ge,TextSize);
        OLED_ShowStr(x+18,y,"  ",TextSize);				
			}
			break;

			case 4:
			{
				OLED_ShowSNum(x,y,qian,TextSize);
				OLED_ShowSNum(x+6,y,bai,TextSize);
				OLED_ShowSNum(x+12,y,shi,TextSize);
				OLED_ShowSNum(x+18,y,ge,TextSize);	
        OLED_ShowStr(x+24,y," ",TextSize);	
			}
			break;

			case 5:
			{
				OLED_ShowSNum(x,y,wan,TextSize);
				OLED_ShowSNum(x+6,y,qian,TextSize);
				OLED_ShowSNum(x+12,y,bai,TextSize);
				OLED_ShowSNum(x+18,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);		
				
			}
			break;		
		}
	}

	if(TextSize==2)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+8,y,"    ",TextSize);
			}
			break;
			
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+8,y,ge,TextSize);	
        OLED_ShowStr(x+16,y,"   ",TextSize);					
			}
			break;

			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+8,y,shi,TextSize);
				OLED_ShowSNum(x+16,y,ge,TextSize);
        OLED_ShowStr(x+24,y,"  ",TextSize);
			}
			break;

			case 4:
			{
				OLED_ShowSNum(x,y,qian,TextSize);
				OLED_ShowSNum(x+8,y,bai,TextSize);
				OLED_ShowSNum(x+16,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);
        OLED_ShowStr(x+32,y," ",TextSize);
			}
			break;

			case 5:
			{
				OLED_ShowSNum(x,y,wan,TextSize);
				OLED_ShowSNum(x+8,y,qian,TextSize);
				OLED_ShowSNum(x+16,y,bai,TextSize);
				OLED_ShowSNum(x+24,y,shi,TextSize);
				OLED_ShowSNum(x+32,y,ge,TextSize);	
			}
			break;		
		}
	}
}
//���ܣ���һ������ʾ��λ����
//zsl 2021.7.21
void OLED_ShowNum44(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	
	if(TextSize==1)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+6,y,"   ",TextSize);
			}
			break;			
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+6,y,ge,TextSize);	
        OLED_ShowStr(x+12,y,"  ",TextSize);				
			}
			break;
			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+6,y,shi,TextSize);
				OLED_ShowSNum(x+12,y,ge,TextSize);
        OLED_ShowStr(x+18,y," ",TextSize);				
			}
			break;
			case 4:
			{
				OLED_ShowSNum(x,y,qian,TextSize);
				OLED_ShowSNum(x+6,y,bai,TextSize);
				OLED_ShowSNum(x+12,y,shi,TextSize);
				OLED_ShowSNum(x+18,y,ge,TextSize);		
			}
			break;		
		}
	}

	if(TextSize==2)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+8,y,"   ",TextSize);
			}
			break;		
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+8,y,ge,TextSize);	
        OLED_ShowStr(x+16,y,"  ",TextSize);					
			}
			break;
			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+8,y,shi,TextSize);
				OLED_ShowSNum(x+16,y,ge,TextSize);
        OLED_ShowStr(x+24,y," ",TextSize);
			}
			break;
			case 4:
			{
				OLED_ShowSNum(x,y,qian,TextSize);
				OLED_ShowSNum(x+8,y,bai,TextSize);
				OLED_ShowSNum(x+16,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);
			}
			break;	
		}
	}
}
//���ܣ���һ������ʾ��λ����
//zsl 2021.7.21
void OLED_ShowNum33(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	
	if(TextSize==1)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+6,y,"  ",TextSize);
			}
			break;			
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+6,y,ge,TextSize);	
        OLED_ShowStr(x+12,y," ",TextSize);				
			}
			break;
			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+6,y,shi,TextSize);
				OLED_ShowSNum(x+12,y,ge,TextSize);				
			}
			break;		
		}
	}

	if(TextSize==2)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
        OLED_ShowStr(x+8,y,"  ",TextSize);
			}
			break;		
			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+8,y,ge,TextSize);	
        OLED_ShowStr(x+16,y," ",TextSize);					
			}
			break;
			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+8,y,shi,TextSize);
				OLED_ShowSNum(x+16,y,ge,TextSize);
			}
			break;
		}
	}
}
void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	unsigned char ch[2];
	ch[0]=48+num;
	ch[1]= '\0';
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}			
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_Data(F6x8[c][i]);
				
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i]);			
				OLED_SetPos(x,y+1);		
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i+8]);
				
				x += 8;
				j++;
			}
		}break;
	}
}

//���ܣ�������λ����������λ��
//wgn 2021.4.29
int Num_Digit(int num)
{
    if(num>=0 && num<100000)
    {
        if(num<10) return 1;
        if(num<100) return 2;
        if(num<1000) return 3;
        if(num<10000) return 4;
        if(num<1000000) return 5;    
    }
    return 0;
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); ch[] -- Ҫ��ʾ���ַ���; TextSize -- �ַ���С(1:6*8 ; 2:8*16)
// Description    : ��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_Data(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
// Description    : ��ʾcodetab.h�еĺ���,16*16����
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
}



//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- ��ʼ������(x0:0~127, y0:0~7); x1,y1 -- ���Խ���(������)������(x1:1~128,y1:1~8)
// Description    : ��ʾBMPλͼ
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_Data(BMP[j++]);
		}
	}
}


void OLED_Clear(void)
{
	OLED_Fill(0);
}
	
	
void OLED_SetPos(unsigned char x, unsigned char y) //������ʼ������
{ 
	OLED_Command(0xb0+y);
	OLED_Command(((x&0xf0)>>4)|0x10);
	OLED_Command((x&0x0f)|0x01);
}


void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_Command(0xb0+m);		//page0-page1
		OLED_Command(0x00);		//low column start address
		OLED_Command(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_Data(fill_Data);
			}
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
void OLED_ON(void)
{
	OLED_Command(0X8D);  //���õ�ɱ�
	OLED_Command(0X14);  //������ɱ�
	OLED_Command(0XAF);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	OLED_Command(0X8D);  //���õ�ɱ�
	OLED_Command(0X10);  //�رյ�ɱ�
	OLED_Command(0XAE);  //OLED����
}


void OLED_Init(void)
{
	delay_init();
	IIC_Init(); //GPIO��ʼ��
	
	//OLED�������
	delay_ms(100);
	
	OLED_Command(0xAE); //display off
	OLED_Command(0x20);	//Set Memory Addressing Mode	
	OLED_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_Command(0xc0);	//Set COM Output Scan Direction              (c8����c0��)
	OLED_Command(0xa0); //--set segment re-map 0 to 127              (a1����a0��)
	OLED_Command(0x00); //---set low column address
	OLED_Command(0x10); //---set high column address
	OLED_Command(0x40); //--set start line address
	OLED_Command(0x81); //--set contrast control register
	OLED_Command(0xff); //���ȵ��� 0x00~0xff
	OLED_Command(0xa6); //--set normal display
	OLED_Command(0xa8); //--set multiplex ratio(1 to 64)
	OLED_Command(0x3F); //
	OLED_Command(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_Command(0xd3); //-set display offset
	OLED_Command(0x00); //-not offset
	OLED_Command(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_Command(0xf0); //--set divide ratio
	OLED_Command(0xd9); //--set pre-charge period
	OLED_Command(0x22); //
	OLED_Command(0xda); //--set com pins hardware configuration
	OLED_Command(0x12);
	OLED_Command(0xdb); //--set vcomh
	OLED_Command(0x20); //0x20,0.77xVcc
	OLED_Command(0x8d); //--set DC-DC enable
	OLED_Command(0x14); //
	OLED_Command(0xaf); //--turn on oled panel
	OLED_WR_Byte(0xC8,0);//��ת��ʾ
	OLED_WR_Byte(0xA1,0);
	OLED_Fill(0x00);//������ȫ��0��䣩
}


int OLED_Command(unsigned char Command)
{
   IIC_Start();
   IIC_Send_Byte(0x78);         //Slave address,SA0=0
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Send_Byte(0x00);	       //write command
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Send_Byte(Command);
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Stop();
	 return 0;
}


int OLED_Data(unsigned char Data)
{
   IIC_Start();
   IIC_Send_Byte(0x78);			//D/C#=0; R/W#=0
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Send_Byte(0x40);			//write data
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Send_Byte(Data);
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();		 
		 return 1;		
	 }
   IIC_Stop();
	 return 0;
}
