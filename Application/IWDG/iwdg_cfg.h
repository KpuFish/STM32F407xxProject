#ifndef IWDG_CFG_H_
#define IWDG_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//---����ʹ�õ�ͷ�ļ�
#include "complier_lib.h"
//---�ṹ�嶨��
struct _IWDG_HandlerType
{
	IWDG_TypeDef *msgIWDGx;
};
//---�ṹ������
typedef struct _IWDG_HandlerType			IWDG_HandlerType;
//---�ṹ��ָ��
typedef struct _IWDG_HandlerType			*pIWDG_HandlerType;
//---�ⲿ���ýӿ�
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---��������
 UINT8_T IWDG_Init(IWDG_HandlerType *IWDGx);
 UINT8_T IWDG_DeInit(IWDG_HandlerType *IWDGx);
 UINT8_T IWDG_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_CFG_H_ */