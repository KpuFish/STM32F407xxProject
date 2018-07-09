#ifndef IWDG_LIB_H_
#define IWDG_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//---定义使用的头文件
#include "iwdg_cfg.h"

//---外部调用接口
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---函数定义
UINT8_T IWDGLib_Init(IWDG_HandlerType *IWDGx);
UINT8_T IWDGLib_DeInit(IWDG_HandlerType *IWDGx);
UINT8_T IWDGLib_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_LIB_H_ */