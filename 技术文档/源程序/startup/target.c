
/**--------------File Info---------------------------------------------------------------------------------
** File name:			target.c
** modified Date:  		2013-1-5
** Last Version:		V2.00
** Descriptions:		Ŀ���ϵͳʱ�����ã��Լ��ں���ص����ã�ע�⣺��ARM�ںˣ���оƬ���裩
**	
*********************************************************************************************************/
#include "stm32f10x.h"  

/********************************************************************************************************
**������Ϣ ��SystemInit (void)                         // WAN.CG // 2013.01.05 
**�������� ��ϵͳʱ�ӳ�ʼ����������ʼ��֮ǰ�ȸ�λ����ʱ��
**������� ����
**������� ����
********************************************************************************************************/
void SystemInit (void)
{
	RCC->CR |= (uint32_t)0x00000001;  //CR�Ĵ���BIT0λ��HSIONλ����1�������������ڲ�ʱ��HSI��Ϊϵͳʱ��
                                      //��������Ϊ���±ߵĲ�����׼��
#ifndef STM32F10X_CL                  //��λ SW, HPRE, PPRE1, PPRE2, ADCPRE �� MCO ����λ
	RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
	RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif //STM32F10X_CL  
  
	RCC->CR &= (uint32_t)0xFEF6FFFF;      //��λ HSEON, CSSON and PLLON ����λ
	RCC->CR &= (uint32_t)0xFFFBFFFF;      //��λReset HSEBYP ����λ��ֻ�������HSEONλ�����Ͽ��ⲿʱ�ӣ�����λ�������  
	RCC->CFGR &= (uint32_t)0xFF80FFFF;    //��λPLLSRC, PLLXTPRE, PLLMUL �� USBPRE/OTGFSPRE ����λ

#ifdef STM32F10X_CL
	RCC->CR &= (uint32_t)0xEBFFFFFF;      //��λ Reset PLL2ON and PLL3ON ����λ
	RCC->CIR = 0x00FF0000;                //��ֹ�����жϣ�����жϱ�־λ 
	RCC->CFGR2 = 0x00000000;              //��λ CFGR2 �Ĵ���
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
	RCC->CIR = 0x009F0000;                //��ֹ�����жϣ�����жϱ�־λ 
	RCC->CFGR2 = 0x00000000;              //��λ CFGR2 �Ĵ���
#else
	RCC->CIR = 0x009F0000;                //��ֹ�����жϣ�����жϱ�־λ 
#endif //STM32F10X_CL  

	SetSysClock();  //����ϵͳʱ�ӣ�HCLK, PCLK2 �� PCLK1Ԥ��Ƶ�����ô洢����������

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;  //��������ӳ�䵽�ڲ�RAM
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; //��������ӳ�䵽�ڲ�FLASH
#endif 
}

/********************************************************************************************************
**������Ϣ ��SystemInit (void)                         // WAN.CG // 2013.01.05 
**�������� ������ϵͳʱ��//Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
**������� ����
**������� ����
********************************************************************************************************/
void SetSysClock(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;  //��ʼ������
   
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);  //�����ⲿʱ�� 

	do                                    //�ȴ��ⲿʱ���ȶ���������ӳ�ʱ�������˳�
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;  //���HSE�Ƿ����ӳɹ�
		StartUpCounter++;                     //��ʱ�������ñ�����target.H�ļ����ж���
	} 
	while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT)); //�˳����������ӳɹ���ʱ

	if (HSEStatus)  //���HSE���ӳɹ�
	{
		FLASH->ACR |= FLASH_ACR_PRFTBE;  //ʹ��FLASH��ȡָ������
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    //FLASH�ȴ���������Ϊ2 

		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;  	//HCLK��AHB����ʱ�ӣ� = SYSCLK��ϵͳʱ�ӣ�
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;		//PCLK2��APB2ʱ�ӣ� = HCLK
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;  	//PCLK1��APB1ʱ�ӣ� = HCLK/2

#ifdef STM32F10X_CL  //CL�͵�Ƭ����Ĭ��HSEΪ25M		
		//PLL2����: PLL2CLK = (HSE / 5) * 8 = 40 MH
		//PREDIV1����: PREDIV1CLK = PLL2 / 5 = 8 MH ��CL�͵ĵ�Ƭ��PREDIV1 CLK����ΪPLL1��ʱ��Դ       
		RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL | RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
		RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 | RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);
		RCC->CR |= RCC_CR_PLL2ON;    	//ʹ��PLL2
		while((RCC->CR & RCC_CR_PLL2RDY) == 0);  	//�ȴ�PLL2�������
   
		//PLL����: PLLCLK = PREDIV1 * 9 = 72 MHz 
		RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLMULL9);  //�����Ҫ�Ķ�ʱ�ӣ�ֻ��Ҫ�Ķ��˴�����
