#ifndef IWDG_LIB_H_
#define IWDG_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//---����ʹ�õ�ͷ�ļ�
#include "iwdg_cfg.h"

//---�ⲿ���ýӿ�
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---��������
UINT8_T IWDGLib_Init(IWDG_HandlerType *IWDGx);
UINT8_T IWDGLib_DeInit(IWDG_HandlerType *IWDGx);
UINT8_T IWDGLib_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_LIB_H_ */