#include "usart_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void))
{
	return USART_Init(USARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, sysTickFunc);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_DeInit(USART_HandlerType*  USARTx)
{
	return USART_DeInit(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_TXE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_TXE(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_TC(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_TC(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_RX(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_RX(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_IDLE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_IDLE(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput)
{
	return USART_GPIOInit(USARTx, isInput);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TransmitData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	return USART_TransmitData8Bits(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReceiveData8Bits(USART_HandlerType*USARTx)
{
	return USART_ReceiveData8Bits(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReceInit(USART_HandlerType*  USARTx)
{
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexR = 0;
	USARTx->msgRxHandler.msgIndexR = 0;

	USARTx->msgRxHandler.msgTaskState = 0;
	//---清零超时计数
	USARTx->msgNowTime = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetReceState(USART_HandlerType* USARTx)
{
	return USART_GetReceState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearReceState(USART_HandlerType* USARTx)
{
	return USART_ClearReceState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetSendState(USART_HandlerType* USARTx)
{
	return USART_GetSendState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearSendState(USART_HandlerType* USARTx)
{
	return USART_ClearSendState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeTick_Init(USART_HandlerType*USARTx) 
{
	return USART_TimeTick_Init(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut)
{
	return USART_TimeTick_OVF(USARTx,timeOut);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeTick_Task(USART_HandlerType*USARTx)
{
	UINT8_T _return = OK_0;
	if (USARTx->msgNowTime!=0)
	{
		//---获取超时值
		_return = USARTLib_TimeTick_OVF(USARTx, USARTx->msgMaxTime);
		if (_return!=OK_0)
		{
			//---打印超时的串口信息
			USART_Printf(USARTx, "接收串口%d发生超时错误!\r\n", (USARTx->msgIndex - 1));
			//---复位接收数据缓存区
			USARTLib_ReceInit(USARTx);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Rece8BitsCount_Task(USART_HandlerType*USARTx,UINT8_T val )
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---检查合法性
	if ((USARTx!=NULL)&&(USARTx->msgUSART!=NULL)&&(USARTx->msgRxHandler.pMsgVal!=NULL))
	{
		switch (USARTx->msgRxHandler.msgStep)
		{
			//---接收数据的报头
			case 0:
				if (USARTx->msgRxHandler.msgIndexW==0)
				{
					if (USARTx->msgRxID==tempVal)
					{
						USARTx->msgRxHandler.pMsgVal[0] = tempVal;
						USARTx->msgRxHandler.msgStep = 1;
						//---收到第一个符合格式的数据，启动超时计数器
						USARTLib_TimeTick_Init(USARTx);
					}
				}
				break;
			//---接收数据的长度
			case 1:
				if ((tempVal>0)&&(tempVal<(UINT8_T)(USARTx->msgRxHandler.msgSize&0xFF)))
				{
					USARTx->msgRxHandler.pMsgVal[1] = tempVal;
					USARTx->msgRxHandler.msgIndexR = tempVal;
					USARTx->msgRxHandler.msgStep = 2;
				}
				else
				{
					USARTx->msgRxHandler.msgStep = 0;
				}
				//---复位超时计数器
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 2:
				USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexW +2] = tempVal;
				USARTx->msgRxHandler.msgIndexW++;
				//---判断是否接收完成
				if (USARTx->msgRxHandler.msgIndexW>=USARTx->msgRxHandler.msgIndexR)
				{
					USARTx->msgRxHandler.msgStep = 3;
					USARTx->msgRxHandler.msgTaskState = 1;
				}
				//---复位超时计数器
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 3:
			case 4:
			default:
				USARTx->msgNowTime = 0;
				break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Rece16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val)
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---检查合法性
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL) && (USARTx->msgRxHandler.pMsgVal != NULL))
	{
		switch (USARTx->msgRxHandler.msgStep)
		{
			//---接收数据的报头
			case 0:
				if (USARTx->msgRxHandler.msgIndexW == 0)
				{
					if (USARTx->msgRxID == tempVal)
					{
						USARTx->msgRxHandler.pMsgVal[0] = tempVal;
						USARTx->msgRxHandler.msgStep = 1;
						//---收到第一个符合格式的数据，启动超时计数器
						USARTLib_TimeTick_Init(USARTx);
					}
				}
				break;
				//---接收数据的长度高位
			case 1:
				USARTx->msgRxHandler.pMsgVal[1] = tempVal;
				USARTx->msgRxHandler.msgIndexR = tempVal;
				USARTx->msgRxHandler.msgIndexR <<= 8;
				USARTx->msgRxHandler.msgStep = 2;
				//---复位超时计数器
				USARTLib_TimeTick_Init(USARTx);
				break;
				//---接收数据的长度低位
			case 2:
				USARTx->msgRxHandler.pMsgVal[2] = tempVal;
				USARTx->msgRxHandler.msgIndexR += tempVal;
				//---判断数据是否合法
				if ((USARTx->msgRxHandler.msgIndexR > 0) && (USARTx->msgRxHandler.msgIndexR < USARTx->msgRxHandler.msgSize ))
				{
					USARTx->msgRxHandler.msgStep = 3;
				}
				else
				{
					USARTx->msgRxHandler.msgStep = 0;
				}
				//---复位超时计数器
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 3:
				USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexW + 3] = tempVal;
				USARTx->msgRxHandler.msgIndexW++;
				//---判断是否接收完成
				if (USARTx->msgRxHandler.msgIndexW >= USARTx->msgRxHandler.msgIndexR)
				{
					USARTx->msgRxHandler.msgStep = 4;
					USARTx->msgRxHandler.msgTaskState = 1;
				}				//---复位超时计数器
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 4:
			case 5:
			default:
				USARTx->msgNowTime = 0;
				break;
		}
	}
}