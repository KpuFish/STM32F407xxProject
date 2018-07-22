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
	UINT8_T _return = OK_0;
	_return= USART_Init(USARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, sysTickFunc);
	if (_return==OK_0)
	{
		if (CRCTask_Enable()!=OK_0)
		{
			//===CRC校验函数调用失败,之后的CRC标志设置为无校验位
			USARTx->msgRxHandler.msgCRCFlag = 0;
			USARTx->msgTxHandler.msgCRCFlag = 0;
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
UINT8_T  USARTLib_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	return USART_WriteData8Bits(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReadData8Bits(USART_HandlerType*USARTx)
{
	return USART_ReadData8Bits(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReadInit(USART_HandlerType*  USARTx)
{
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexW = 0;
	USARTx->msgRxHandler.msgIndexR = 0;

	USARTx->msgRxHandler.msgTaskState = 0;
	//---清零超时计数
	USARTx->msgNowTime = 0;
    
    return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetReadState(USART_HandlerType* USARTx)
{
	return USART_GetReadState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearReadState(USART_HandlerType* USARTx)
{
	return USART_ClearReadState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetWriteState(USART_HandlerType* USARTx)
{
	return USART_GetWriteState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearWriteState(USART_HandlerType* USARTx)
{
	return USART_ClearWriteState(USARTx);
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
UINT8_T  USARTLib_GetOVF(USART_HandlerType* USARTx)
{
	return USART_GetOVF(USARTx);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearOVF(USART_HandlerType* USARTx)
{
	return USART_ClearOVF(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeOVFTask(USART_HandlerType*USARTx)
{
	UINT8_T _return = OK_0;
	if ((USARTx->msgNowTime!=0)&&(USARTx->msgMaxTime!=0))
	{
		//---获取超时值
		_return = USARTLib_TimeTick_OVF(USARTx, USARTx->msgMaxTime);
		if (_return!=OK_0)
		{
			//---打印超时的串口信息
			USART_Printf(USARTx, "=>>接收串口%d发生超时错误!<<=\r\n", (USARTx->msgIndex - 1));
			//---复位接收数据缓存区
			USARTLib_ReadInit(USARTx);
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
UINT8_T  USARTLib_Read8BitsCount_Task(USART_HandlerType*USARTx,UINT8_T val )
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
						//---清零超时标志
						USARTLib_ClearOVF(USARTx);
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
UINT8_T  USARTLib_Read16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val)
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
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_WriteInit(USART_HandlerType*USARTx)
{
	//数据发送完成,清零发送数据长度
	USARTx->msgTxHandler.msgIndexW = 0;
	//---本次发送完成
	USARTx->msgTxHandler.msgTaskState = 1;
	//---缓存区序号归零处理
	USARTx->msgTxHandler.msgIndexR = 0;
	//---清空接收缓存区的数据
	//memset(USARTxHandlerType->msgTxHandler.pTxVal, 0x00, USARTxHandlerType->msgTxHandler.txSize);
	//---设置发送端口为输入模式(使用数据空寄存器，不能在这里将端口切换为输入模式)
	USARTLib_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ITWrite_TXETask(USART_HandlerType*USARTx)
{
	if ((USARTx->msgTxHandler.msgIndexW != 0)&&(USARTx->msgTxHandler.pMsgVal!=NULL))
	{
		if ((USARTx->msgTxHandler.msgIndexW - 1) != USARTx->msgTxHandler.msgIndexR)
		{
			//---发送8Bit的数据
			USARTLib_WriteData8Bits(USARTx, USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexR]);
			//---数据缓存区序号增加
			USARTx->msgTxHandler.msgIndexR++;
			//---校验缓存区是否溢出
			if (USARTx->msgTxHandler.msgIndexR > USARTx->msgTxHandler.msgSize)
			{
				USARTx->msgTxHandler.msgIndexR = 0;
			}
		}
		else
		{
			//===发送最后一组数据的处理---由于需要切换TX端口为输入状态，需要使用发送完成中断
			//---发送完成,发送数据寄存器空中断不使能
			USARTLib_EnableIT_TXE(USARTx, 0);
			//---利用发送完成中断实现发送端口从输出模式配置为输入模式
			//---使能发送完成中断---如果继续使用数据寄存器空中断，在步骤三的时候修改发送端口为输入状态，这样会导致最后一个数据的发送失败；这里采用使用发送完成中断
			USARTLib_EnableIT_TC(USARTx, 1);
			//---发送最后一组数据数据
			USARTLib_WriteData8Bits(USARTx, USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexR]);
		}
	}
	else
	{
		//---发送完成,发送数据寄存器空中断不使能---检查是否存在异常；关闭发送数据寄存器空中断
		USARTLib_EnableIT_TXE(USARTx, 0);
		//---清空数据发送缓存区
		USARTLib_WriteInit(USARTx);
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
UINT8_T  USARTLib_ITWrite_TCTask(USART_HandlerType*USARTx)
{
	USARTx->msgTxHandler.msgTaskState = 1;
	//---发送完成,发送数据发送完成中断不使能
	USARTLib_EnableIT_TC(USARTx, 0);
	//---清空数据发送缓存区
	USARTLib_WriteInit(USARTx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_AddWriteByte(USART_HandlerType*USARTx, UINT8_T val,UINT8_T isNeedID)
{
	if (USARTx->msgTxHandler.pMsgVal != NULL)
	{

		if (USARTx->msgTxHandler.msgIndexW>=USARTx->msgTxHandler.msgSize)
		{
			USARTx->msgTxHandler.msgIndexW=0;
		}
		if ((USARTx->msgTxHandler.msgIndexW==0)&&(isNeedID==1))
		{
			if (USARTx->msgTxHandler.msgSize < 0xFF)
			{
				USARTx->msgTxHandler.msgIndexW += 2;
			}
			else
			{
				USARTx->msgTxHandler.msgIndexW += 3;
			}
		}
		
		USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexW] = val;
		USARTx->msgTxHandler.msgIndexW++;

		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_AddWriteData(USART_HandlerType*USARTx,UINT8_T *pVal ,UINT16_T length, UINT8_T isNeedID)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i=0;i<length;i++)
	{
		_return = USARTLib_AddWriteByte(USARTx, pVal[i], isNeedID);
		//---判断数据是否填充正确
		if (_return!=OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 接收的数据进行处理，主要是校验信息
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_CRCTask(USART_HandlerType*USARTx,UINT16_T *pCount)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---接收数据的个数
	UINT16_T length = USARTx->msgRxHandler.msgIndexW;
	//---校验CRC是否初始化
	if (CRCTask_Enable()==OK_0)
	{
		//---判断数据校验模式
		if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算校验和
			crcVal = CRCTask_CheckSum(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC8校验值
			crcVal = CRCTask_CRC8(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			length -= 2;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 1];
				//---获取CRC16的低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---获取CRC16的低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC16校验值
			crcVal = CRCTask_CRC16(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			length -= 4;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = USARTx->msgRxHandler.pMsgVal[length - 1];
				//---获取CRC32的次高位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length];
				//---获取CRC32的次低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 1];
				//---获取CRC32的低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = USARTx->msgRxHandler.pMsgVal[length];
				//---获取CRC32的次高位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 1];
				//---获取CRC32的次低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---获取CRC32的低位值
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(USARTx->msgRxHandler.pMsgVal, length);
		}
		//---比对CRC的值
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	else
	{
		if (USARTx->msgRxHandler.msgSize < 250)
		{
			length += 2;
		}
		else
		{
			length += 3;
		}
	}
	*pCount = length;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_WriteSTART(USART_HandlerType*USARTx,UINT8_T isNeedID)
{
	//---等待传输完成
	while (USARTx->msgTxHandler.msgTaskState ==0)
	{
		WDT_RESET();
	}
	//---校验CRC是否初始化
	if (CRCTask_Enable()==OK_0)
	{
		UINT32_T crcVal = 0;
		//---判断数据校验模式
		if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)crcVal, isNeedID);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)crcVal, isNeedID);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)(crcVal >> 8), isNeedID);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)crcVal, isNeedID);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)(crcVal >> 24), isNeedID);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)(crcVal >> 16), isNeedID);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)(crcVal >> 8), isNeedID);
			USARTLib_AddWriteByte(USARTx, (UINT8_T)crcVal, isNeedID);
		}
	}
	//---判断填充的数据是否需要整理
	if (isNeedID==1)
	{
		//---填充报头和数据长度
		USARTx->msgTxHandler.pMsgVal[0] = USARTx->msgTxID;
		if (USARTx->msgTxHandler.msgSize < 0xFF)
		{
			USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)(USARTx->msgTxHandler.msgIndexW - 2);
		}
		else
		{
			USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)((USARTx->msgTxHandler.msgIndexW - 3) >> 8);
			USARTx->msgTxHandler.pMsgVal[2] = (UINT8_T)(USARTx->msgTxHandler.msgIndexW - 3);
		}
	}
	//---切换发送端口为输出模式
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
	//---发送数据寄存器空中断使能
	USARTLib_EnableIT_TXE(USARTx, 1);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_SendByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	return USART_SendByte(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_SendString(USART_HandlerType*USARTx, char *pVal)
{
	return USART_SendString(USARTx, pVal);
}
