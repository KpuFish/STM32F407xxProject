#include "one_wire_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_StructInit(OneWire_HandlerType *OneWirex)
{
	OneWirex->msgDelayus = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_Init(OneWire_HandlerType *OneWirex, void(*Delayus)(UINT32_T delay))
{
	OneWire_StructInit(OneWirex);
	#ifdef USE_MCU_STM32
		if ((OneWirex == NULL) || (OneWirex->msgPort == NULL))
		{
			return ERROR_1;
		}

		//---ʹ�ܶ˿�ʱ��
		GPIOTask_Clock(OneWirex->msgPort, 1);
		LL_GPIO_InitTypeDef GPIO_InitStruct;

		//---GPIO�ĳ�ʼ��
		GPIO_InitStruct.Pin = OneWirex->msgBit;			//---��Ӧ��GPIO������
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;					//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;			//---GPIO���ٶ�
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;				//---���ģʽ---��©���
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---����ʹ��

		//---��ʼ���˿�
		LL_GPIO_Init(OneWirex->msgPort, &GPIO_InitStruct);
	#endif

	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//---�˿�����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);
	//---��ʱ����
	if (Delayus != NULL)
	{
		OneWirex->msgDelayus = Delayus;
	}
	else
	{
		OneWirex->msgDelayus = DelayTask_us;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_DeInit(OneWire_HandlerType *OneWirex)
{
	#ifdef USE_MCU_STM32
		LL_GPIO_DeInit(OneWirex->msgPort);
	#endif
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_START(OneWire_HandlerType *OneWirex)
{
	UINT8_T _return = OK_0;
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//---����Ϊ����������
	GPIO_OUT_0(OneWirex->msgPort, OneWirex->msgBit);

	//>=480
	if (OneWirex->msgDelayus != NULL)
	{
		OneWirex->msgDelayus(500);
	}

	//---����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//15us~60us֮��
	if (OneWirex->msgDelayus != NULL)
	{
		OneWirex->msgDelayus(50);
	}
	_return = GPIO_GET_STATE(OneWirex->msgPort, OneWirex->msgBit);

	//60us~240us
	if (OneWirex->msgDelayus != NULL)
	{
		OneWirex->msgDelayus(200);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteBit(OneWire_HandlerType *OneWireHandlerType, UINT8_T bitVal)
{
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//---�������ߣ�ǿ������
	GPIO_OUT_0(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);

	//=4
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(4);
	}

	//---��������
	if (bitVal)
	{
		//---�ͷ�����
		GPIO_OUT_1(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);
	}

	//=60us
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(50);
	}

	//---�ͷ�����
	GPIO_OUT_1(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);

	//=4
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(4);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadBit(OneWire_HandlerType *OneWireHandlerType)
{
	UINT8_T _return = 0;
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//---��������,ǿ������
	GPIO_OUT_0(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);

	//=8
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(8);
	}

	//---�ͷ�����
	GPIO_OUT_1(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//=14
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(14);
	}
	
	//---��ȡ����
	if (GPIO_GET_STATE(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit))
	{
		_return = 1;
	}

	//=40
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(40);
	}
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(OneWirex->msgPort, OneWirex->msgBit);
	#endif 
	//---�ͷ�����
	GPIO_OUT_1(OneWireHandlerType->msgPort, OneWireHandlerType->msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteByte(OneWire_HandlerType *OneWireHandlerType, UINT8_T val)
{
	UINT8_T i = 0;
	for (i = 0; i < 8; i++)
	{
		//---�ȷ��͵�λ����
		OneWire_WriteBit(OneWireHandlerType, (val & 0x01));
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadByte(OneWire_HandlerType *OneWireHandlerType)
{
	UINT8_T _return = 0, i = 0;
	for (i = 0; i < 8; i++)
	{
		_return |= (OneWire_ReadBit(OneWireHandlerType) << i);
	}

	//=5
	if (OneWireHandlerType->msgDelayus != NULL)
	{
		OneWireHandlerType->msgDelayus(5);
	}
	return _return;
}