#ifndef _GPIO_H_
#define _GPIO_H_

#define PB0_H   GPIO_SetBits(GPIOB, GPIO_Pin_0)	           //PB0����ߵ�ƽ
#define PB0_L   GPIO_ResetBits(GPIOB, GPIO_Pin_0)          //PB0����͵�ƽ
#define PB1_H   GPIO_SetBits(GPIOB, GPIO_Pin_1)	           //PB1����ߵ�ƽ
#define PB1_L   GPIO_ResetBits(GPIOB, GPIO_Pin_1)          //PB1����͵�ƽ
#define PB2_H   GPIO_SetBits(GPIOB, GPIO_Pin_2)	           //PB2����ߵ�ƽ
#define PB2_L   GPIO_ResetBits(GPIOB, GPIO_Pin_2)          //PB2����͵�ƽ
#define PB3_H   GPIO_SetBits(GPIOB, GPIO_Pin_3)	           //PB3����ߵ�ƽ
#define PB3_L   GPIO_ResetBits(GPIOB, GPIO_Pin_3)          //PB3����͵�ƽ
#define PB4_H   GPIO_SetBits(GPIOB, GPIO_Pin_4)	           //PB4����ߵ�ƽ
#define PB4_L   GPIO_ResetBits(GPIOB, GPIO_Pin_4)          //PB4����͵�ƽ
#define PB5_H   GPIO_SetBits(GPIOB, GPIO_Pin_5)	           //PB5����ߵ�ƽ
#define PB5_L   GPIO_ResetBits(GPIOB, GPIO_Pin_5)          //PB5����͵�ƽ
#define PB6_H   GPIO_SetBits(GPIOB, GPIO_Pin_6)	           //PB6����ߵ�ƽ
#define PB6_L   GPIO_ResetBits(GPIOB, GPIO_Pin_6)          //PB6����͵�ƽ

#define BuzzerOn  GPIO_SetBits(GPIOA, GPIO_Pin_0)	       //PA0����ߵ�ƽ
#define BuzzerOff GPIO_ResetBits(GPIOA, GPIO_Pin_0)	       //PA0����ߵ�ƽ

#define KeyCheck3 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) //�������,PB3,��0
#define KeyCheck2 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) //�������,PB2,��1
#define KeyCheck1 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) //�������,PB1,��2
#define KeyCheck0 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) //�������,PB0,��3  
#define KeyCheck4 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) //�������,PB4,��0
#define KeyCheck5 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) //�������,PB5,��1
#define KeyCheck6 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) //�������,PB6,��2

#define INT0Check GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) //�������,PC6

void SP_GPIO_Init(void); 

#endif 
