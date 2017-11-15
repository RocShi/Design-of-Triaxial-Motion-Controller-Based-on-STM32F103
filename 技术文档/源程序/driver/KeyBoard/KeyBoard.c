/****************************************Copyright (c)****************************************************
** 
**                                           石鹏
**
**                                      QQ：1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			KeyBoard.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		矩阵键盘程序源文件
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //时钟配置函数
#include "stm32f10x_gpio.h"
#include "Delay.h"       	//ms,us延时
#include "SP_GPIO_Init.h"   //GPIO初始化
#include "KeyBoard.h"       //矩阵键盘   

int32u KeyBoard(void)
{
	int32u KeyValue[3][4]=
	{	
	    {1,2,3,4},
		{5,6,7,8},
		{9,0,11,12}
	},t=20,x,y;
	Delay_Init(72);	//延时初始化
	while(t==20)	//如果无按键按下，则一直循环,等待按键    
	{
		PB3_H;  PB2_H;  PB1_H;  PB0_H;  PB4_L;  PB5_L;  PB6_L;
		if((KeyCheck3&&KeyCheck2&&KeyCheck1&&KeyCheck0)==0)	//有按键按下,则；注意不要丢内括号，由运算符优先级决定
		{	
			Delay_ms(10);   //消抖
			if(KeyCheck3==0) y=0;
			if(KeyCheck2==0) y=1;
			if(KeyCheck1==0) y=2;
			if(KeyCheck0==0) y=3;								
			PB3_L;  PB2_L;  PB1_L;  PB0_L;  PB4_H;  PB5_H;  PB6_H;
			if(KeyCheck4==0) x=0;
			if(KeyCheck5==0) x=1;
			if(KeyCheck6==0) x=2;
			t=KeyValue[x][y];
		}
		else t=20; 	//无按键按下
	}
	return t;
}
