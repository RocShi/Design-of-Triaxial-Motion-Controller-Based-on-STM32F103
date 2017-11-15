#ifndef __DELAY_H
#define __DELAY_H 			   

//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
//版本：V1.2
//V1.2修改说明
//修正了中断中调用出现死循环的错误
//防止延时不准确,采用do while结构!
////////////////////////////////////////////////////////////////////////////////// 
void Delay_Init(int8u SYSCLK);
void Delay_ms(int16u nms);
void Delay_us(int32u nus);

#endif
