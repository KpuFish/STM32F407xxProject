#ifndef IWDG_TASK_H_
#define IWDG_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//---����ʹ�õ�ͷ�ļ�
#include "iwdg_lib.h"

//---�ⲿ���ýӿ�
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---��������
UINT8_T IWDGTask_Init(IWDG_HandlerType *IWDGx);
UINT8_T IWDGTask_DeInit(IWDG_HandlerType *IWDGx);
UINT8_T IWDGTask_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_TASK_H_ */