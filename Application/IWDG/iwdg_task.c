#include "iwdg_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGTask_Init(IWDG_HandlerType *IWDGx)
{
	return IWDGLib_Init(IWDGx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGTask_DeInit(IWDG_HandlerType *IWDGx)
{
	return IWDGLib_DeInit(IWDGx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGTask_Reset(IWDG_HandlerType *IWDGx)
{
	return IWDGLib_Reset(IWDGx);
}