#ifndef _MOTOR_H_
#define _MOTOR_H_

#define X_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_9)	   //PC9输出高电平，X轴脉冲高
#define X_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_9)   //PC9输出低电平，X轴脉冲低
#define X_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_3)	   //PC3输出低电平，X轴方向负
#define X_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_3)   //PC3输出高电平，X轴方向正

#define Y_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_8)	   //PC8输出高电平，Y轴脉冲高
#define Y_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_8)   //PC8输出低电平，Y轴脉冲低
#define Y_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_4)	   //PC4输出低电平，Y轴方向负
#define Y_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_4)   //PC4输出高电平，Y轴方向正

#define Z_Port_PUL_H   GPIO_SetBits(GPIOC, GPIO_Pin_7)	   //PC9输出高电平，Z轴脉冲高
#define Z_Port_PUL_L   GPIO_ResetBits(GPIOC, GPIO_Pin_7)   //PC9输出低电平，Z轴脉冲低
#define Z_Port_DIR_N   GPIO_SetBits(GPIOC, GPIO_Pin_5)	   //PC3输出低电平，Z轴方向负
#define Z_Port_DIR_P   GPIO_ResetBits(GPIOC, GPIO_Pin_5)   //PC3输出高电平，Z轴方向正

void X_MotorRun(int32u Speed,int32u Direction,int32u StepNumber);
void Y_MotorRun(int32u Speed,int32u Direction,int32u StepNumber);
void Z_MotorRun(int32u Speed,int32u Direction,int32u StepNumber); 

#endif 
