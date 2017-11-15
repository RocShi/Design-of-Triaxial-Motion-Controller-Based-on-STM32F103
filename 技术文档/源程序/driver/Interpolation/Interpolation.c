/****************************************Copyright (c)****************************************************
** 
**                                           ʯ��
**
**                                      QQ��1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			Interpolation.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		�岹����Դ�ļ�
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //ʱ�����ú���
#include "stm32f10x_gpio.h"
#include "Interpolation.h"
#include "SP_GPIO_Init.h"   //GPIO��ʼ��
#include "Motor.h"
#include "Delay.h"       	//ms,us��ʱ
#include "KeyBoard.h"       //�������

//ֱ�߲岹����,�ɼ��������յ�x��y���꣬��������ֹͣ�Ӽ���
void Line(void)	//�յ�����x,y;��λmm
{
	int32u x=0,y=0,Xe,Ye,N;	//�岹�յ�����x,y;X��Y����Բ���Xe��Ye,�ܲ���N
	int32u Dx,Dy;	//����������
	int32s i,F=0;	//ƫ��F��F����Ϊһ��ʼ��������޷��ű������������ƫ���б���ȷ!!

	while(1)	//x��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dx=0; break;
			case 12: Dx=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x=x*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//��ֹ����������
		BuzzerOff;
		break;
	}

	while(1)	//y��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dy=0; break;
			case 12: Dy=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y=y*10+KeyBoard();
			Delay_ms(1000);	//��ֹ����������
			PB0_H;			
		}
		BuzzerOn;
		Delay_ms(1000);
		BuzzerOff;
		break;
	}

	Xe=x*100; 
	Ye=y*100;
	N=Xe+Ye;

	if((Xe!=0)&&(Ye==0))	//x���겻Ϊ0��y����Ϊ0
	{
		for(i=50;i<=200;)
		{
			X_MotorRun(i,Dx,i);
			i=i+50;
		}
		X_MotorRun(200,Dx,Xe-1000);
		for(i=200;i>=0;)
		{
			X_MotorRun(i,Dx,i);
			i=i-50;
		}
	}

	if((Xe==0)&&(Ye!=0))	//y���겻Ϊ0��x����Ϊ0
	{
		for(i=50;i<=200;)
		{
			Y_MotorRun(i,Dy,i);
			i=i+50;
		}
		Y_MotorRun(200,Dy,Ye-1000);
		for(i=200;i>=0;)
		{
			Y_MotorRun(i,Dy,i);
			i=i-50;
		}
	}		
										   
	if((Xe!=0)&&(Ye!=0))	//x��y�������Ϊ0
	{
		while(N>(Xe+Ye-500))	//�岹��ʼ���200���������
  		{
			if(F>=0)
			{
				X_MotorRun(Xe+Ye-N+1,Dx,1);
				F=F-Ye;
				N--;
			}
			else
			{
				Y_MotorRun(Xe+Ye-N+1,Dy,1);
				F=F+Xe;
				N--;
			}
		}
		while((500<N)&&(N<=(Xe+Ye-500)))	//�м����������
		{
			if(F>=0)
			{
				X_MotorRun(500,Dx,1);
				F=F-Ye;
				N--;
			}
			else
			{
				Y_MotorRun(500,Dy,1);
				F=F+Xe;
				N--;
			}
		}
		while((N>0)&&N<=500)	//�岹����ǰ��200���������
		{
			if(F>=0)
			{
				X_MotorRun(N,Dx,1);
				F=F-Ye;
				N--;
			}
			else
			{
				Y_MotorRun(N,Dy,1);
				F=F+Xe;
				N--;
			}
		}
	}	
}

//Բ���岹����
void Arc(void)	
{
	int32s x0=0,y0=0,x1,y1;	//�岹��㡢�յ�����(mm);
	int32u Dx0,Dy0,Dx1,Dy1,R_D;	//���������ż��岹����
	int32s Step_x0,Step_y0,Step_x1,Step_y1,Step_xi,Step_yi,F=0;	//	��㡢�յ㡢����Ĳ�������;ƫ��

	while(1)	//x0��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dx0=0; break;
			case 12: Dx0=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x0=x0*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//��ֹ����������
		BuzzerOff;
		break;
	}
	if(Dx0==0) Step_x0=x0*(-100);
	else Step_x0=x0*100;  

	while(1)	//y0��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dy0=0; break;
			case 12: Dy0=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y0=y0*10+KeyBoard();
			Delay_ms(1000);	//��ֹ����������
			PB0_H;			
		}
		BuzzerOn;
		Delay_ms(1000);
		BuzzerOff;
		break;
	}
	if(Dy0==0) Step_y0=y0*(-100);
	else Step_y0=y0*100;

	while(1)	//x1��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dx1=0; break;
			case 12: Dx1=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x1=x1*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//��ֹ����������
		BuzzerOff;
		break;
	}
	if(Dx1==0) Step_x1=x1*(-100);
	else Step_x1=x1*100;

	while(1)	//y1��������
	{
		switch(KeyBoard())	//����ѡ��
		{
			case 11: Dy1=0; break;
			case 12: Dy1=1; break;
			default: continue;
		}
		Delay_ms(1000);	//��ֹ����������
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y1=y1*10+KeyBoard();
			Delay_ms(1000);	//��ֹ����������
			PB0_H;			
		}
		BuzzerOn;
		Delay_ms(1000);
		BuzzerOff;
		break;
	}
	if(Dy1==0) Step_y1=y1*(-100);
	else Step_y1=y1*100;

	while(1)	//�岹��������
	{
		switch(KeyBoard())	
		{
			case 11: R_D=0; break;	//��ʱ��Բ���岹
			case 12: R_D=1; break;	//˳ʱ��Բ���岹
			default: continue;
		}
		BuzzerOn;
		Delay_ms(1000);	//�����岹
		BuzzerOff;
		break;
	}
	Z_MotorRun(200,1,100);
	X_MotorRun(200,Dx0,x0*100);
	Y_MotorRun(200,Dy0,y0*100);		//�����ƶ����岹��ʼ��
	Z_MotorRun(200,0,100);

	if(R_D==0)	//��ʱ��Բ���岹
	{
		Step_xi=Step_x0;
		Step_yi=Step_y0;
		do
		{
			if((Step_xi>0)&&(Step_yi)>=0)	//��һ����
			{
				if(F>=0) 
				{
					X_MotorRun(100,0,1);
					F=F-2*Step_xi+1;
					Step_xi--;
				}
				else
				{
					Y_MotorRun(200,1,1);
					F=F+2*Step_yi+1;
					Step_yi++;	
				}
			}
			else if((Step_xi<=0)&&(Step_yi)>0)	//�ڶ�����
			{
				if(F>=0) 
				{
					Y_MotorRun(200,0,1);
					F=F-2*Step_yi+1;
					Step_yi--;
				}
				else
				{
					X_MotorRun(100,0,1);
					F=F-2*Step_xi+1;
					Step_xi--;	
				}
			}
			else if((Step_xi<0)&&(Step_yi)<=0)	//��������
			{
				if(F>=0) 
				{
					X_MotorRun(100,1,1);
					F=F+2*Step_xi+1;
					Step_xi++;
				}
				else
				{
					Y_MotorRun(200,0,1);
					F=F-2*Step_yi+1;
					Step_yi--;	
				}
			}
			else if((Step_xi>=0)&&(Step_yi)<0)	//��������
			{
				if(F>=0) 
				{
					Y_MotorRun(200,1,1);
					F=F+2*Step_yi+1;
					Step_yi++;
				}
				else
				{
					X_MotorRun(100,1,1);
					F=F+2*Step_xi+1;
					Step_xi++;
				}
			}	
		}
		while((Step_xi!=Step_x1)&&(Step_yi!=Step_y1));
	}

	else	//˳ʱ��Բ���岹
	{
		Step_xi=Step_x0;
		Step_yi=Step_y0;
		do
		{
			if((Step_xi>=0)&&(Step_yi)>0)	//��һ����
			{
				if(F>=0) 
				{
					Y_MotorRun(200,0,1);
					F=F-2*Step_yi+1;
					Step_yi--;
				}
				else
				{
					X_MotorRun(100,1,1);
					F=F+2*Step_xi+1;
					Step_xi++;	
				}			   
			}
			else if((Step_xi>0)&&(Step_yi)<=0)	//��������
			{
				if(F>=0) 
				{
					X_MotorRun(100,0,1);
					F=F-2*Step_xi+1;
					Step_xi--;
				}
				else
				{
					Y_MotorRun(200,0,1);
					F=F-2*Step_yi+1;
					Step_yi--;
				}
			}
			else if((Step_xi<=0)&&(Step_yi)<0)	//��������
			{
				if(F>=0) 
				{
					Y_MotorRun(200,1,1);
					F=F+2*Step_yi+1;
					Step_yi++;
				}
				else
				{
					X_MotorRun(100,0,1);
					F=F-2*Step_xi+1;
					Step_xi--;
				}
			}
			else if((Step_xi<0)&&(Step_yi)>=0)	//�ڶ�����
			{
				if(F>=0) 
				{
					X_MotorRun(100,1,1);
					F=F+2*Step_xi+1;
					Step_xi++;
				}
				else
				{
					Y_MotorRun(200,1,1);
					F=F+2*Step_yi+1;
					Step_yi++;	
				}
			}	
		}
		while((Step_xi!=Step_x1)&&(Step_yi!=Step_y1));
	}			
}
