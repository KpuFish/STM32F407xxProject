#include "usart_cfg.h"

//===ȫ�ֱ�������
USART_HandlerType  g_USART1;
pUSART_HandlerType pUSART1=&g_USART1;

#ifdef USE_USART_PRINTF
	//---printf����ʹ�õĻ�����
	char printfBuffer[1024] = { 0 };
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_StructInit(USART_HandlerType*  USARTx)
{
	USARTx->msgIndex = 0;
	USARTx->msgRxID = 0;
	USARTx->msgTxID = 0;
	USARTx->msgOverFlow = 0;
	USARTx->msgNowTime = 0;
	USARTx->msgEndTime = 0;
	USARTx->msgMaxTime = 0;
	USARTx->msgTxBit = 0;
	USARTx->msgTxPort = NULL;
	USARTx->msgUSART = NULL;

	//---���ջ�����
	USARTx->msgRxHandler.msgCheckSum = 0;
	USARTx->msgRxHandler.msgCRCFlag = 0;
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexW = 0;
	USARTx->msgRxHandler.msgIndexR = 0;
	USARTx->msgRxHandler.msgCount = 0;
	USARTx->msgRxHandler.msgSize = 0;
	USARTx->msgTxHandler.msgTaskState = 0;
	USARTx->msgRxHandler.pMsgVal = NULL;

	//---���ͻ�����
	USARTx->msgTxHandler.msgCheckSum = 0;
	USARTx->msgTxHandler.msgCRCFlag = 0;
	USARTx->msgTxHandler.msgStep = 0;
	USARTx->msgTxHandler.msgIndexW = 0;
	USARTx->msgTxHandler.msgIndexR = 0;
	USARTx->msgTxHandler.msgCount = 0;
	USARTx->msgTxHandler.msgSize = 0;
	USARTx->msgTxHandler.msgTaskState = 1;
	USARTx->msgTxHandler.pMsgVal = NULL;

	//---������
	USARTx->msgFuncSysTick = NULL;
    return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal,UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal,UINT8_T txCRCFlag,UINT32_T (*sysTickFunc)(void))
{
	if (USARTx!=NULL)
	{
		USART_StructInit(USARTx);

		USARTx->msgRxHandler.msgCRCFlag = rxCRCFlag;
		USARTx->msgRxHandler.msgSize = rxSize;
		USARTx->msgRxHandler.pMsgVal = pRxVal;
		
		USARTx->msgTxHandler.msgCRCFlag = txCRCFlag;
		USARTx->msgTxHandler.msgSize = txSize;
		USARTx->msgTxHandler.pMsgVal = pTxVal;

		//---ע���������
		USARTx->msgFuncSysTick = sysTickFunc;

		//---�ж��˿ڵĶ���
		if ((USARTx == pUSART1) && (pUSART1 != NULL))
		{
			USART1_Init(USARTx);
		}
		return OK_0;
	}
	return ERROR_1;
}


