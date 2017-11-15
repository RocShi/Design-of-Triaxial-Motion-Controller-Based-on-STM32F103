/****************************************Copyright (c)****************************************************
** 
**                                           石鹏
**
**                                      QQ：1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			PositionConstraint.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		限位检测程序源文件，包括中断初始化函数与中断服务程序
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"      //时钟配置函数
#include "stm32f10x.h"
#include "misc.h"               //NVIC中断配置需要用到
#include "stm32f10x_gpio.h"	    //GPIO库函数头文件
#include "stm32f10x_exti.h"	    //外部中断库函数头文件
#include "stm32f10x_pwr.h"	    
#include "PositionConstraint.h" //限位急停与复位
#include "SP_GPIO_Init.h"       //GPIO初始化 
#include "Motor.h"		  	    //电机控制
#include "Delay.h"       	    //ms,us延时


void SP_ExtiInit(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//连接IO口到中断控制器
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  //PB9,Z轴正方向超程触发中断
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);  //PC6,X、Y、Z轴其它方向超程触发中断
	
	//设置中断为下降沿触发
	EXTI_InitStructure.EXTI_Line = EXTI_Line6|EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//外部中断NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		  //选择中断号
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //选择中断主优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;        //选择中断从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //选择使能中断
	NVIC_Init(&NVIC_InitStructure);                           //用以上参数，配置中断NVIC寄存器
}

void EXTI9_5_IRQHandler(void)
{
	BuzzerOn;
	X_Port_PUL_H;   //X轴急停
	Y_Port_PUL_H;   //Y轴急停
	Z_Port_PUL_H;   //Z轴急停
	Delay_Init(72);	//延时初始化
	while(Z_P==1)  Z_MotorRun(500,1,1);
	EXTI_ClearITPendingBit(EXTI_Line9);    //清除Z+超程中断标志
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
	EXTI_ClearITPendingBit(EXTI_Line6);      //清除其它方向超程中断标志
	while(1);  //系统复位等待
}
