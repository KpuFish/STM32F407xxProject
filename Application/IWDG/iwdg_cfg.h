#ifndef IWDG_CFG_H_
#define IWDG_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//---定义使用的头文件
#include "complier_lib.h"
//---结构体定义
struct _IWDG_HandlerType
{
	IWDG_TypeDef *msgIWDGx;
};
//---结构体命名
typedef struct _IWDG_HandlerType			IWDG_HandlerType;
//---结构体指针
typedef struct _IWDG_HandlerType			*pIWDG_HandlerType;
//---外部调用接口
extern IWDG_HandlerType		g_IWDG;
extern pIWDG_HandlerType	pIWDG;

//---函数定义
 UINT8_T IWDG_Init(IWDG_HandlerType *IWDGx);
 UINT8_T IWDG_DeInit(IWDG_HandlerType *IWDGx);
 UINT8_T IWDG_Reset(IWDG_HandlerType *IWDGx);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_CFG_H_ */