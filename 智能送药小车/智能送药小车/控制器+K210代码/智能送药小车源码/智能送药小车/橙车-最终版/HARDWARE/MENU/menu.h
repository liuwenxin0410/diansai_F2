#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"
#include "oled.h"

/*�˵��ṹ����*/
struct MenuItem
{
	 short MenuCount;                  //�ṹ�������Ԫ�ظ���
	 u8 *DisplayString;                //��ǰOLED��ʾ����Ϣ
	 int MenuClass;                    //�ṹ��ڼ���ĵڼ�����Ŀ
	 void(*Subs)();                    //ִ�еĺ�����ָ��. 
	 struct MenuItem *ChildrenMenus;   //ָ���ӽڵ��ָ��
	 struct MenuItem *ParentMenus;     //ָ�򸸽ڵ��ָ�� 
};

void display(struct MenuItem * MenuPoint,short selectItem);


#endif



