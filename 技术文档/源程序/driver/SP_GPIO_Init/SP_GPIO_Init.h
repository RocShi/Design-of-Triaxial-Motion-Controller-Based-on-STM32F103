#ifndef _GPIO_H_
#define _GPIO_H_

#define PB0_H   GPIO_SetBits(GPIOB, GPIO_Pin_0)	           //PB0输出高电平
#define PB0_L   GPIO_ResetBits(GPIOB, GPIO_Pin_0)          //PB0输出低电平
#define PB1_H   GPIO_SetBits(GPIOB, GPIO_Pin_1)	           //PB1输出高电平
#define PB1_L   GPIO_ResetBits(GPIOB, GPIO_Pin_1)          //PB1输出低电平
#define PB2_H   GPIO_SetBits(GPIOB, GPIO_Pin_2)	           //PB2输出高电平
#define PB2_L   GPIO_ResetBits(GPIOB, GPIO_Pin_2)          //PB2输出低电平
#define PB3_H   GPIO_SetBits(GPIOB, GPIO_Pin_3)	           //PB3输出高电平
#define PB3_L   GPIO_ResetBits(GPIOB, GPIO_Pin_3)          //PB3输出低电平
#define PB4_H   GPIO_SetBits(GPIOB, GPIO_Pin_4)	           //PB4输出高电平
#define PB4_L   GPIO_ResetBits(GPIOB, GPIO_Pin_4)          //PB4输出低电平
#define PB5_H   GPIO_SetBits(GPIOB, GPIO_Pin_5)	           //PB5输出高电平
#define PB5_L   GPIO_ResetBits(GPIOB, GPIO_Pin_5)          //PB5输出低电平
#define PB6_H   GPIO_SetBits(GPIOB, GPIO_Pin_6)	           //PB6输出高电平
#define PB6_L   GPIO_ResetBits(GPIOB, GPIO_Pin_6)          //PB6输出低电平

#define BuzzerOn  GPIO_SetBits(GPIOA, GPIO_Pin_0)	       //PA0输出高电平
#define BuzzerOff GPIO_ResetBits(GPIOA, GPIO_Pin_0)	       //PA0输出高电平

#define KeyCheck3 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) //按键检测,PB3,列0
#define KeyCheck2 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) //按键检测,PB2,列1
#define KeyCheck1 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) //按键检测,PB1,列2
#define KeyCheck0 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) //按键检测,PB0,列3  
#define KeyCheck4 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) //按键检测,PB4,行0
#define KeyCheck5 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) //按键检测,PB5,行1
#define KeyCheck6 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) //按键检测,PB6,行2

#define INT0Check GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) //按键检测,PC6

void SP_GPIO_Init(void); 

#endif 
