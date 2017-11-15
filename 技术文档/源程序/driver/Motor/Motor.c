/****************************************Copyright (c)****************************************************
** 
**                                           ʯ��
**
**                                      QQ��1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			Motor.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		������ƺ���Դ�ļ�
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //ʱ�����ú���
#include "stm32f10x_gpio.h"
#include "Motor.h"
#include "Delay.h"       	//ms,us��ʱ

void X_MotorRun(int32u Speed,int32u Direction,int32u StepNumber)
{
	int32u n,t;	//����n����ʱʱ��t(us)
	t=(1000000/Speed)*0.5;
	Delay_Init(72);	//��ʱ��ʼ��

	switch(Direction)
	{
		case 0: X_Port_DIR_N; break;
		case 1: X_Port_DIR_P; break;
		default:break;
	}
	for(n=0;n<StepNumber;n++)
	{
		X_Port_PUL_H;
		Delay_us(t);	
		X_Port_PUL_L;																					   
 		Delay_us(t);
	}	
}

void Y_MotorRun(int32u Speed,int32u Direction,int32u StepNumber)
{
	int32u n,t;	//����n����ʱʱ��t(us)
	t=(1000000/Speed)*0.5;
	Delay_Init(72);	//��ʱ��ʼ��

	switch(Direction)
	{
		case 0: Y_Port_DIR_N; break;
		case 1: Y_Port_DIR_P; break;
		default:break;
	}
	for(n=0;n<StepNumber;n++)
	{
		Y_Port_PUL_H;
		Delay_us(t);	
		Y_Port_PUL_L;																					   
 		Delay_us(t);
	}	
}

void Z_MotorRun(int32u Speed,int32u Direction,int32u StepNumber)
{
	int32u n,t;	//����n����ʱʱ��t(us)
	t=(1000000/Speed)*0.5;
	Delay_Init(72);	//��ʱ��ʼ��

	switch(Direction)
	{
		case 0: Z_Port_DIR_N; break;
		case 1: Z_Port_DIR_P; break;
		default:break;
	}
	for(n=0;n<StepNumber;n++)
	{
		Z_Port_PUL_H;
		Delay_us(t);	
		Z_Port_PUL_L;																					   
 		Delay_us(t);
	}	
}
