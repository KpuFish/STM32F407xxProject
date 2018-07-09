#ifndef SYSTICK_TASK_H_
#define SYSTICK_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//---ͷ�ļ�����
#include "systick_lib.h"
//---��������
UINT8_T	 SysTickTask_Init(void);
UINT8_T	 SysTickTask_DeInit(void);
UINT8_T	 SysTickTask_TickTask(UINT32_T tickFreq, void(*TickTask)(void));
UINT8_T  SysTickTask_IRQDecTick(UINT32_T waitDecTick);
UINT32_T SysTickTask_GetTick(void);
UINT8_T	 SysTickTask_IRQTask(void);
UINT8_T	 SysTickTask_WaitTick(UINT32_T usTimer);
UINT8_T  SysTickTask_1msTick(void);
UINT32_T SysTickTask_GetTickOVF(void);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SYSTICK_TASK_H_ */
