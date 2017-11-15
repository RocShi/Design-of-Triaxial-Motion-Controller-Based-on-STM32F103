/****************************************Copyright (c)****************************************************
** 
**                                           ʯ��
**
**                                      QQ��1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			SP_GPIO_Init.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		GPIO��ʼ��Դ�ļ�
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //ʱ�����ú���
#include "stm32f10x_gpio.h"
#include "SP_GPIO_Init.h"
void SP_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;                  //����GPIO��ʼ���ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //����GPIOA�˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //����GPIOB�˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //����GPIOC�˿�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //����GPIOD�˿�

	//�ͷ�JTAG��PA15��PB3��PB4������GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //��������ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��ֹJTAG	
	
	//PB0,PB1,PB2,PB3,PB4,PB5,PB6����Ϊ��©���;����3*4���������4���긴λ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2Mʱ���ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);
												  
	//PB7,PB8,PB9����Ϊ��������;����X0��Y0��Z+����ԭ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	       //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PC6����Ϊ��������;������λ��ͣ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	       //��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//PC9,PC3,PC8,PC4,PC7,PC5����Ϊ�������;�ֱ�ΪX��Y��Z���PUL��DIR
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2Mʱ���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//PA0����Ϊ�������;���ڷ�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2Mʱ���ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
