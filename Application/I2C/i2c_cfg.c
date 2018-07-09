#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2CxHandlerType, void(*msgDelay)(UINT32_T delay))
{
	#ifdef USE_MCU_STM32

	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(I2CxHandlerType->msgSclPort, 1);
	GPIOTask_Clock(I2CxHandlerType->msgSdaPort, 1);

	//---SCL��SDA�˿�����ߵ�ƽ
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2CxHandlerType->msgSclBit;				//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;				//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;					//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����

	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2CxHandlerType->msgSclPort, &GPIO_InitStruct);

	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2CxHandlerType->msgSdaBit;
	LL_GPIO_Init(I2CxHandlerType->msgSdaPort, &GPIO_InitStruct);
	#endif

	//---����ʹ�õ���ʱ����
	if (msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay = msgDelay;
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
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2CxHandlerType)
{
	//---�˿�����Ϊ����ģʽ
	I2C_SCL_READ(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_READ(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---SCL��SDA�˿�����ߵ�ƽ
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---ע��������
	if (I2CxHandlerType->msgTask != NULL)
	{
		I2CxHandlerType->msgTask = NULL;
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
UINT8_T I2C_MSW_START(I2C_HandlerType *I2CxHandlerType)
{
	//---������ʼ�����������ź�
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---������ʼ�ź�;
	I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---0��ʧ��SDA---1
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) != OK_0)
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
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2CxHandlerType)
{
	//---����ֹͣ�����������ź�
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

	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---1��ʧ��SDA---0
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) == OK_0)
	{
		return ERROR_1;
	}
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2CxHandlerType)
{
	I2C_SDA_OUT_0(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2CxHandlerType)
{
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T _return = OK_0;

	//---��ȡӦ���ź�
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---��ʱ�ȴ�
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---��ȡSDA��״̬�ź�---ACK״̬��SDAΪ�͵�ƽ
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit) != OK_0)
	{
		_return = ERROR_1;
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T i = 0;

	//---��ȡӦ���ź�
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---�ȴ�Ӧ���ź�
	for (i = 255; i > 0; i--)
	{
		//---��ȡSDA��״̬
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

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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

	//---һ��ʱ������
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2CxHandlerType, UINT8_T val)
{
	UINT8_T i = 0;

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2CxHandlerType, val);
		val <<= 1;
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
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum)
{
	//---�����ֽڸ���
	UINT8_T byteCount = (bitNum / 8);

	//---����bit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---���������ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2CxHandlerType, pVal[i]);
	}

	//---��������---���ݵķ��ͣ����ȷ��͸�λ
	pVal[byteCount] <<= (8 - bitCount);

	//---����ָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2CxHandlerType, pVal[byteCount]);
		pVal[byteCount] <<= 1;
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
UINT8_T I2C_MSW_ReadBit(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T _return = OK_0;

	//---ʱ��������
	I2C_SCL_OUT_1(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}

	//---��ȡ����λ
	if (I2C_SDA_STATE(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit))
	{
		_return = ERROR_1;
	}

	//---ʱ�Ӹ�����
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);
	if (I2CxHandlerType->msgDelay != NULL)
	{
		I2CxHandlerType->msgDelay(I2CxHandlerType->msgPluseWidth);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2CxHandlerType)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;

	//---׼�����ݵĶ�ȡ
	I2C_SDA_OUT_1(I2CxHandlerType->msgSdaPort, I2CxHandlerType->msgSdaBit);

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	I2C_SCL_OUT_0(I2CxHandlerType->msgSclPort, I2CxHandlerType->msgSclBit);

	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2CxHandlerType);
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
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum)
{
	//---��ȡ�ֽڸ���
	UINT8_T byteCount = (bitNum / 8);

	//---��ȡbit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---��ȡ�����ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2CxHandlerType);
	}

	//---���㴦��
	pVal[byteCount] = 0x00;

	//---��ȡָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2CxHandlerType);
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
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2CxHandlerType, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---�������������ź�
		_return = I2C_MSW_START(I2CxHandlerType);
		if (_return)
		{
			I2C_MSW_STOP(I2CxHandlerType);
			return ERROR_1;
		}
	}

	//---��������
	_return = I2C_MSW_SendByte(I2CxHandlerType, cmd);

	//---��ȡӦ��
	_return = I2C_MSW_ReadACK(I2CxHandlerType);

	//---ֹͣ����������
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2CxHandlerType);
	}
	return _return;
}