#else   //�����͵�Ƭ����Ĭ��HSEΪ8M  
		//PLL����: PLLCLK = HSE * 9 = 72 MHz
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);  //�����Ҫ�Ķ�ʱ�ӣ�ֻ��Ҫ�Ķ��˴����ɣ��磺�ⲿ����Ϊ12M����Ҫ48M�ں�Ƶ��
#endif  //STM32F10X_CL                                                     //ֻ��Ҫ��RCC_CFGR_PLLMULL9����ΪRCC_CFGR_PLLMULL4����

		RCC->CR |= RCC_CR_PLLON;   //ʹ��PLL
		while((RCC->CR & RCC_CR_PLLRDY) == 0);//�ȴ�PLL�������
    
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));  //ѡ��PLLʱ����Ϊϵͳʱ��
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08); //�ȴ�ϵͳʱ���������
	}
	else
	{ 
		//���ϵͳ�ڲ�ʱ��δ�ܳɹ����������뽫���е��˴����û������ڴ����һЩ��ش���
	}
}
/********************************************************************************************************
**������Ϣ ��IrqDisable / IrqEnable                          // WAN.CG // 2010.3.25 
**�������� ����ֹ/����ȫ��IRQ�жϣ���Ȩģʽ��ʹ��
**������� ��
**������� ��
********************************************************************************************************/
__asm void IrqDisable (void)
{
    CPSID   I
    BX      LR
}

__asm void IrqEnable (void)
{
    CPSIE   I
    BX      LR
}
/********************************************************************************************************
**������Ϣ ��DisablePRI  / RecoveryPRI                          // WAN.CG // 2010.3.25 
**�������� ����Ȩģʽ��ʹ��;�ȱ���Ĵ���״̬��Ȼ���ֹ�ж� / �ָ��жϱ�־�Ĵ���״̬����������Ϊ�˿���֧��
             ��Ƕ���ж��е��ã���������������ɶԳ��֣�����ʹ��ǰ���붨��һ����ʱ�����洢�Ĵ���״̬
**������� ��
**������� ��
********************************************************************************************************/
__asm int32s DisablePRI(void)
{
    MRS     R0, PRIMASK                           
    CPSID   I
    BX      LR
}

__asm void RecoveryPRI(int32s primask)
{
    MSR     PRIMASK, R0
    BX      LR
}
/********************************************************************************************************
**������Ϣ ��NVIC_SetPriority                      // WAN.CG // 2013.01.05 
**�������� ���ж����ȼ�����
**������� ���жϺź��ж����ȼ�
**������� ����
********************************************************************************************************/
static void NVIC_SetPriority(IRQn_Type IRQn, int32u priority)
{
	if(IRQn < 0) //����ϵͳ�ں˵��ж����ȼ�
	{
		SCB->SHP[((int32u)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); 
	} 
	else    //����оƬ������ж����ȼ�
	{
		NVIC->IP[(int32u)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    
	}     
}
/********************************************************************************************************
**������Ϣ ��SysTick_Config                      // WAN.CG // 2013.01.05 
**�������� ��ϵͳ��ʱ�����ú�����ϵͳ��ʱ��ʹ�õ���ϵͳʱ��
**������� ������ֵ��ϵͳ��ʱ����M3�ں��Դ���24λ��ʱ�������ֵ���ܳ���24λ
**������� ����
********************************************************************************************************/
int32u SysTick_Config(int32u ticks)
{ 
	if (ticks > SysTick_LOAD_RELOAD_Msk)  
		return (1);            //����������ȳ���ϵͳ��ʱ�����������ֵʱ��ʧ��
                                                               
	SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      //������װ�ؼĴ���
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  //����ϵͳ��ʱ���ж�����Ȩ
	SysTick->VAL   = 0;                                          //������ʼ����ֵ
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;  //ʹ��ϵͳ��ʱ���ж�
	return (0);                                                  //���óɹ�����0
}


