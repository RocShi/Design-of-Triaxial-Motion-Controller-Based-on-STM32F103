#ifndef _MOTOR_H_
#define _MOTOR_H_

#define X_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_9)	   //PC9����ߵ�ƽ��X�������
#define X_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_9)   //PC9����͵�ƽ��X�������
#define X_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_3)	   //PC3����͵�ƽ��X�᷽��
#define X_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_3)   //PC3����ߵ�ƽ��X�᷽����

#define Y_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_8)	   //PC8����ߵ�ƽ��Y�������
#define Y_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_8)   //PC8����͵�ƽ��Y�������
#define Y_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_4)	   //PC4����͵�ƽ��Y�᷽��
#define Y_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_4)   //PC4����ߵ�ƽ��Y�᷽����

#define Z_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_7)	   //PC9����ߵ�ƽ��Z�������
#define Z_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_7)   //PC9����͵�ƽ��Z�������
#define Z_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_5)	   //PC3����͵�ƽ��Z�᷽��
#define Z_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_5)   //PC3����ߵ�ƽ��Z�᷽����

void X_MotorRun(int32u Speed,int32u Direction,int32u StepNumber);
void Y_MotorRun(int32u Speed,int32u Direction,int32u StepNumber);
void Z_MotorRun(int32u Speed,int32u Direction,int32u StepNumber); 

#endif 
