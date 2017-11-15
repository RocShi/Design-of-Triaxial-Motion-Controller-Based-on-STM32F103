#ifndef _PositionConstraint_H_
#define _PositionConstraint_H_

#define Z_P  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) //读Z+超程中断触发位状态
#define INT0 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) //读INT0中断触发位状态
#define X0   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) //读X轴原点状态
#define Y0   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) //读Y轴原点状态

void SP_ExtiInit(void);

#endif 
