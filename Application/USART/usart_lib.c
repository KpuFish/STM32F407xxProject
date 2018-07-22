#include "usart_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void))
{
	UINT8_T _return = OK_0;
	_return= USART_Init(USARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, sysTickFunc);
	if (_return==OK_0)
	{
		if (CRCTask_Enable()!=OK_0)
		{
			//===CRCУ�麯������ʧ��,֮���CRC��־����Ϊ��У��λ
			USARTx->msgRxHandler.msgCRCFlag = 0;
			USARTx->msgTxHandler.msgCRCFlag = 0;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_DeInit(USART_HandlerType*  USARTx)
{
	return USART_DeInit(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_TXE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_TXE(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_TC(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_TC(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_RX(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_RX(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_EnableIT_IDLE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	return USART_EnableIT_IDLE(USARTx, isEnable);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput)
{
	return USART_GPIOInit(USARTx, isInput);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	return USART_WriteData8Bits(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReadData8Bits(USART_HandlerType*USARTx)
{
	return USART_ReadData8Bits(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReadInit(USART_HandlerType*  USARTx)
{
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexW = 0;
	USARTx->msgRxHandler.msgIndexR = 0;

	USARTx->msgRxHandler.msgTaskState = 0;
	//---���㳬ʱ����
	USARTx->msgNowTime = 0;
    
    return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetReadState(USART_HandlerType* USARTx)
{
	return USART_GetReadState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearReadState(USART_HandlerType* USARTx)
{
	return USART_ClearReadState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetWriteState(USART_HandlerType* USARTx)
{
	return USART_GetWriteState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearWriteState(USART_HandlerType* USARTx)
{
	return USART_ClearWriteState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeTick_Init(USART_HandlerType*USARTx) 
{
	return USART_TimeTick_Init(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut)
{
	return USART_TimeTick_OVF(USARTx,timeOut);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetOVF(USART_HandlerType* USARTx)
{
	return USART_GetOVF(USARTx);
}


///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearOVF(USART_HandlerType* USARTx)
{
	return USART_ClearOVF(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_TimeOVFTask(USART_HandlerType*USARTx)
{
	UINT8_T _return = OK_0;
	if ((USARTx->msgNowTime!=0)&&(USARTx->msgMaxTime!=0))
	{
		//---��ȡ��ʱֵ
		_return = USARTLib_TimeTick_OVF(USARTx, USARTx->msgMaxTime);
		if (_return!=OK_0)
		{
			//---��ӡ��ʱ�Ĵ�����Ϣ
			USART_Printf(USARTx, "=>>���մ���%d������ʱ����!<<=\r\n", (USARTx->msgIndex - 1));
			//---��λ�������ݻ�����
			USARTLib_ReadInit(USARTx);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Read8BitsCount_Task(USART_HandlerType*USARTx,UINT8_T val )
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���Ϸ���
	if ((USARTx!=NULL)&&(USARTx->msgUSART!=NULL)&&(USARTx->msgRxHandler.pMsgVal!=NULL))
	{
		switch (USARTx->msgRxHandler.msgStep)
		{
			//---�������ݵı�ͷ
			case 0:
				if (USARTx->msgRxHandler.msgIndexW==0)
				{
					if (USARTx->msgRxID==tempVal)
					{
						USARTx->msgRxHandler.pMsgVal[0] = tempVal;
						USARTx->msgRxHandler.msgStep = 1;
						//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
						USARTLib_TimeTick_Init(USARTx);
						//---���㳬ʱ��־
						USARTLib_ClearOVF(USARTx);
					}
				}
				break;
			//---�������ݵĳ���
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
				//---��λ��ʱ������
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 2:
				USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexW +2] = tempVal;
				USARTx->msgRxHandler.msgIndexW++;
				//---�ж��Ƿ�������
				if (USARTx->msgRxHandler.msgIndexW>=USARTx->msgRxHandler.msgIndexR)
				{
					USARTx->msgRxHandler.msgStep = 3;
					USARTx->msgRxHandler.msgTaskState = 1;
				}
				//---��λ��ʱ������
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
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_Read16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���Ϸ���
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL) && (USARTx->msgRxHandler.pMsgVal != NULL))
	{
		switch (USARTx->msgRxHandler.msgStep)
		{
			//---�������ݵı�ͷ
			case 0:
				if (USARTx->msgRxHandler.msgIndexW == 0)
				{
					if (USARTx->msgRxID == tempVal)
					{
						USARTx->msgRxHandler.pMsgVal[0] = tempVal;
						USARTx->msgRxHandler.msgStep = 1;
						//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
						USARTLib_TimeTick_Init(USARTx);
					}
				}
				break;
				//---�������ݵĳ��ȸ�λ
			case 1:
				USARTx->msgRxHandler.pMsgVal[1] = tempVal;
				USARTx->msgRxHandler.msgIndexR = tempVal;
				USARTx->msgRxHandler.msgIndexR <<= 8;
				USARTx->msgRxHandler.msgStep = 2;
				//---��λ��ʱ������
				USARTLib_TimeTick_Init(USARTx);
				break;
				//---�������ݵĳ��ȵ�λ
			case 2:
				USARTx->msgRxHandler.pMsgVal[2] = tempVal;
				USARTx->msgRxHandler.msgIndexR += tempVal;
				//---�ж������Ƿ�Ϸ�
				if ((USARTx->msgRxHandler.msgIndexR > 0) && (USARTx->msgRxHandler.msgIndexR < USARTx->msgRxHandler.msgSize ))
				{
					USARTx->msgRxHandler.msgStep = 3;
				}
				else
				{
					USARTx->msgRxHandler.msgStep = 0;
				}
				//---��λ��ʱ������
				USARTLib_TimeTick_Init(USARTx);
				break;
			case 3:
				USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexW + 3] = tempVal;
				USARTx->msgRxHandler.msgIndexW++;
				//---�ж��Ƿ�������
				if (USARTx->msgRxHandler.msgIndexW >= USARTx->msgRxHandler.msgIndexR)
				{
					USARTx->msgRxHandler.msgStep = 4;
					USARTx->msgRxHandler.msgTaskState = 1;
				}				//---��λ��ʱ������
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_WriteInit(USART_HandlerType*USARTx)
{
	//���ݷ������,���㷢�����ݳ���
	USARTx->msgTxHandler.msgIndexW = 0;
	//---���η������
	USARTx->msgTxHandler.msgTaskState = 1;
	//---��������Ź��㴦��
	USARTx->msgTxHandler.msgIndexR = 0;
	//---��ս��ջ�����������
	//memset(USARTxHandlerType->msgTxHandler.pTxVal, 0x00, USARTxHandlerType->msgTxHandler.txSize);
	//---���÷��Ͷ˿�Ϊ����ģʽ(ʹ�����ݿռĴ��������������ｫ�˿��л�Ϊ����ģʽ)
	USARTLib_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ITWrite_TXETask(USART_HandlerType*USARTx)
{
	if ((USARTx->msgTxHandler.msgIndexW != 0)&&(USARTx->msgTxHandler.pMsgVal!=NULL))
	{
		if ((USARTx->msgTxHandler.msgIndexW - 1) != USARTx->msgTxHandler.msgIndexR)
		{
			//---����8Bit������
			USARTLib_WriteData8Bits(USARTx, USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexR]);
			//---���ݻ������������
			USARTx->msgTxHandler.msgIndexR++;
			//---У�黺�����Ƿ����
			if (USARTx->msgTxHandler.msgIndexR > USARTx->msgTxHandler.msgSize)
			{
				USARTx->msgTxHandler.msgIndexR = 0;
			}
		}
		else
		{
			//===�������һ�����ݵĴ���---������Ҫ�л�TX�˿�Ϊ����״̬����Ҫʹ�÷�������ж�
			//---�������,�������ݼĴ������жϲ�ʹ��
			USARTLib_EnableIT_TXE(USARTx, 0);
			//---���÷�������ж�ʵ�ַ��Ͷ˿ڴ����ģʽ����Ϊ����ģʽ
			//---ʹ�ܷ�������ж�---�������ʹ�����ݼĴ������жϣ��ڲ�������ʱ���޸ķ��Ͷ˿�Ϊ����״̬�������ᵼ�����һ�����ݵķ���ʧ�ܣ��������ʹ�÷�������ж�
			USARTLib_EnableIT_TC(USARTx, 1);
			//---�������һ����������
			USARTLib_WriteData8Bits(USARTx, USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexR]);
		}
	}
	else
	{
		//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
		USARTLib_EnableIT_TXE(USARTx, 0);
		//---������ݷ��ͻ�����
		USARTLib_WriteInit(USARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ITWrite_TCTask(USART_HandlerType*USARTx)
{
	USARTx->msgTxHandler.msgTaskState = 1;
	//---�������,�������ݷ�������жϲ�ʹ��
	USARTLib_EnableIT_TC(USARTx, 0);
	//---������ݷ��ͻ�����
	USARTLib_WriteInit(USARTx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_AddWriteData(USART_HandlerType*USARTx,UINT8_T *pVal ,UINT16_T length, UINT8_T isNeedID)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i=0;i<length;i++)
	{
		_return = USARTLib_AddWriteByte(USARTx, pVal[i], isNeedID);
		//---�ж������Ƿ������ȷ
		if (_return!=OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ���յ����ݽ��д�����Ҫ��У����Ϣ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_CRCTask(USART_HandlerType*USARTx,UINT16_T *pCount)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---�������ݵĸ���
	UINT16_T length = USARTx->msgRxHandler.msgIndexW;
	//---У��CRC�Ƿ��ʼ��
	if (CRCTask_Enable()==OK_0)
	{
		//---�ж�����У��ģʽ
		if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����У���
			crcVal = CRCTask_CheckSum(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC8У��ֵ
			crcVal = CRCTask_CRC8(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			length -= 2;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 1];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC16У��ֵ
			crcVal = CRCTask_CRC16(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			length -= 4;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length - 1];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 1];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 1];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 2];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = crcTemp << 8 + USARTx->msgRxHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(USARTx->msgRxHandler.pMsgVal, length);
		}
		//---�ȶ�CRC��ֵ
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_WriteSTART(USART_HandlerType*USARTx,UINT8_T isNeedID)
{
	//---�ȴ��������
	while (USARTx->msgTxHandler.msgTaskState ==0)
	{
		WDT_RESET();
	}
	//---У��CRC�Ƿ��ʼ��
	if (CRCTask_Enable()==OK_0)
	{
		UINT32_T crcVal = 0;
		//---�ж�����У��ģʽ
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
	//---�ж����������Ƿ���Ҫ����
	if (isNeedID==1)
	{
		//---��䱨ͷ�����ݳ���
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
	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
	//---�������ݼĴ������ж�ʹ��
	USARTLib_EnableIT_TXE(USARTx, 1);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_SendByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	return USART_SendByte(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USARTLib_SendString(USART_HandlerType*USARTx, char *pVal)
{
	return USART_SendString(USARTx, pVal);
}
