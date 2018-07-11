#ifndef STM32_CFG_H_
#define STM32_CFG_H_
////////////////////////////////////////////////////////////////////////////////////////////
//---����ʹ�õ�ͷ�ļ�
//#define USE_MCU_STM32F0
//#define USE_MCU_STM32F1
//#define USE_MCU_STM32F2
//#define USE_MCU_STM32F3
#define USE_MCU_STM32F4

//---����Ƿ������ⲿʹ�õľ���
#ifndef HSE_VALUE
	#define	HSE_VALUE			8000000UL
#endif

//===ѡ��ϵ��---�Ĵ����Ķ���
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
	#error "STM32�������ͺ�ѡ�����!"
#endif

//===ʹ�õĿ��ļ�
#if defined(USE_HAL_DRIVER)||defined(USE_FULL_LL_DRIVER)
	//---LL��
	#if defined (USE_FULL_LL_DRIVER )
		//---����NVICʹ�õķ���
		#ifndef NVIC_PRIORITYGROUP_4
			#define NVIC_PRIORITYGROUP_0         0x00000007U
			#define NVIC_PRIORITYGROUP_1         0x00000006U
			#define NVIC_PRIORITYGROUP_2         0x00000005U
			#define NVIC_PRIORITYGROUP_3         0x00000004U
			#define NVIC_PRIORITYGROUP_4         0x00000003U
		#endif
		//---���ݲ�ͬ��ͬ�ͺŵ�MCUѡ��ͷ�ļ�
		#ifdef USE_MCU_STM32F0
			#include "stm32f0xx_ll.h"
		#elif defined USE_MCU_STM32F1
			#include "stm32f1xx_ll.h"
			//---GPIO�ķ�תʱ�Ӷ���
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
			#error "STM32��LL�⵼�����!"
		#endif
	#endif
    //---Hal��
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
			#error "STM32��Hal�⵼�����!"
		#endif
	#endif
#else
	#error "STM32���ļ��������!"
#endif

//---�������Ź��ļ�
#include "iwdg_cfg.h"
//---��ȡϵͳʱ�ӵĶ���
#define	SYS_CLOCK_HZ						( SystemCoreClock )
#define	SYS_CLOCK_KHZ						( (SYS_CLOCK_HZ/1000U) )
#define SYS_CLOCK_MHZ						( (SYS_CLOCK_HZ/1000000U) )
//---ʹ��ȫ���ж�
#define SEI()								_irq_enable()
//---��ֹȫ���ж�
#define CLI()								_irq_disable()
//---ι��
#define WDT_RESET()							IWDG_Reset(pIWDG);
//---�����λ
#define SOFT_RESET()						( CLI(),NVIC_SystemReset() )
//---������
#define Error_Handler()						_Error_Handler(__FILE__, __LINE__)
//---��������
void _irq_enable(void);
void _irq_disable(void);
void _Error_Handler(char * file, int line);
///////////////////////////////////////////////////////////////////////////////////////////
#endif /* STM32_CFG_H_ */