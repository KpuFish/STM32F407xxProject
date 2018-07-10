#include "dht11_cfg.h"

//---��������
#ifdef DHT11_HandlerType_Device0
	DHT11_HandlerType	g_DHT11Device0;
	pDHT11_HandlerType	pDHT11Device0 = &g_DHT11Device0;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_StructInit(DHT11_HandlerType *DHT11x)
{
	DHT11x->msgDelayms = NULL;
	DHT11x->msgDelayus = NULL;
	DHT11x->msgShiDuX1000 = 0;
	DHT11x->msgWenDuX1000 = 0;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_GPIO_Init(DHT11_HandlerType *DHT11x)
{
	#ifdef USE_MCU_STM32
		if ((DHT11x == NULL) || (DHT11x->msgPort == NULL))
		{
			return ERROR_1;
		}

		//---ʹ�ܶ˿�ʱ��
		GPIOTask_Clock(DHT11x->msgPort, 1);
		LL_GPIO_InitTypeDef GPIO_InitStruct;

		//---GPIO�ĳ�ʼ��
		GPIO_InitStruct.Pin = DHT11x->msgBit;						//---��Ӧ��GPIO������
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;					//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;		//---GPIO���ٶ�
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;		//---���ģʽ---��©���
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---����ʹ��
		#ifndef USE_MCU_STM32F1
			GPIO_InitStruct.Alternate = LL_GPIO_AF_0;				//---�˿ڸ���ģʽ
		#endif
		//---��ʼ���˿�
		LL_GPIO_Init(DHT11x->msgPort, &GPIO_InitStruct);
	#endif
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay))
{
	DHT11_StructInit(DHT11x);
	//---ʹ�õ�DHT11�Ķ˿�
	#ifdef DHT11_HandlerType_Device0
		if ((DHT11x != NULL) && (DHT11x == pDHT11Device0))
		{
			DHT11_Device0_Init(DHT11x);
		}
	#endif
	//---GPIO�ĳ�ʼ��
	DHT11_GPIO_Init(DHT11x);
	//===ע����ʱ����
	//---us��ʱ
	if (Delayus != NULL)
	{
		DHT11x->msgDelayus = Delayus;
	}
	else
	{
		DHT11x->msgDelayus = DelayTask_us;
	}
	//---ms��ʱ
	if (Delayms != NULL)
	{
		DHT11x->msgDelayms = Delayms;
	}
	else
	{
		DHT11x->msgDelayms = DelayTask_ms;
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
UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHT11x)
{
	DHT11x->msgBit = LL_GPIO_PIN_14;
	DHT11x->msgPort = GPIOB;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_DeInit(DHT11_HandlerType *DHT11x)
{
	#ifdef USE_MCU_STM32
		LL_GPIO_DeInit(DHT11x->msgPort);
	#endif
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32

	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_RESET(DHT11_HandlerType *DHT11x)
{
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---�ͷ�����
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	//---��������2us
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(2);
	}
	GPIO_OUT_0(DHT11x->msgPort, DHT11x->msgBit);
	//---������ʼ,��������Ҫ����18ms
	if (DHT11x->msgDelayms != NULL)
	{
		DHT11x->msgDelayms(20);
	}
	//---�ͷ�����
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	//��������20~40us;�ȴ�DHT11�ĵ͵�ƽ��Ӧ�ź�
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(30);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����1:������;0:����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Check(DHT11_HandlerType *DHT11x)
{
	UINT8_T count = 0;
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---DHT11�����Ӧ�Ļ�����������40~80us
	while (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) != 0)
	{
		if (DHT11x->msgDelayus != NULL)
		{
			DHT11x->msgDelayus(1);
		}
		count++;
		if (count > 200)
		{
			break;
		}
	}
	if (count > 200)
	{
		return ERROR_1;
	}
	count = 0;
	//---DHT11�ߵ�ƽ����׼���ź��ٴ�����40~80us
	while (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) == 0)
	{
		if (DHT11x->msgDelayus != NULL)
		{
			DHT11x->msgDelayus(1);
		}
		count++;
		if (count > 200)
		{
			break;
		}
	}

	if (count > 200)
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����1:������;0:����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_START(DHT11_HandlerType *DHT11x)
{
	//---��������
	DHT11_RESET(DHT11x);

	//---����豸
	return DHT11_Check(DHT11x);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����λ���ݡ�0���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 26-28 ΢��ĸߵ�ƽ;
/////////////  λ���ݡ�1���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 70΢��ĸߵ�ƽ
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadBit(DHT11_HandlerType *DHT11x)
{
	UINT8_T count = 0;
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---�ȴ���Ϊ�͵�ƽ---�ߵ�ƽ���ֵ�ʱ��ԼΪ50us
	while (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) != 0)
	{
		if (DHT11x->msgDelayus != NULL)
		{
			DHT11x->msgDelayus(1);
		}
		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---��ȡ�ߵ�ƽ�ȴ�һ��
    if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(10);
	}
	//---�ȴ���ߵ�ƽ---�͵�ƽ���ֵ�ʱ��ԼΪ20us
	while (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) == 0)
	{
		if (DHT11x->msgDelayus != NULL)
		{
			DHT11x->msgDelayus(1);
		}
		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}

	//---�ȴ�40us;����Ϊ0���ź�ʱ��Ϊ26-28us��1��Ϊ70us
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(50);
	}
	//---��ȡ״̬
	if (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) != 0)
	{
		return 1;
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
UINT8_T DHT11_ReadByte(DHT11_HandlerType *DHT11x)
{
	UINT8_T i = 0, _return = 0;
	for (i = 0; i < 8; i++)
	{
         _return <<= 1;
		_return |= DHT11_ReadBit(DHT11x);
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
UINT8_T DHT11_Read(DHT11_HandlerType *DHT11x)
{
	UINT8_T temp[5] = { 0 };
	UINT8_T i = 0;

	//---�������ݵĶ�ȡ������豸�Ƿ����
	if (DHT11_START(DHT11x) != OK_0)
	{
		return ERROR_1;
	}
	//---��ȡ����
	for (i = 0; i < 5; i++)
	{
		temp[i] = DHT11_ReadByte(DHT11x);
	}
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---�ͷ�����
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);

	//---����У��
	if ((temp[0] + temp[1] + temp[2] + temp[3]) != temp[4])
	{
		return ERROR_2;
	}
	//---ʪ����������
	DHT11x->msgShiDuX1000 = temp[0];
	//---ʪ��С������
	DHT11x->msgShiDuX1000 = (DHT11x->msgShiDuX1000 *1000) + temp[1];
	//---�¶���������
	DHT11x->msgWenDuX1000 = temp[2];
	//---�¶�С������
	DHT11x->msgWenDuX1000 = (DHT11x->msgWenDuX1000 *1000) + temp[3];
	return OK_0;
}