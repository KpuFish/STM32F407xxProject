#ifndef USART_TASK_H_
#define USART_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//===头文件定义
#include "usart_lib.h"

UINT8_T  USARTTask_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void));
UINT8_T  USARTTask_DeInit(USART_HandlerType*  USARTx);
UINT8_T  USARTTask_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTTask_ReadData8Bits(USART_HandlerType*USARTx);
UINT8_T  USARTTask_ReadInit(USART_HandlerType*  USARTx);
UINT8_T  USARTTask_GetReadState(USART_HandlerType* USARTx);
UINT8_T  USARTTask_ClearReadState(USART_HandlerType* USARTx);
UINT8_T  USARTTask_GetWriteState(USART_HandlerType* USARTx);
UINT8_T  USARTTask_ClearWriteState(USART_HandlerType* USARTx);
UINT8_T  USARTTask_TimeOVFTask(USART_HandlerType*USARTx);
UINT8_T  USARTTask_Read8BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTTask_Read16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTTask_ITWrite_TXETask(USART_HandlerType*USARTx);
UINT8_T  USARTTask_ITWrite_TCTask(USART_HandlerType*USARTx);
UINT8_T  USARTTask_AddWriteByte(USART_HandlerType*USARTx, UINT8_T val, UINT8_T isNeedID);
UINT8_T  USARTTask_AddWriteData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length, UINT8_T isNeedID);
UINT8_T  USARTTask_CRCTask(USART_HandlerType*USARTx, UINT16_T *pCount);
UINT8_T  USARTTask_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID);
UINT8_T  USARTTask_SendByte(USART_HandlerType*USARTx, UINT8_T  val);
UINT8_T  USARTTask_SendString(USART_HandlerType*USARTx, char *pVal);
UINT8_T  USARTTask_FuncTask(USART_HandlerType*USARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *));
//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_LIB_H_ */
