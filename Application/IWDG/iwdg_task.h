#ifndef IWDG_TASK_H_
#define IWDG_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//---����ʹ�õ�ͷ�ļ�
#include "iwdg_cfg.h"
#include "iwdg_lib.h"
//---�������� 
  UINT8_T IWDGTask_Init(IWDG_HandlerType *IWDGx);
  UINT8_T IWDGTask_DeInit(IWDG_HandlerType *IWDGx);
  UINT8_T IWDGTask_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_TASK_H_ */