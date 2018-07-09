#ifndef IWDG_TASK_H_
#define IWDG_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//---定义使用的头文件
#include "iwdg_lib.h"

//---外部调用接口
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---函数定义
UINT8_T IWDGTask_Init(IWDG_HandlerType *IWDGx);
UINT8_T IWDGTask_DeInit(IWDG_HandlerType *IWDGx);
UINT8_T IWDGTask_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_TASK_H_ */