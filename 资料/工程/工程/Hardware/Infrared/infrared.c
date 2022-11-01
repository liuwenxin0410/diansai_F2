/**
  *************************************************************************************************************************
  * @file    infrared.c
  * @author  amkl
  * @version V1.0
  * @date    2022-09-22
  * @brief   ���⴫����ģ��.c�ļ�����
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "infrared.h"
/* ���� -----------------------------------------------------------------------------------------------------------------*/

/**
 * ������:Infrafred_GPIO_Init
 * ����:���⴫������Ӧgpio����
 * ����:��
 * ���:��
 */
void Infrafred_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruture);
}

/**
 * ������:LoadOrNot
 * ����:���ҩƷװ��
 * ����:��
 * ���:0-�ȴ� 1-װҩ 2-ȡҩ
 */
uint8_t LoadOrNot(void)
{
  static uint8_t load_flag;
	
	if(DRUG_Testing==1)//װ��ҩƷ���
	{
	 load_flag=1;
		return 1;
	}
	else if(DRUG_Testing==0)
	{
	  if(load_flag==1)//ȡҩ���
		{
		  return 2;
		}
	}
  return 0;
}


/*****************************************************END OF FILE*********************************************************/	
