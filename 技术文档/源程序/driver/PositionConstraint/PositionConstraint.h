#ifndef _PositionConstraint_H_
#define _PositionConstraint_H_

#define Z_P  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) //��Z+�����жϴ���λ״̬
#define INT0 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) //��INT0�жϴ���λ״̬
#define X0   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) //��X��ԭ��״̬
#define Y0   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) //��Y��ԭ��״̬

void SP_ExtiInit(void);

#endif 
