/****************************************Copyright (c)****************************************************
** 
**                                           石鹏
**
**                                      QQ：1195349851
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			Interpolation.c
** modified Date:  		2015-5-18
** Last Version:		V1.00
** Descriptions:		插补程序源文件
**	
*********************************************************************************************************/
#include "stm32f10x_rcc.h"  //时钟配置函数
#include "stm32f10x_gpio.h"
#include "Interpolation.h"
#include "SP_GPIO_Init.h"   //GPIO初始化
#include "Motor.h"
#include "Delay.h"       	//ms,us延时
#include "KeyBoard.h"       //矩阵键盘

//直线插补函数,可键盘输入终点x、y坐标，带启动、停止加减速
void Line(void)	//终点坐标x,y;单位mm
{
	int32u x=0,y=0,Xe,Ye,N;	//插补终点坐标x,y;X、Y轴各自步数Xe、Ye,总步数N
	int32u Dx,Dy;	//坐标正负号
	int32s i,F=0;	//偏差F。F就因为一开始定义的是无符号变量，结果死活偏差判别不正确!!

	while(1)	//x坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dx=0; break;
			case 12: Dx=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x=x*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//防止坐标误输入
		BuzzerOff;
		break;
	}

	while(1)	//y坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dy=0; break;
			case 12: Dy=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y=y*10+KeyBoard();
			Delay_ms(1000);	//防止坐标误输入
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

	if((Xe!=0)&&(Ye==0))	//x坐标不为0，y坐标为0
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

	if((Xe==0)&&(Ye!=0))	//y坐标不为0，x坐标为0
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
										   
	if((Xe!=0)&&(Ye!=0))	//x、y坐标均不为0
	{
		while(N>(Xe+Ye-500))	//插补开始后的200个脉冲加速
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
		while((500<N)&&(N<=(Xe+Ye-500)))	//中间段匀速运行
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
		while((N>0)&&N<=500)	//插补结束前的200个脉冲减速
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

//圆弧插补函数
void Arc(void)	
{
	int32s x0=0,y0=0,x1,y1;	//插补起点、终点坐标(mm);
	int32u Dx0,Dy0,Dx1,Dy1,R_D;	//坐标正负号及插补方向
	int32s Step_x0,Step_y0,Step_x1,Step_y1,Step_xi,Step_yi,F=0;	//	起点、终点、动点的步数坐标;偏差

	while(1)	//x0坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dx0=0; break;
			case 12: Dx0=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x0=x0*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//防止坐标误输入
		BuzzerOff;
		break;
	}
	if(Dx0==0) Step_x0=x0*(-100);
	else Step_x0=x0*100;  

	while(1)	//y0坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dy0=0; break;
			case 12: Dy0=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y0=y0*10+KeyBoard();
			Delay_ms(1000);	//防止坐标误输入
			PB0_H;			
		}
		BuzzerOn;
		Delay_ms(1000);
		BuzzerOff;
		break;
	}
	if(Dy0==0) Step_y0=y0*(-100);
	else Step_y0=y0*100;

	while(1)	//x1坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dx1=0; break;
			case 12: Dx1=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			x1=x1*10+KeyBoard();
			Delay_ms(1000);
			PB0_H;		
		}
		BuzzerOn;
		Delay_ms(1000);	//防止坐标误输入
		BuzzerOff;
		break;
	}
	if(Dx1==0) Step_x1=x1*(-100);
	else Step_x1=x1*100;

	while(1)	//y1坐标输入
	{
		switch(KeyBoard())	//正负选择
		{
			case 11: Dy1=0; break;
			case 12: Dy1=1; break;
			default: continue;
		}
		Delay_ms(1000);	//防止坐标误输入
		PB0_H;	
		while(KeyCheck0!=0)
		{
			y1=y1*10+KeyBoard();
			Delay_ms(1000);	//防止坐标误输入
			PB0_H;			
		}
		BuzzerOn;
		Delay_ms(1000);
		BuzzerOff;
		break;
	}
	if(Dy1==0) Step_y1=y1*(-100);
	else Step_y1=y1*100;

	while(1)	//插补方向输入
	{
		switch(KeyBoard())	
		{
			case 11: R_D=0; break;	//逆时针圆弧插补
			case 12: R_D=1; break;	//顺时针圆弧插补
			default: continue;
		}
		BuzzerOn;
		Delay_ms(1000);	//即将插补
		BuzzerOff;
		break;
	}
	Z_MotorRun(200,1,100);
	X_MotorRun(200,Dx0,x0*100);
	Y_MotorRun(200,Dy0,y0*100);		//快速移动至插补起始点
	Z_MotorRun(200,0,100);

	if(R_D==0)	//逆时针圆弧插补
	{
		Step_xi=Step_x0;
		Step_yi=Step_y0;
		do
		{
			if((Step_xi>0)&&(Step_yi)>=0)	//第一象限
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
			else if((Step_xi<=0)&&(Step_yi)>0)	//第二象限
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
			else if((Step_xi<0)&&(Step_yi)<=0)	//第三象限
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
			else if((Step_xi>=0)&&(Step_yi)<0)	//第四象限
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

	else	//顺时针圆弧插补
	{
		Step_xi=Step_x0;
		Step_yi=Step_y0;
		do
		{
			if((Step_xi>=0)&&(Step_yi)>0)	//第一象限
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
			else if((Step_xi>0)&&(Step_yi)<=0)	//第四象限
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
			else if((Step_xi<=0)&&(Step_yi)<0)	//第三象限
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
			else if((Step_xi<0)&&(Step_yi)>=0)	//第二象限
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
