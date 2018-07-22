#ifndef USART_LIB_H_
#define USART_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//===头文件定义
#include "usart_cfg.h"
#include "crc_task.h"

UINT8_T  USARTLib_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void));
UINT8_T  USARTLib_DeInit(USART_HandlerType*  USARTx);
UINT8_T  USARTLib_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTLib_ReadData8Bits(USART_HandlerType*USARTx);
UINT8_T  USARTLib_ReadInit(USART_HandlerType*  USARTx);
UINT8_T  USARTLib_GetReadState(USART_HandlerType* USARTx);
UINT8_T  USARTLib_ClearReadState(USART_HandlerType* USARTx);
UINT8_T  USARTLib_GetWriteState(USART_HandlerType* USARTx);
UINT8_T  USARTLib_ClearWriteState(USART_HandlerType* USARTx);
UINT8_T  USARTLib_TimeOVFTask(USART_HandlerType*USARTx);
UINT8_T  USARTLib_Read8BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTLib_Read16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USARTLib_WriteInit(USART_HandlerType*USARTx);
UINT8_T  USARTLib_ITWrite_TXETask(USART_HandlerType*USARTx);
UINT8_T  USARTLib_ITWrite_TCTask(USART_HandlerType*USARTx);
UINT8_T  USARTLib_AddWriteByte(USART_HandlerType*USARTx, UINT8_T val, UINT8_T isNeedID);
UINT8_T  USARTLib_AddWriteData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length, UINT8_T isNeedID);
UINT8_T USARTLib_CRCTask(USART_HandlerType*USARTx, UINT16_T *pCount);
UINT8_T  USARTLib_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID);
UINT8_T  USARTLib_SendByte(USART_HandlerType*USARTx, UINT8_T  val);
UINT8_T  USARTLib_SendString(USART_HandlerType*USARTx, char *pVal);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_LIB_H_ */
