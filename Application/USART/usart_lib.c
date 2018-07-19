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
	return USART_Init(USARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, sysTickFunc);
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
UINT8_T  USARTLib_TransmitData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	return USART_TransmitData8Bits(USARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReceiveData8Bits(USART_HandlerType*USARTx)
{
	return USART_ReceiveData8Bits(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ReceInit(USART_HandlerType*  USARTx)
{
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexR = 0;
	USARTx->msgRxHandler.msgIndexR = 0;

	USARTx->msgRxHandler.msgTaskState = 0;
	//---���㳬ʱ����
	USARTx->msgNowTime = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetReceState(USART_HandlerType* USARTx)
{
	return USART_GetReceState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearReceState(USART_HandlerType* USARTx)
{
	return USART_ClearReceState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_GetSendState(USART_HandlerType* USARTx)
{
	return USART_GetSendState(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USARTLib_ClearSendState(USART_HandlerType* USARTx)
{
	return USART_ClearSendState(USARTx);
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
UINT8_T  USARTLib_TimeTick_Task(USART_HandlerType*USARTx)
{
	UINT8_T _return = OK_0;
	if (USARTx->msgNowTime!=0)
	{
		//---��ȡ��ʱֵ
		_return = USARTLib_TimeTick_OVF(USARTx, USARTx->msgMaxTime);
		if (_return!=OK_0)
		{
			//---��ӡ��ʱ�Ĵ�����Ϣ
			USART_Printf(USARTx, "���մ���%d������ʱ����!\r\n", (USARTx->msgIndex - 1));
			//---��λ�������ݻ�����
			USARTLib_ReceInit(USARTx);
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
UINT8_T  USARTLib_Rece8BitsCount_Task(USART_HandlerType*USARTx,UINT8_T val )
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
UINT8_T  USARTLib_Rece16BitsCount_Task(USART_HandlerType*USARTx, UINT8_T val)
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
}