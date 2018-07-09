#ifndef CRC_CFG_H_
#define CRC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
//---消息结构体
typedef struct  _CRC_HandlerType				CRC_HandlerType;
//---指针消息结构体
typedef struct  _CRC_HandlerType				*pCRC_HandlerType;
//---结构定义
struct _CRC_HandlerType
{
	UINT32_T(*msg8BitsTask)(UINT8_T *pVal, UINT32_T length);
	UINT32_T(*msg32BitsTask)(UINT32_T *pVal, UINT32_T length);
};

//---提供外部调用的结构
extern CRC_HandlerType g_CRC;
extern pCRC_HandlerType pCRC;

//---函数定义
void CRC32_Init(UINT8_T isHW);
void CRC32_DeInit(UINT8_T isHW);
UINT32_T CRC32_HWGetCalc8BitsData(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC32_HWGetCalc323BitsData(UINT32_T *pVal, UINT32_T length);
UINT32_T CRC32_SWGetCalc8BitsData(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC32_SWGetCalc32BitsData(UINT32_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CRC_CFG_H_ */