
/**--------------File Info---------------------------------------------------------------------------------
** File name:			target.h
** modified Date:  		2013-1-5
** Last Version:		V2.00
** Descriptions:	    Ŀ���ϵͳʱ�����ã��Լ��ں���ص����ã�ע�⣺���ںˣ������裩
**	
*********************************************************************************************************/

#ifndef _RARGET_H_
#define _RARGET_H_

#define HSE_STARTUP_TIMEOUT  ((uint16_t)0x0500)  //�ⲿ��������ʱ�䳬ʱ���壬�û����޸�
#define HSE_VALUE            ((uint32_t)8000000) //�ⲿ�����Ƶ�ʣ�����ʵ�ʵ��ⲿ�����壬�������103������ʹ��8M�ⲿ����
#define HSI_VALUE            ((uint32_t)8000000) //�ڲ������Ƶ�ʣ�һ��Ϊ8M
#define SystemFrequency      72000000	         //ϵͳ�ں�ʱ��ѡ��72M
#define VECT_TAB_OFFSET      0x0                 //�������������ַƫ����

#define __NVIC_PRIO_BITS           4 //��ѡ16����4���أ��ж����ȼ�
#define __Vendor_SysTickConfig     0 //����в�ͬ��ϵͳ��ʱ�����ô˴�����1

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
        
extern void    SystemInit(void);   //ϵͳʱ�ӳ�ʼ��
extern void    SetSysClock(void);  //����ϵͳʱ��
extern int32u  SysTick_Config(int32u ticks); //ϵͳ��ʱ������
extern void    IrqDisable (void);//��ֹ�ж�
extern void    IrqEnable (void); //�����ж�

extern int32s DisablePRI(void);
extern void RecoveryPRI(int32s primask);

#endif //_RARGET_H_ 
 

