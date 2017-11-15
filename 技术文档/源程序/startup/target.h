
/**--------------File Info---------------------------------------------------------------------------------
** File name:			target.h
** modified Date:  		2013-1-5
** Last Version:		V2.00
** Descriptions:	    目标板系统时钟配置，以及内核相关的设置（注意：是内核，非外设）
**	
*********************************************************************************************************/

#ifndef _RARGET_H_
#define _RARGET_H_

#define HSE_STARTUP_TIMEOUT  ((uint16_t)0x0500)  //外部晶振起振时间超时定义，用户可修改
#define HSE_VALUE            ((uint32_t)8000000) //外部晶振的频率，根据实际的外部晶振定义，格兰瑞的103开发板使用8M外部晶振
#define HSI_VALUE            ((uint32_t)8000000) //内部晶振的频率，一般为8M
#define SystemFrequency      72000000	         //系统内核时钟选择72M
#define VECT_TAB_OFFSET      0x0                 //设置向量表基地址偏移量

#define __NVIC_PRIO_BITS           4 //可选16个（4比特）中断优先级
#define __Vendor_SysTickConfig     0 //如果有不同的系统定时器配置此处请置1

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq
#define __NOP                             __nop
#define __WFI                             __wfi
#define __WFE                             __wfe
#define __SEV                             __sev
#define __ISB()                           __isb(0)
#define __DSB()                           __dsb(0)
#define __DMB()                           __dmb(0)
#define __REV                             __rev
#define __RBIT                            __rbit
#define __LDREXB(ptr)                     ((unsigned char ) __ldrex(ptr))
#define __LDREXH(ptr)                     ((unsigned short) __ldrex(ptr))
#define __LDREXW(ptr)                     ((unsigned int  ) __ldrex(ptr))
#define __STREXB(value, ptr)              __strex(value, ptr)
#define __STREXH(value, ptr)              __strex(value, ptr)
#define __STREXW(value, ptr)              __strex(value, ptr)
        
extern void    SystemInit(void);   //系统时钟初始化
extern void    SetSysClock(void);  //设置系统时钟
extern int32u  SysTick_Config(int32u ticks); //系统定时器设置
extern void    IrqDisable (void);//禁止中断
extern void    IrqEnable (void); //允许中断

extern int32s DisablePRI(void);
extern void RecoveryPRI(int32s primask);

#endif //_RARGET_H_ 
 

