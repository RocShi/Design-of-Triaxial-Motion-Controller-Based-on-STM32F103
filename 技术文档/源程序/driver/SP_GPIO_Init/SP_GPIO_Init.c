/****************************************Copyright (c)****************************************************
** 
**                                           石鹏
**
**                                      QQ：1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			SP_GPIO_Init.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		GPIO初始化源文件
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //时钟配置函数
#include "stm32f10x_gpio.h"
#include "SP_GPIO_Init.h"
void SP_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;                  //定义GPIO初始化结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开启GPIOA端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //开启GPIOB端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //开启GPIOC端口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //开启GPIOD端口

	//释放JTAG的PA15、PB3、PB4，用于GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //开启复用时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//禁止JTAG	
	
	//PB0,PB1,PB2,PB3,PB4,PB5,PB6配置为开漏输出;用于3*4矩阵键盘与4坐标复位按键
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	   //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2M时钟速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);
												  
	//PB7,PB8,PB9配置为上拉输入;用于X0、Y0、Z+坐标原点检测
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	       //上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PC6配置为上拉输入;用于限位急停
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	       //上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//PC9,PC3,PC8,PC4,PC7,PC5配置为推挽输出;分别为X、Y、Z轴的PUL和DIR
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2M时钟速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//PA0配置为推挽输出;用于蜂鸣器
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	   //2M时钟速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
