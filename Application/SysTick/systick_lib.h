#ifndef SYSTICK_LIB_H_
#define SYSTICK_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//------------使用包含的头文件
#include "systick_cfg.h"
//---函数定义
UINT8_T	 SysTickLib_Init(void);
UINT8_T	 SysTickLib_DeInit(void);
UINT8_T	 SysTickLib_TickTask(UINT32_T tickFreq, void(*TickTask)(void));
UINT8_T  SysTickLib_IRQDecTick(UINT32_T waitDecTick);
UINT32_T SysTickLib_GetTick(void);
UINT8_T	 SysTickLib_IRQTask(void);
UINT8_T	 SysTickLib_WaitTick(UINT32_T usTimer);
UINT8_T  SysTickLib_1msTick(void);
UINT32_T SysTickLib_GetTickOVF(void);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYSTICK_LIB_H_ */