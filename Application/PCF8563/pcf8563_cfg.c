#include "pcf8563_cfg.h"

//===�����Ķ���
#ifdef PCF8563_HandlerType_Device0
	//---ȫ�ֱ�������
	PCF8563_HandlerType g_PCF8563Device0;
	//---ȫ��ָ�����
	pPCF8563_HandlerType pPCF8563Device0 = &g_PCF8563Device0;
#endif


///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_Init(PCF8563_HandlerType *PCF8563HandlerType, void(*msgDelay)(UINT32_T delay))
{
	#ifdef PCF8563_HandlerType_Device0
		if ((PCF8563HandlerType != NULL) && (PCF8563HandlerType == pPCF8563Device0))
		{
			PCF8563_Device0_Init(PCF8563HandlerType);
		}
	#endif
	return I2CTask_MSW_Init(&(PCF8563HandlerType->msgI2C), msgDelay);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_Device0_Init(PCF8563_HandlerType *PCF8563HandlerType)
{
	PCF8563HandlerType->msgI2C.msgI2Cx = NULL;
	PCF8563HandlerType->msgI2C.msgSclPort = GPIOB;
	PCF8563HandlerType->msgI2C.msgSdaPort = GPIOB;
	PCF8563HandlerType->msgI2C.msgSclBit = LL_GPIO_PIN_8;
	PCF8563HandlerType->msgI2C.msgSdaBit = LL_GPIO_PIN_9;
	PCF8563HandlerType->msgI2C.msgModelIsHW = 0;
	PCF8563HandlerType->msgI2C.msgPluseWidth = 0;
	PCF8563HandlerType->msgI2C.msgDelay = NULL;
	PCF8563HandlerType->msgI2C.msgAddr = 0xA2;//PCF8563_WRITE_ADDR;
	PCF8563HandlerType->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_Device1_Init(PCF8563_HandlerType *PCF8563HandlerType)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_DeInit(PCF8563_HandlerType *PCF8563HandlerType)
{
	return I2CTask_MSW_DeInit(&(PCF8563HandlerType->msgI2C));
}
///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�д�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_WriteReg(PCF8563_HandlerType *PCF8563HandlerType, UINT8_T reg, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(PCF8563HandlerType->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563HandlerType->msgI2C), reg);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563HandlerType->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563HandlerType->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563HandlerType->msgI2C));
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563HandlerType->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_ReadReg(PCF8563_HandlerType *PCF8563HandlerType, UINT8_T reg, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = OK_0, i = 0;
	//---����д����
	_return = I2CTask_MSW_START(&(PCF8563HandlerType->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563HandlerType->msgI2C), reg);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563HandlerType->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563HandlerType->msgI2C));
	//---������ȡ����
	_return = I2CTask_MSW_START(&(PCF8563HandlerType->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(PCF8563HandlerType->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(PCF8563HandlerType->msgI2C), _return);
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563HandlerType->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T PCF8563_HandlerType_ClockOut(UINT8_T preVal)
//////��	   �ܣ� PCF8563���ʱ�ӣ������Ƶ
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_ClockOut(PCF8563_HandlerType *PCF8563HandlerType, UINT8_T preVal)
{
	UINT8_T _return = OK_0;
	UINT8_T temp = 0;
	//---д�Ĵ���
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_CLKOUT, (preVal | 0x80));
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��ȡ�Ĵ���
	_return = PCF8563_ReadReg(PCF8563HandlerType, PCF8563_REG_CLKOUT, &temp, 1);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݵ�У��
	if ((temp & 0x7F) != preVal)
	{
		_return = ERROR_1;
	}
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_ReadRTC(PCF8563_HandlerType *PCF8563HandlerType)
{
	UINT8_T _return = OK_0;
	UINT8_T temp[7];
	//---��ȡʱ��
	_return = PCF8563_ReadReg(PCF8563HandlerType, PCF8563_REG_SECOND, temp, 7);
	//---��������
	if (_return == OK_0)
	{
		//---����ȡ��������䵽������
		PCF8563HandlerType->msgRTC.second = (temp[0] & 0x7F);
		PCF8563HandlerType->msgRTC.minute = (temp[1] & 0x7F);
		PCF8563HandlerType->msgRTC.hour = (temp[2] & 0x3F);
		PCF8563HandlerType->msgRTC.day = (temp[3] & 0x3F);
		PCF8563HandlerType->msgRTC.week = (temp[4] & 0x07);
		PCF8563HandlerType->msgRTC.month = (temp[5] & 0x1F);
		//---���
		PCF8563HandlerType->msgRTC.year = temp[6];
		//---����
		if (temp[5] & 0x80)
		{
			PCF8563HandlerType->msgRTC.century = 0x19;
		}
		else
		{
			PCF8563HandlerType->msgRTC.century = 0x20;
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
UINT8_T PCF8563_WriteRTC(PCF8563_HandlerType *PCF8563HandlerType, RTC_HandlerType rtc)
{
	UINT8_T _return = OK_0;
	//---�ж����������ǲ���BCD��
	if ((rtc.century != 0x19) || (rtc.century != 0x20))
	{
		//===��������λBCD��ʽ
		rtc.second = DecToBcd(rtc.second);
		rtc.minute = DecToBcd(rtc.minute);
		rtc.hour = DecToBcd(rtc.hour);
		rtc.day = DecToBcd(rtc.day);
		rtc.week = DecToBcd(rtc.week);
		rtc.month = DecToBcd(rtc.month);
		rtc.year = DecToBcd(rtc.year);
		rtc.century = DecToBcd(rtc.century);
	}
	//---���Ͳ����Ĵ���
	if (rtc.century == 0x20)
	{
		rtc.month &= 0x3F;
	}
	else
	{
		rtc.month |= 0x80;
	}
	//---д��
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_SECOND, rtc.second);
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_MINUTE, rtc.minute);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---дʱ
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_HOURS, rtc.hour);
	if (_return != OK_0)
	{
		_return = ERROR_4;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_DAY, rtc.day);
	if (_return != OK_0)
	{
		_return = ERROR_5;
		goto GoToExit;
	}
	//---д����
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_WEEK, rtc.week);
	if (_return != OK_0)
	{
		_return = ERROR_6;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_MONTH, rtc.month);
	if (_return != OK_0)
	{
		_return = ERROR_7;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_WriteReg(PCF8563HandlerType, PCF8563_REG_YEAR, rtc.year);
GoToExit:
	return _return;
}