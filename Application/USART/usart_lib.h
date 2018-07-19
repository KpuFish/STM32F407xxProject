#ifndef USART_LIB_H_
#define USART_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//===头文件定义
#include "usart_cfg.h"
#include "crc_task.h"

UINT8_T  USARTLib_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void));
UINT8_T  USARTLib_DeInit(USART_HandlerType*  USARTx);
UINT8_T  USARTLib_TransmitData8Bits(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTLib_ReceiveData8Bits(USART_HandlerType*USARTx);
UINT8_T  USARTLib_Rece8BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTLib_Rece16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_LIB_H_ */
