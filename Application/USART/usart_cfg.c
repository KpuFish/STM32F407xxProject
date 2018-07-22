#include "usart_cfg.h"

//===全局变量定义
USART_HandlerType  g_USART1;
pUSART_HandlerType pUSART1=&g_USART1;

#ifdef USE_USART_PRINTF
	//---printf函数使用的缓存区
	char printfBuffer[1024] = { 0 };
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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

	//---接收缓存区
	USARTx->msgRxHandler.msgCheckSum = 0;
	USARTx->msgRxHandler.msgCRCFlag = 0;
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexW = 0;
	USARTx->msgRxHandler.msgIndexR = 0;
	USARTx->msgRxHandler.msgCount = 0;
	USARTx->msgRxHandler.msgSize = 0;
	USARTx->msgTxHandler.msgTaskState = 0;
	USARTx->msgRxHandler.pMsgVal = NULL;

	//---发送缓存区
	USARTx->msgTxHandler.msgCheckSum = 0;
	USARTx->msgTxHandler.msgCRCFlag = 0;
	USARTx->msgTxHandler.msgStep = 0;
	USARTx->msgTxHandler.msgIndexW = 0;
	USARTx->msgTxHandler.msgIndexR = 0;
	USARTx->msgTxHandler.msgCount = 0;
	USARTx->msgTxHandler.msgSize = 0;
	USARTx->msgTxHandler.msgTaskState = 1;
	USARTx->msgTxHandler.pMsgVal = NULL;

	//---计数器
	USARTx->msgFuncSysTick = NULL;
    return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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

		//---注册计数函数
		USARTx->msgFuncSysTick = sysTickFunc;

		//---判读端口的定义
		if ((USARTx == pUSART1) && (pUSART1 != NULL))
		{
			USART1_Init(USARTx);
		}
		return OK_0;
	}
	return ERROR_1;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 对于STM32这项有效，对于AVR这项无效
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 对于STM32这项有效，对于AVR这项无效
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
					//---F1和F4的端口配置不太一样
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		//---发送数据
		LL_USART_TransmitData8(USARTx->msgUSART, val);
	}
	else
	{
		return ERROR_1;
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
UINT8_T USART_ReadData8Bits(USART_HandlerType*USARTx)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		return LL_USART_ReceiveData8(USARTx->msgUSART);
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
		//---同步时钟
		USARTx->msgEndTime = USARTx->msgNowTime;
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 时间计数是否发生超时
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut)
{
	if ((USARTx != NULL) && (USARTx->msgUSART != NULL))
	{
		//---获取当前时间
		if (USARTx->msgFuncSysTick != NULL)
		{
			USARTx->msgEndTime = USARTx->msgFuncSysTick() + 2;
		}
		else
		{
			USARTx->msgEndTime = 0;
		}
		//---判断是否发生超时错误
		if ((USARTx->msgEndTime - USARTx->msgNowTime) > timeOut)
		{
			USARTx->msgOverFlow = 1;
			return ERROR_1;
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
UINT8_T USART_SendByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	//---发送数据
	USART_WriteData8Bits(USARTx, val);
	//---等待发送完成
	while (USART_IsActiveFlag_TC(USARTx) == RESET)
	{
		WDT_RESET();
	}
	//---清除发送完成标志位
	USART_ClearFlag_TC(USARTx);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 发送字符串
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 获取溢出标志
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 清除溢出标志
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
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
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
void USART_Printf(USART_HandlerType*USARTx, char*fmt, ...)
{
	#ifdef USE_USART_PRINTF
		//---检查发送寄存器空中断是否使能
		if (USART_IsEnabledIT_TXE(USARTx))
		{
			//---等待发送完成
			while (USART_IsActiveFlag_TXE(USARTx) != RESET)
			{
				WDT_RESET();
			}
		}
		//---检查发送完成中断
		if (USART_IsEnabledIT_TC(USARTx))
		{
			//---等待发送完成
			while ((USART_IsActiveFlag_TC(USARTx) != RESET)&&(USARTx->msgTxHandler.msgStep==0))
			{
				WDT_RESET();
			}
			USART_ClearFlag_TC(USARTx);
		}
		//---切换发送端口为输出模式
		USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
		//---计算数据
		UINT16_T length = 0, i = 0;
		va_list arg_ptr;
		va_start(arg_ptr, fmt);
		//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
		length = vsnprintf(printfBuffer, 1024, fmt, arg_ptr);
		va_end(arg_ptr);
		//---数据发送
		for (i = 0; i < length; i++)
		{
			USART_SendByte(USARTx, printfBuffer[i]);
		}
		//---数据发送完成，切换端口为输入模式
		USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	#endif
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable)
{
	#ifdef USE_MCU_STM32
		if (USARTx == USART1)
		{
			if (isEnable)
			{
				//---使能USART1的时钟信号
				LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
			}
			else
			{
				//---不使能USART1的时钟信号
				LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
			}
			return OK_0;
		}
		if (USARTx == USART2)
		{
			if (isEnable)
			{
				//---使能USART2的时钟信号
				LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
			}
			else
			{
				//---不使能USART2的时钟信号
				LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
			}
			return OK_0;
		}
		#if defined(USART3)
			if (USARTx == USART3)
			{
				if (isEnable)
				{
					//---使能USART3的时钟信号
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
				}
				else
				{
					//---不使能USART3的时钟信号
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
					//---使能USART6的时钟信号
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
				}
				else
				{
					//---不使能USART6的时钟信号
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
					//---使能USART4的时钟信号
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
				}
				else
				{
					//---不使能USART4的时钟信号
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
					//---使能USART5的时钟信号
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
				}
				else
				{
					//---不使能USART5的时钟信号
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
					//---使能USART7的时钟信号
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
				}
				else
				{
					//---不使能USART7的时钟信号
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
					//---使能USART8的时钟信号
					LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
				}
				else
				{
					//---不使能USART8的时钟信号
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
					//---使能USART9的时钟信号
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
				}
				else
				{
					//---不使能USART9的时钟信号
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
					//---使能USART10的时钟信号
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
				}
				else
				{
					//---不使能USART10的时钟信号
					LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
				}
				return OK_0;
			}
		#endif /* UART10 */
	#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Init(USART_HandlerType*USARTx)
{
	#ifdef USE_MCU_STM32
		//---USART1 GPIO Configuration
		//---PA9  ------> USART1_TX---端口复用为7
		//---PA10 ------> USART1_RX---端口复用为7
		//---使能端口时钟
		GPIOTask_Clock(GPIOA, 1);
		//---GPIO的结构体
		LL_GPIO_InitTypeDef GPIO_InitStruct;
		//---模式配置
		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		//---工作速度
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
		//---复用功能的推完输出
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		//---输入上拉使能
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
			//---端口号
			GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
			//---复用功能为USART1
			GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
			LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#endif
		//---注销串口的初始化
		LL_USART_DeInit(USART1);
		//---使能USART1的时钟信号
		USART_Clock(USART1, 1);
		//---USART的接口结构体
		LL_USART_InitTypeDef USART_InitStruct;
		//---波特率
		USART_InitStruct.BaudRate = 115200;
		//---数据位
		USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
		//---停止位
		USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
		//---校验位
		USART_InitStruct.Parity = LL_USART_PARITY_NONE;
		//---配置为收发模式
		USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
		//---硬件流控制---默认为无
		USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
		//---过采样配置
		#if defined(USART_CR1_OVER8)
			//---过采样次数---默认配置为16
			USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
		#endif
		//---初始化串口
		LL_USART_Init(USART1, &USART_InitStruct);
		//---串口异步模式配置
		LL_USART_ConfigAsyncMode(USART1);
		//---USART1_IRQ中断配置---中断等级配置
		NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
		//---使能中断
		NVIC_EnableIRQ(USART1_IRQn);
		//---使能接收中断
		LL_USART_EnableIT_RXNE(USART1);
		//---使能串口
		LL_USART_Enable(USART1);
		//---清除标志位
		USART1->SR = 0;
		//---配置消息结构体中的信息
		USARTx->msgTxPort = GPIOA;
		USARTx->msgTxBit = LL_GPIO_PIN_9;
		USARTx->msgUSART = USART1;
	#else
		#error "串口初始化格式为不支持的MCU!"
	#endif
	USARTx->msgIndex = 1 + 1;
	//---校验是否需要超时函数
	if (USARTx->msgFuncSysTick!=NULL)
	{
		USARTx->msgMaxTime = 100;
	}
	else
	{
		USARTx->msgMaxTime = 0;
	}
	//---配置报头和保尾
	USARTx->msgRxID = 0x55;
	USARTx->msgTxID = 0x5A;
	//---设置TX端口为输入模式
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	//---打印初始化信息
	USART_Printf(USARTx, "=>>串口1的初始化<<=\r\n");
	return OK_0;
}