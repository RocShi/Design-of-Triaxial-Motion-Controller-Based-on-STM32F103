/****************************************Copyright (c)****************************************************
** 
**                                           ʯ��
**
**                                      QQ��1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			main.c
** modified Date:  		2015-5-22
** Last Version:		V1.5  (2015.5.18-2015.5.22)
** Descriptions:		���ļ�
*********************************************************************************************************/
#include "stm32f10x_rcc.h"      //ʱ�����ú���
#include "SP_GPIO_Init.h"	    //GPIO��ʼ��
#include "Motor.h"       	    //�������
#include "Delay.h"       	    //ms,us��ʱ
#include "KeyBoard.h"           //�������
#include "PositionConstraint.h" //��λ��ͣ�븴λ
#include "Interpolation.h" 		//�岹

int main(void)
{
	SP_GPIO_Init();    	        //GPIO��ʼ��
	Delay_Init(72);	            //��ʱ��ʼ��
	SP_ExtiInit();              //�ⲿ�жϳ�ʼ��

  	while(1)                       
	{
		 switch(KeyBoard()) 	//ѡ��岹��ʼ��
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
		 switch(KeyBoard())	  //ѡ��岹ģʽ
		 {
		 	case 1:  Line(); break;	 //ֱ�߲岹 
			case 2:  Arc();  break;  //Բ���岹 
			default: continue;
		 }
		 Delay_ms(1000);
	}  
}
