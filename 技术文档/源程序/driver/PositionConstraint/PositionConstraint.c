/****************************************Copyright (c)****************************************************
** 
**                                           ʯ��
**
**                                      QQ��1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			PositionConstraint.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		��λ������Դ�ļ��������жϳ�ʼ���������жϷ������
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"      //ʱ�����ú���
#include "stm32f10x.h"
#include "misc.h"               //NVIC�ж�������Ҫ�õ�
#include "stm32f10x_gpio.h"	    //GPIO�⺯��ͷ�ļ�
#include "stm32f10x_exti.h"	    //�ⲿ�жϿ⺯��ͷ�ļ�
#include "stm32f10x_pwr.h"	    
#include "PositionConstraint.h" //��λ��ͣ�븴λ
#include "SP_GPIO_Init.h"       //GPIO��ʼ�� 
#include "Motor.h"		  	    //�������
#include "Delay.h"       	    //ms,us��ʱ


void SP_ExtiInit(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//����IO�ڵ��жϿ�����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  //PB9,Z�������򳬳̴����ж�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);  //PC6,X��Y��Z���������򳬳̴����ж�
	
	//�����ж�Ϊ�½��ش���
	EXTI_InitStructure.EXTI_Line = EXTI_Line6|EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//�ⲿ�ж�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		  //ѡ���жϺ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //ѡ���ж������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;        //ѡ���жϴ����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ѡ��ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);                           //�����ϲ����������ж�NVIC�Ĵ���
}

void EXTI9_5_IRQHandler(void)
{
	BuzzerOn;
	X_Port_PUL_H;   //X�ἱͣ
	Y_Port_PUL_H;   //Y�ἱͣ
	Z_Port_PUL_H;   //Z�ἱͣ
	Delay_Init(72);	//��ʱ��ʼ��
	while(Z_P==1)  Z_MotorRun(500,1,1);
	EXTI_ClearITPendingBit(EXTI_Line9);    //���Z+�����жϱ�־
	while(X0!=0)
	{
		PB3_H; PB2_H; PB1_H; PB0_H;
		if(KeyCheck3==0)
			X_MotorRun(500,1,1);
		if(KeyCheck2==0)
			X_MotorRun(500,0,1);
	}
	while(Y0!=0)
	{
		PB3_H; PB2_H; PB1_H; PB0_H;
		if(KeyCheck1==0)
			Y_MotorRun(500,1,1);
		if(KeyCheck0==0)
			Y_MotorRun(500,0,1);
	}
	BuzzerOff;
	EXTI_ClearITPendingBit(EXTI_Line6);      //����������򳬳��жϱ�־
	while(1);  //ϵͳ��λ�ȴ�
}
