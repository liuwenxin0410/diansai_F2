#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"
#include "oled.h"

/*菜单结构定义*/
struct MenuItem
{
	 short MenuCount;                  //结构体数组的元素个数
	 u8 *DisplayString;                //当前OLED显示的信息
	 int MenuClass;                    //结构体第几层的第几个项目
	 void(*Subs)();                    //执行的函数的指针. 
	 struct MenuItem *ChildrenMenus;   //指向子节点的指针
	 struct MenuItem *ParentMenus;     //指向父节点的指针 
};

void display(struct MenuItem * MenuPoint,short selectItem);


#endif



