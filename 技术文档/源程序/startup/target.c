
/**--------------File Info---------------------------------------------------------------------------------
** File name:			target.c
** modified Date:  		2013-1-5
** Last Version:		V2.00
** Descriptions:		目标板系统时钟配置，以及内核相关的设置（注意：是ARM内核，非芯片外设）
**	
*********************************************************************************************************/
#include "stm32f10x.h"  

/********************************************************************************************************
**函数信息 ：SystemInit (void)                         // WAN.CG // 2013.01.05 
**功能描述 ：系统时钟初始化函数，初始化之前先复位所有时钟
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void SystemInit (void)
{
	RCC->CR |= (uint32_t)0x00000001;  //CR寄存器BIT0位（HSION位）置1，作用是连接内部时钟HSI作为系统时钟
                                      //这样做是为了下边的操作做准备
#ifndef STM32F10X_CL                  //复位 SW, HPRE, PPRE1, PPRE2, ADCPRE 和 MCO 控制位
	RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
	RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif //STM32F10X_CL  
  
	RCC->CR &= (uint32_t)0xFEF6FFFF;      //复位 HSEON, CSSON and PLLON 控制位
	RCC->CR &= (uint32_t)0xFFFBFFFF;      //复位Reset HSEBYP 控制位，只有先清除HSEON位（即断开外部时钟），该位才能清除  
	RCC->CFGR &= (uint32_t)0xFF80FFFF;    //复位PLLSRC, PLLXTPRE, PLLMUL 和 USBPRE/OTGFSPRE 控制位

#ifdef STM32F10X_CL
	RCC->CR &= (uint32_t)0xEBFFFFFF;      //复位 Reset PLL2ON and PLL3ON 控制位
	RCC->CIR = 0x00FF0000;                //禁止所有中断，清除中断标志位 
	RCC->CFGR2 = 0x00000000;              //复位 CFGR2 寄存器
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
	RCC->CIR = 0x009F0000;                //禁止所有中断，清除中断标志位 
	RCC->CFGR2 = 0x00000000;              //复位 CFGR2 寄存器
#else
	RCC->CIR = 0x009F0000;                //禁止所有中断，清除中断标志位 
#endif //STM32F10X_CL  

	SetSysClock();  //配置系统时钟，HCLK, PCLK2 和 PCLK1预分频，设置存储器访问周期

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;  //向量表重映射到内部RAM
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; //向量表重映射到内部FLASH
#endif 
}

/********************************************************************************************************
**函数信息 ：SystemInit (void)                         // WAN.CG // 2013.01.05 
**功能描述 ：设置系统时钟//Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void SetSysClock(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;  //初始化变量
   
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);  //连接外部时钟 

	do                                    //等待外部时钟稳定，如果连接超时，程序将退出
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;  //检测HSE是否连接成功
		StartUpCounter++;                     //超时计数，该变量在target.H文件中有定义
	} 
	while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT)); //退出条件，连接成功或超时

	if (HSEStatus)  //如果HSE连接成功
	{
		FLASH->ACR |= FLASH_ACR_PRFTBE;  //使能FLASH欲取指缓冲器
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    //FLASH等待周期设置为2 

		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;  	//HCLK（AHB总线时钟） = SYSCLK（系统时钟）
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;		//PCLK2（APB2时钟） = HCLK
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;  	//PCLK1（APB1时钟） = HCLK/2

#ifdef STM32F10X_CL  //CL型单片机，默认HSE为25M		
		//PLL2配置: PLL2CLK = (HSE / 5) * 8 = 40 MH
		//PREDIV1配置: PREDIV1CLK = PLL2 / 5 = 8 MH ，CL型的单片机PREDIV1 CLK将作为PLL1的时钟源       
		RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL | RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
		RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 | RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);
		RCC->CR |= RCC_CR_PLL2ON;    	//使能PLL2
		while((RCC->CR & RCC_CR_PLL2RDY) == 0);  	//等待PLL2配置完成
   
		//PLL配置: PLLCLK = PREDIV1 * 9 = 72 MHz 
		RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLMULL9);  //如果需要改动时钟，只需要改动此处即可
#else   //其他型单片机，默认HSE为8M  
		//PLL配置: PLLCLK = HSE * 9 = 72 MHz
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);  //如果需要改动时钟，只需要改动此处即可，如：外部晶振为12M，需要48M内核频率
#endif  //STM32F10X_CL                                                     //只需要把RCC_CFGR_PLLMULL9更改为RCC_CFGR_PLLMULL4即可

		RCC->CR |= RCC_CR_PLLON;   //使能PLL
		while((RCC->CR & RCC_CR_PLLRDY) == 0);//等待PLL配置完成
    
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));  //选择PLL时钟作为系统时钟
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08); //等待系统时钟配置完成
	}
	else
	{ 
		//如果系统内部时钟未能成功启动，代码将运行到此处，用户可以在此添加一些相关代码
	}
}
/********************************************************************************************************
**函数信息 ：IrqDisable / IrqEnable                          // WAN.CG // 2010.3.25 
**功能描述 ：禁止/允许全部IRQ中断，特权模式下使用
**输入参数 ：
**输出参数 ：
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
**函数信息 ：DisablePRI  / RecoveryPRI                          // WAN.CG // 2010.3.25 
**功能描述 ：特权模式下使用;先保存寄存器状态，然后禁止中断 / 恢复中断标志寄存器状态，这样做是为了可以支持
             在嵌套中断中调用，这两个函数必须成对出现，而且使用前必须定义一个临时变量存储寄存器状态
**输入参数 ：
**输出参数 ：
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
**函数信息 ：NVIC_SetPriority                      // WAN.CG // 2013.01.05 
**功能描述 ：中断优先级配置
**输入参数 ：中断号和中断优先级
**输出参数 ：无
********************************************************************************************************/
static void NVIC_SetPriority(IRQn_Type IRQn, int32u priority)
{
	if(IRQn < 0) //配置系统内核的中断优先级
	{
		SCB->SHP[((int32u)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); 
	} 
	else    //配置芯片外设的中断优先级
	{
		NVIC->IP[(int32u)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    
	}     
}
/********************************************************************************************************
**函数信息 ：SysTick_Config                      // WAN.CG // 2013.01.05 
**功能描述 ：系统定时器配置函数，系统定时器使用的是系统时钟
**输入参数 ：计数值，系统定时器是M3内核自带的24位定时器，最大值不能超过24位
**输出参数 ：无
********************************************************************************************************/
int32u SysTick_Config(int32u ticks)
{ 
	if (ticks > SysTick_LOAD_RELOAD_Msk)  
		return (1);            //如果计数长度超过系统定时器最大设置数值时，失败
                                                               
	SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      //设置重装载寄存器
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  //设置系统定时器中断优先权
	SysTick->VAL   = 0;                                          //加载起始记数值
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;  //使能系统定时器中断
	return (0);                                                  //设置成功返回0
}


