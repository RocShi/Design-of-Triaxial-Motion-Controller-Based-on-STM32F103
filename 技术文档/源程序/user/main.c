/****************************************Copyright (c)****************************************************
** 
**                                           石鹏
**
**                                      QQ：1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			main.c
** modified Date:  		2015-5-22
** Last Version:		V1.5  (2015.5.18-2015.5.22)
** Descriptions:		主文件
*********************************************************************************************************/
#include "stm32f10x_rcc.h"      //时钟配置函数
#include "SP_GPIO_Init.h"	    //GPIO初始化
#include "Motor.h"       	    //电机控制
#include "Delay.h"       	    //ms,us延时
#include "KeyBoard.h"           //矩阵键盘
#include "PositionConstraint.h" //限位急停与复位
#include "Interpolation.h" 		//插补

int main(void)
{
	SP_GPIO_Init();    	        //GPIO初始化
	Delay_Init(72);	            //延时初始化
	SP_ExtiInit();              //外部中断初始化

  	while(1)                       
	{
		 switch(KeyBoard()) 	//选择插补起始点
		 {
		 	case 1:  X_MotorRun(500,1,100); continue; 
			case 2:  X_MotorRun(500,0,100); continue;  
			case 3:  Y_MotorRun(500,1,100); continue;  
			case 4:  Y_MotorRun(500,0,100); continue; 			   
			case 5:  Z_MotorRun(500,1,100); continue; 
			case 6:  Z_MotorRun(500,0,100); continue; 
			default: break;
		 }
		 Delay_ms(1000);
		 switch(KeyBoard())	  //选择插补模式
		 {
		 	case 1:  Line(); break;	 //直线插补 
			case 2:  Arc();  break;  //圆弧插补 
			default: continue;
		 }
		 Delay_ms(1000);
	}  
}
