#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_HandlerType_Init(I2C_HandlerType *I2CxHandlerType)
{
	/*
	I2CxHandlerType->msgPluseWidth = 0;
	I2CxHandlerType->msgDelay = NULL;
	I2CxHandlerType->msgAddr = 0;
	I2CxHandlerType->msgClockSpeed = 0;
	I2CxHandlerType->msgTask = NULL;
	*/
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2CxHandlerType, void(*msgDelay)(UINT32_T delay))
{
	#ifdef USE_MCU_STM32

	//---使能GPIO的时钟
	GPIOTask_Clock(I2CxHandlerType->msgSclPort, 1);
	GPIOTask_Clock(I2CxHandlerType->msgSdaPort, 1);

	//---SCL和SDA端口输出高电平
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2CxHandlerType->msgSclBit;				//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;				//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;					//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉

	//---SCL的初始化
	LL_GPIO_Init(I2CxHandlerType->msgSclPort, &GPIO_InitStruct);

	//---SDA的初始化
	GPIO_InitStruct.Pin = I2CxHandlerType->msgSdaBit;
	LL_GPIO_Init(I2CxHandlerType->msgSdaPort, &GPIO_InitStruct);
	#endif

	//---设置使用的延时函数
	if (msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay = msgDelay;
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
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2CxHandlerType)
{
	//---端口设置为输入模式
	I2C_SCL_READ(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_READ(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---SCL和SDA端口输出高电平
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---注销任务函数
	if (I2CxHandlerType->msgTask != NULL)
	{
		I2CxHandlerType->msgTask = NULL;
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
UINT8_T I2C_MSW_START(I2C_HandlerType *I2CxHandlerType)
{
	//---发送起始条件的数据信号
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---发送起始信号;
	I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---0；失败SDA---1
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) != OK_0)
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
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2CxHandlerType)
{
	//---发送停止条件的数据信号
	I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---1；失败SDA---0
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) == OK_0)
	{
		return ERROR_1;
	}
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2CxHandlerType)
{
	I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2CxHandlerType)
{
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T _return = OK_0;

	//---读取应答信号
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---延时等待
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---读取SDA的状态信号---ACK状态下SDA为低电平
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) != OK_0)
	{
		_return = ERROR_1;
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T i = 0;

	//---读取应答信号
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---等待应答信号
	for (i = 255; i > 0; i--)
	{
		//---读取SDA的状态
		if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit))
		{
			break;
		}
	}
	if (i == 0)
	{
		I2C_MSW_STOP(I2CxHandlerType);
		return ERROR_1;
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2CxHandlerType, UINT8_T isNACK)
{
	if (isNACK)
	{
		return I2C_MSW_NACK(I2CxHandlerType);
	}
	else
	{
		return I2C_MSW_ACK(I2CxHandlerType);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBit(I2C_HandlerType *I2CxHandlerType, UINT8_T bitVal)
{
	if (bitVal & 0x80)
	{
		I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	}
	else
	{
		I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	}

	//---一个时钟脉冲
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
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
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2CxHandlerType, UINT8_T val)
{
	UINT8_T i = 0;

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		I2C_MSW_SendBit(I2CxHandlerType, val);
		val <<= 1;
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
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum)
{
	//---计算字节个数
	UINT8_T byteCount = (bitNum / 8);

	//---计算bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---发送整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2CxHandlerType, pVal[i]);
	}

	//---数据左移---数据的发送，首先发送高位
	pVal[byteCount] <<= (8 - bitCount);

	//---发送指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2CxHandlerType, pVal[byteCount]);
		pVal[byteCount] <<= 1;
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
UINT8_T I2C_MSW_ReadBit(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T _return = OK_0;

	//---时钟正脉冲
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---读取数据位
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit))
	{
		_return = ERROR_1;
	}

	//---时钟负脉冲
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;

	//---准备数据的读取
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2CxHandlerType);
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
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum)
{
	//---读取字节个数
	UINT8_T byteCount = (bitNum / 8);

	//---读取bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---读取整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2CxHandlerType);
	}

	//---清零处理
	pVal[byteCount] = 0x00;

	//---读取指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2CxHandlerType);
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
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2CxHandlerType, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---发送启动启动信号
		_return = I2C_MSW_START(I2CxHandlerType);
		if (_return)
		{
			I2C_MSW_STOP(I2CxHandlerType);
			return ERROR_1;
		}
	}

	//---发送数据
	_return = I2C_MSW_SendByte(I2CxHandlerType, cmd);

	//---读取应答
	_return = I2C_MSW_ReadACK(I2CxHandlerType);

	//---停止条件的满足
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2CxHandlerType);
	}
	return _return;
}