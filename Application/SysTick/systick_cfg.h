#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//---使用包含的头文件
#include "complier_lib.h"
//---变量定义
//---结构体声明
typedef struct _SysTick_HandlerType			SysTick_HandlerType;
//---结构体指针的声明
typedef struct _SysTick_HandlerType			*pSysTick_HandlerType;

//---滴答定时器的结构体
struct _SysTick_HandlerType
{
	VLTUINT32_T				msgInc;																					//---定时器递加计数器
	VLTUINT32_T				msgDec;																					//---定时器递减计数器
	VLTUINT32_T				msgOVF;																					//---定时计数器溢出
	VLTUINT32_T				msgTaskInc;																				//---任务计数器
	VLTUINT32_T				msgTaskMax;																				//---任务计数上限
	void(*msgTaskHal)(void);																						//---hal库的计数方式
	void(*msgTaskFunc)(void);																						//---注册任务函数
};

//---外部调用接口
extern SysTick_HandlerType		g_SysTick;
extern pSysTick_HandlerType		pSysTick ;

//---函数定义
UINT8_T SysTick_Init(void);
UINT8_T SysTick_DeInit(void);
UINT8_T SysTick_TickTask(UINT32_T tickFreq, void(*TickTask)(void));
UINT8_T SysTick_IRQDecTick(UINT32_T waitDecTick);
UINT32_T SysTick_GetTick(void);
UINT8_T SysTick_IRQTask(void);
UINT8_T SysTick_WaitTick(UINT32_T usTimer);
UINT8_T SysTick_1msTick(void);
UINT32_T SysTick_GetTickOVF(void);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYSTICK_CFG_H_ */