///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ����STM32������Ч������AVR������Ч
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_EnableIT_TXE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	#ifdef USE_MCU_STM32
		if ((USARTx!=NULL)&&(USARTx->msgUSART!=NULL))
		{
			if (isEnable!=0)
			{
				LL_USART_EnableIT_TXE(USARTx->msgUSART);
			}
			else
			{
				LL_USART_DisableIT_TXE(USARTx->msgUSART);
			}
		}
		else
		{
			return ERROR_1;
		}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT32_T USART_IsEnabledIT_TXE(USART_HandlerType*  USARTx)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_IsEnabledIT_TXE(USARTx->msgUSART);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT32_T USART_IsActiveFlag_TXE(USART_HandlerType*  USARTx)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_IsActiveFlag_TXE(USARTx->msgUSART);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_EnableIT_TC(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		if (isEnable != 0)
		{
			LL_USART_EnableIT_TC(USARTx->msgUSART);
		}
		else
		{
			LL_USART_DisableIT_TC(USARTx->msgUSART);
		}
	}
	else
	{
		return ERROR_1;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT32_T USART_IsEnabledIT_TC(USART_HandlerType*  USARTx)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_IsEnabledIT_TC(USARTx->msgUSART);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT32_T USART_IsActiveFlag_TC(USART_HandlerType*  USARTx)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_IsActiveFlag_TC(USARTx->msgUSART);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearFlag_TC(USART_HandlerType*  USARTx)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		LL_USART_ClearFlag_TC(USARTx->msgUSART);
	}
	else
	{
		return ERROR_1;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_EnableIT_RX(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
#ifdef USE_MCU_STM32
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		if (isEnable != 0)
		{
			LL_USART_EnableIT_RXNE(USARTx->msgUSART);
		}
		else
		{
			LL_USART_DisableIT_RXNE(USARTx->msgUSART);
		}
	}
	else
	{
		return ERROR_1;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ����STM32������Ч������AVR������Ч
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_EnableIT_IDLE(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	#ifdef USE_MCU_STM32
		if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
		{
			if (isEnable != 0)
			{
				LL_USART_EnableIT_IDLE(USARTx->msgUSART);
			}
			else
			{
				LL_USART_DisableIT_IDLE(USARTx->msgUSART);
			}
		}
		else
		{
			return ERROR_1;
		}
	#endif
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		if (isInput==USART_TXGPIO_SET_OUTPUT)
		{
			#ifdef USE_MCU_STM32
				/*
				#ifdef USE_MCU_STM32F1
					//---F1��F4�Ķ˿����ò�̫һ��
					LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_ALTERNATE);
				#else
					LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_OUTPUT);
				#endif
				*/
				LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_ALTERNATE);
			#else
				USARTxHandlerType->msgUSART->UCSRB |= (1 << USART_TXEN);
			#endif 
		}
		else
		{
			#ifdef USE_MCU_STM32
				LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_INPUT);
			#else
				USARTxHandlerType->msgUSART->UCSRB |= (1 << USART_TXEN);
			#endif 
		}
	}
	else
	{
		return ERROR_1;
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
UINT8_T USART_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		//---��������
		LL_USART_TransmitData8(USARTx->msgUSART, val);
	}
	else
	{
		return ERROR_1;
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
UINT8_T USART_ReadData8Bits(USART_HandlerType*USARTx)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_ReceiveData8(USARTx->msgUSART);
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
UINT8_T USART_EnableCRC_RX(USART_HandlerType*USARTx,UINT8_T crcFlag)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		USARTx->msgRxHandler.msgCRCFlag = crcFlag;
	}
	else 
	{
		return ERROR_1;
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
UINT8_T USART_GetCRC_RX(USART_HandlerType*USARTx)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return  USARTx->msgRxHandler.msgCRCFlag;
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
UINT8_T USART_EnableCRC_TX(USART_HandlerType*USARTx, UINT8_T crcFlag)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		USARTx->msgTxHandler.msgCRCFlag = crcFlag;
	}
	else
	{
		return ERROR_1;
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
UINT8_T USART_GetCRC_TX(USART_HandlerType*USARTx)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return  USARTx->msgTxHandler.msgCRCFlag;
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
UINT8_T USART_TimeTick_Init(USART_HandlerType*USARTx)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		if (USARTx->msgFuncSysTick != NULL)
		{
			USARTx->msgNowTime = USARTx->msgFuncSysTick();
		}
		else
		{
			USARTx->msgNowTime = 0;
		}
		//---ͬ��ʱ��
		USARTx->msgEndTime = USARTx->msgNowTime;
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ʱ������Ƿ�����ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		//---��ȡ��ǰʱ��
		if (USARTx->msgFuncSysTick != NULL)
		{
			USARTx->msgEndTime = USARTx->msgFuncSysTick() + 2;
		}
		else
		{
			USARTx->msgEndTime = 0;
		}
		//---�ж��Ƿ�����ʱ����
		if ((USARTx->msgEndTime - USARTx->msgNowTime) > timeOut)
		{
			USARTx->msgOverFlow = 1;
			return ERROR_1;
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
UINT8_T USART_SendByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	//---��������
	USART_WriteData8Bits(USARTx, val);
	//---�ȴ��������
	while (USART_IsActiveFlag_TC(USARTx) == RESET)
	{
		WDT_RESET();
	}
	//---���������ɱ�־λ
	USART_ClearFlag_TC(USARTx);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� �����ַ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_SendString(USART_HandlerType*USARTx, char *pVal)
{
	while (*pVal != '\0')
	{
		USART_SendByte(USARTx, (UINT8_T)*pVal);
		pVal++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetOVF(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		return USARTx->msgOverFlow;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��������־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearOVF(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		USARTx->msgOverFlow = 0;
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
UINT8_T USART_GetReadState(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		return USARTx->msgRxHandler.msgTaskState;
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
UINT8_T USART_ClearReadState(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		USARTx->msgRxHandler.msgTaskState=0;
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
UINT8_T USART_GetWriteState(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		return USARTx->msgTxHandler.msgTaskState;
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
UINT8_T USART_ClearWriteState(USART_HandlerType* USARTx)
{
	if (USARTx != NULL)
	{
		USARTx->msgTxHandler.msgTaskState = 0;
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
void USART_Printf(USART_HandlerType*USARTx, char*fmt, ...)
{
	#ifdef USE_USART_PRINTF
		//---��鷢�ͼĴ������ж��Ƿ�ʹ��
		if (USART_IsEnabledIT_TXE(USARTx))
		{
			//---�ȴ��������
			while (USART_IsActiveFlag_TXE(USARTx) != RESET)
			{
				WDT_RESET();
			}
		}
		//---��鷢������ж�
		if (USART_IsEnabledIT_TC(USARTx))
		{
			//---�ȴ��������
			while ((USART_IsActiveFlag_TC(USARTx) != RESET)&&(USARTx->msgTxHandler.msgStep==0))
			{
				WDT_RESET();
			}
			USART_ClearFlag_TC(USARTx);
		}
		//---�л����Ͷ˿�Ϊ���ģʽ
		USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
		//---��������
		UINT16_T length = 0, i = 0;
		va_list arg_ptr;
		va_start(arg_ptr, fmt);
		//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
		length = vsnprintf(printfBuffer, 1024, fmt, arg_ptr);
		va_end(arg_ptr);
		//---���ݷ���
		for (i = 0; i < length; i++)
		{
			USART_SendByte(USARTx, printfBuffer[i]);
		}
		//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
		USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	#endif
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable)
{
	#ifdef USE_MCU_STM32
		if (USARTx == USART1)
		{
			if (isEnable)
			{
				//---ʹ��USART1��ʱ���ź�
				LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
			}
			else
			{
				//---��ʹ��USART1��ʱ���ź�
				LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
			}
			return OK_0;
		}
		if (USARTx == USART2)
		{
			if (isEnable)
			{
				//---ʹ��USART2��ʱ���ź�
				LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
			}
			else
			{
				//---��ʹ��USART2��ʱ���ź�
				LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
			}
			return OK_0;
		}
		#if defined(USART3)
			if (USARTx == USART3)
			{
				if (isEnable)
				{
					//---ʹ��USART3��ʱ���ź�
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
				}
				else
				{
					//---��ʹ��USART3��ʱ���ź�
					LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
				}
				return OK_0;
			}
		#endif /* USART3 */
		#if defined(USART6)
			if (USARTx == USART6)
			{
				if (isEnable)
				{
					//---ʹ��USART6��ʱ���ź�
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
				}
				else
				{
					//---��ʹ��USART6��ʱ���ź�
					LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
				}
				return OK_0;
			}
		#endif /* USART6 */
		#if defined(UART4)
			if (USARTx == UART4)
			{
				if (isEnable)
				{
					//---ʹ��USART4��ʱ���ź�
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
				}
				else
				{
					//---��ʹ��USART4��ʱ���ź�
					LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
				}
				return OK_0;
			}
		#endif /* UART4 */
		#if defined(UART5)
			if (USARTx == UART5)
			{
				if (isEnable)
				{
					//---ʹ��USART5��ʱ���ź�
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
				}
				else
				{
					//---��ʹ��USART5��ʱ���ź�
					LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
				}
				return OK_0;
			}
		#endif /* UART5 */
		#if defined(UART7)
			if (USARTx == UART7)
			{
				if (isEnable)
				{
					//---ʹ��USART7��ʱ���ź�
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
				}
				else
				{
					//---��ʹ��USART7��ʱ���ź�
					LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
				}
				return OK_0;
			}
		#endif /* UART7 */
		#if defined(UART8)
			if (USARTx == UART8)
			{
				if (isEnable)
				{
					//---ʹ��USART8��ʱ���ź�
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
				}
				else
				{
					//---��ʹ��USART8��ʱ���ź�
					LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
				}
				return OK_0;
			}
		#endif /* UART8 */
		#if defined(UART9)
			if (USARTx == UART9)
			{
				if (isEnable)
				{
					//---ʹ��USART9��ʱ���ź�
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
				}
				else
				{
					//---��ʹ��USART9��ʱ���ź�
					LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
				}
				return OK_0;
			}
		#endif /* UART9 */
		#if defined(UART10)
			if (USARTx == UART10)
			{
				if (isEnable)
				{
					//---ʹ��USART10��ʱ���ź�
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
				}
				else
				{
					//---��ʹ��USART10��ʱ���ź�
					LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
				}
				return OK_0;
			}
		#endif /* UART10 */
	#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeInit(USART_HandlerType*USARTx)
{
	#ifdef USE_MCU_STM32
		if ((USARTx != NULL)&&(USARTx->msgUSART!=NULL))
		{
			LL_USART_DeInit(USARTx->msgUSART);
			USART_Clock(USARTx->msgUSART, 0);
		}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Init(USART_HandlerType*USARTx)
{
	#ifdef USE_MCU_STM32
		//---USART1 GPIO Configuration
		//---PA9  ------> USART1_TX---�˿ڸ���Ϊ7
		//---PA10 ------> USART1_RX---�˿ڸ���Ϊ7
		//---ʹ�ܶ˿�ʱ��
		GPIOTask_Clock(GPIOA, 1);
		//---GPIO�Ľṹ��
		LL_GPIO_InitTypeDef GPIO_InitStruct;
		//---ģʽ����
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		//---�����ٶ�
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
		//---���ù��ܵ��������
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		//---��������ʹ��
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		#ifdef USE_MCU_STM32F1
			//---TX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			//---RX
			GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#else
			//---�˿ں�
			GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
			//---���ù���ΪUSART1
			GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#endif
		//---ע�����ڵĳ�ʼ��
		LL_USART_DeInit(USART1);
		//---ʹ��USART1��ʱ���ź�
		USART_Clock(USART1, 1);
		//---USART�Ľӿڽṹ��
		LL_USART_InitTypeDef USART_InitStruct;
		//---������
		USART_InitStruct.BaudRate = 115200;
		//---����λ
		USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
		//---ֹͣλ
		USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
		//---У��λ
		USART_InitStruct.Parity = LL_USART_PARITY_NONE;
		//---����Ϊ�շ�ģʽ
		USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
		//---Ӳ��������---Ĭ��Ϊ��
		USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
		//---����������
		#if defined(USART_CR1_OVER8)
			//---����������---Ĭ������Ϊ16
			USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
		#endif
		//---��ʼ������
		LL_USART_Init(USART1, &USART_InitStruct);
		//---�����첽ģʽ����
		LL_USART_ConfigAsyncMode(USART1);
		//---USART1_IRQ�ж�����---�жϵȼ�����
		NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
		//---ʹ���ж�
		NVIC_EnableIRQ(USART1_IRQn);
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(USART1);
		//---ʹ�ܴ���
		LL_USART_Enable(USART1);
		//---�����־λ
		USART1->SR = 0;
		//---������Ϣ�ṹ���е���Ϣ
		USARTx->msgTxPort = GPIOA;
		USARTx->msgTxBit = LL_GPIO_PIN_9;
		USARTx->msgUSART = USART1;
	#else
		#error "���ڳ�ʼ����ʽΪ��֧�ֵ�MCU!"
	#endif
	USARTx->msgIndex = 1 + 1;
	//---У���Ƿ���Ҫ��ʱ����
	if (USARTx->msgFuncSysTick!=NULL)
	{
		USARTx->msgMaxTime = 100;
	}
	else
	{
		USARTx->msgMaxTime = 0;
	}
	//---���ñ�ͷ�ͱ�β
	USARTx->msgRxID = 0x55;
	USARTx->msgTxID = 0x5A;
	//---����TX�˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	//---��ӡ��ʼ����Ϣ
	USART_Printf(USARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	return OK_0;
}