#ifndef STM32_CFG_H_
#define STM32_CFG_H_
////////////////////////////////////////////////////////////////////////////////////////////
//---定义使用的头文件
//#define USE_MCU_STM32F0
//#define USE_MCU_STM32F1
//#define USE_MCU_STM32F2
//#define USE_MCU_STM32F3
#define USE_MCU_STM32F4

//---检查是否定义了外部使用的晶振
#ifndef HSE_VALUE
	#define	HSE_VALUE			8000000UL
#endif

//===选择系列---寄存器的定义
#if  defined(USE_MCU_STM32F0)
	#include "stm32f0xx.h"
	#include "system_stm32f0xx.h"
#elif defined(USE_MCU_STM32F1)
	#include "stm32f1xx.h"
	#include "system_stm32f1xx.h"
#elif defined(USE_MCU_STM32F2)
	#include "stm32f2xx.h"
	#include "system_stm32f2xx.h"
#elif defined(USE_MCU_STM32F3)
	#include "stm32f3xx.h"
	#include "system_stm32f3xx.h"
#elif defined(USE_MCU_STM32F4)
	#include "stm32f4xx.h"
	#include "system_stm32f4xx.h"
#else
	#error "STM32器件的型号选择错误!"
#endif

//===使用的库文件
#if defined(USE_HAL_DRIVER)||defined(USE_FULL_LL_DRIVER)
	//---LL库
	#if defined (USE_FULL_LL_DRIVER )
		//---定义NVIC使用的分组
		#ifndef NVIC_PRIORITYGROUP_4
			#define NVIC_PRIORITYGROUP_0         0x00000007U
			#define NVIC_PRIORITYGROUP_1         0x00000006U
			#define NVIC_PRIORITYGROUP_2         0x00000005U
			#define NVIC_PRIORITYGROUP_3         0x00000004U
			#define NVIC_PRIORITYGROUP_4         0x00000003U
		#endif
		//---根据不同不同型号的MCU选择头文件
		#ifdef USE_MCU_STM32F0
			#include "stm32f0xx_ll.h"
		#elif defined USE_MCU_STM32F1
			#include "stm32f1xx_ll.h"
			//---GPIO的翻转时钟定义
			#ifndef LL_GPIO_SPEED_FREQ_VERY_HIGH
				#define LL_GPIO_SPEED_FREQ_VERY_HIGH		LL_GPIO_SPEED_FREQ_HIGH
			#endif
		#elif defined(USE_MCU_STM32F2)
			#include "stm32f2xx_ll.h"
		#elif defined(USE_MCU_STM32F3)
			#include "stm32f3xx_ll.h"
		#elif defined(USE_MCU_STM32F4)
			#include "stm32f4xx_ll.h"
		#else
			#error "STM32的LL库导入错误!"
		#endif
	#endif
    //---Hal库
	#if defined (USE_HAL_DRIVER)
		#ifdef USE_MCU_STM32F0
			#include "stm32f0xx_hal.h"
		#elif defined(USE_MCU_STM32F1)
			#include "stm32f1xx_hal.h"
		#elif defined(USE_MCU_STM32F2)
			#include "stm32f2xx_hal.h"
		#elif defined(USE_MCU_STM32F3)
			#include "stm32f3xx_hal.h"
		#elif defined(USE_MCU_STM32F4)
			#include "stm32f4xx_hal.h"
		#else
			#error "STM32的Hal库导入错误!"
		#endif
	#endif
#else
	#error "STM32库文件导入错误!"
#endif

//---独立看门狗文件
#include "iwdg_cfg.h"
//---获取系统时钟的定义
#define	SYS_CLOCK_HZ						( SystemCoreClock )
#define	SYS_CLOCK_KHZ						( (SYS_CLOCK_HZ/1000U) )
#define SYS_CLOCK_MHZ						( (SYS_CLOCK_HZ/1000000U) )
//---使能全局中断
#define SEI()								_irq_enable()
//---禁止全局中断
#define CLI()								_irq_disable()
//---喂狗
#define WDT_RESET()							IWDG_Reset(pIWDG);
//---软件复位
#define SOFT_RESET()						( CLI(),NVIC_SystemReset() )
//---错误处理
#define Error_Handler()						_Error_Handler(__FILE__, __LINE__)
//---函数定义
void _irq_enable(void);
void _irq_disable(void);
void _Error_Handler(char * file, int line);
///////////////////////////////////////////////////////////////////////////////////////////
#endif /* STM32_CFG_H_ */