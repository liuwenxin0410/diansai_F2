#include "menu.h"

/*�ṹ������*/ 
struct MenuItem MainMenu[2] =        //������
{
		{ 2,"Basic part",1,NULL,NULL,NULL },
		{ 2,"Advanced part",2,NULL,NULL,NULL },		
};

struct MenuItem Setmenu1[4]=         //һ���˵�����1
{
		{ 4,"B_function 1",11,NULL,NULL,MainMenu },
		{ 4,"B_function 2",12,NULL,NULL,MainMenu },
		{ 4,"B_function 3",13,NULL,NULL,MainMenu },
		{ 4,"B_function 4",14,NULL,NULL,MainMenu },		
};

struct MenuItem Setmenu2[4]=         //һ���˵�����3
{
		{ 4,"A_function 1",21,NULL,NULL,MainMenu },
		{ 4,"A_function 2",22,NULL,NULL,MainMenu },
		{ 4,"A_function 3",23,NULL,NULL,MainMenu },
		{ 4,"A_function 4",24,NULL,NULL,MainMenu },		
};
	



/*��ʾ����*/
void display(struct MenuItem * MenuPoint,short selectItem)              
{	
			int i;
			int j;
			u16 x=12;
			u16 y=0;
	
			for ( i = 0; i < (selectItem); i++)   //����ҳ��
			{
					OLED_ShowStr(x,y,MenuPoint[i].DisplayString,2);
					y+=2;
			}
			//OLED_ShowStr(4,y-2,"*",2);
      OLED_ShowStr(4,0," ",2);
      OLED_ShowStr(4,2," ",2);
      OLED_ShowStr(4,4," ",2);
      OLED_ShowStr(4,6," ",2);
			OLED_ShowStr(4,y-2,"*",2);			
			for ( j= selectItem; j < MenuPoint->MenuCount; j++)
			{
			   OLED_ShowStr(x,y,MenuPoint[j].DisplayString,2);
			   y+=2;
			}
}




















