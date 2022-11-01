#include "menu.h"

/*结构体声明*/ 
struct MenuItem MainMenu[2] =        //主界面
{
		{ 2,"Basic part",1,NULL,NULL,NULL },
		{ 2,"Advanced part",2,NULL,NULL,NULL },		
};

struct MenuItem Setmenu1[4]=         //一级菜单界面1
{
		{ 4,"B_function 1",11,NULL,NULL,MainMenu },
		{ 4,"B_function 2",12,NULL,NULL,MainMenu },
		{ 4,"B_function 3",13,NULL,NULL,MainMenu },
		{ 4,"B_function 4",14,NULL,NULL,MainMenu },		
};

struct MenuItem Setmenu2[4]=         //一级菜单界面3
{
		{ 4,"A_function 1",21,NULL,NULL,MainMenu },
		{ 4,"A_function 2",22,NULL,NULL,MainMenu },
		{ 4,"A_function 3",23,NULL,NULL,MainMenu },
		{ 4,"A_function 4",24,NULL,NULL,MainMenu },		
};
	



/*显示函数*/
void display(struct MenuItem * MenuPoint,short selectItem)              
{	
			int i;
			int j;
			u16 x=12;
			u16 y=0;
	
			for ( i = 0; i < (selectItem); i++)   //整个页面
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




















