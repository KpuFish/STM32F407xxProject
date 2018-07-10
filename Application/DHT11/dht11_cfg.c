#include "dht11_cfg.h"

//---变量定义
#ifdef DHT11_HandlerType_Device0
	DHT11_HandlerType	g_DHT11Device0;
	pDHT11_HandlerType	pDHT11Device0 = &g_DHT11Device0;
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_GPIO_Init(DHT11_HandlerType *DHT11x)
{
	#ifdef USE_MCU_STM32
		if ((DHT11x == NULL) || (DHT11x->msgPort == NULL))
		{
			return ERROR_1;
		}

		//---使能端口时钟
		GPIOTask_Clock(DHT11x->msgPort, 1);
		LL_GPIO_InitTypeDef GPIO_InitStruct;

		//---GPIO的初始化
		GPIO_InitStruct.Pin = DHT11x->msgBit;						//---对应的GPIO的引脚
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;					//---配置状态为输出模式
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;		//---GPIO的速度
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;		//---输出模式---开漏输出
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---上拉使能
		#ifndef USE_MCU_STM32F1
			GPIO_InitStruct.Alternate = LL_GPIO_AF_0;				//---端口复用模式
		#endif
		//---初始化端口
		LL_GPIO_Init(DHT11x->msgPort, &GPIO_InitStruct);
	#endif
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay))
{
	DHT11_StructInit(DHT11x);
	//---使用的DHT11的端口
	#ifdef DHT11_HandlerType_Device0
		if ((DHT11x != NULL) && (DHT11x == pDHT11Device0))
		{
			DHT11_Device0_Init(DHT11x);
		}
	#endif
	//---GPIO的初始化
	DHT11_GPIO_Init(DHT11x);
	//===注册延时函数
	//---us延时
	if (Delayus != NULL)
	{
		DHT11x->msgDelayus = Delayus;
	}
	else
	{
		DHT11x->msgDelayus = DelayTask_us;
	}
	//---ms延时
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHT11x)
{
	DHT11x->msgBit = LL_GPIO_PIN_14;
	DHT11x->msgPort = GPIOB;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
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
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_RESET(DHT11_HandlerType *DHT11x)
{
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---释放总线
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	//---主机拉高2us
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(2);
	}
	GPIO_OUT_0(DHT11x->msgPort, DHT11x->msgBit);
	//---触发开始,总线拉低要大于18ms
	if (DHT11x->msgDelayms != NULL)
	{
		DHT11x->msgDelayms(20);
	}
	//---释放总线
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);
	//主机拉高20~40us;等待DHT11的低电平响应信号
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(30);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：1:不存在;0:存在
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Check(DHT11_HandlerType *DHT11x)
{
	UINT8_T count = 0;
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---DHT11如果响应的话会拉低总线40~80us
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
	//---DHT11高电平数据准备信号再次拉高40~80us
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
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：1:不存在;0:存在
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_START(DHT11_HandlerType *DHT11x)
{
	//---触发传输
	DHT11_RESET(DHT11x);

	//---检测设备
	return DHT11_Check(DHT11x);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：位数据“0”的格式为： 50 微秒的低电平和 26-28 微秒的高电平;
/////////////  位数据“1”的格式为： 50 微秒的低电平加 70微秒的高电平
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadBit(DHT11_HandlerType *DHT11x)
{
	UINT8_T count = 0;
	#ifndef USE_MCU_STM32
		GPIO_SET_READ(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---等待变为低电平---高电平保持的时间约为50us
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
	//---读取高电平等待一下
    if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(10);
	}
	//---等待变高电平---低电平保持的时间约为20us
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

	//---等待40us;数据为0的信号时间为26-28us，1则为70us
	if (DHT11x->msgDelayus != NULL)
	{
		DHT11x->msgDelayus(50);
	}
	//---读取状态
	if (GPIO_GET_STATE(DHT11x->msgPort, DHT11x->msgBit) != 0)
	{
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Read(DHT11_HandlerType *DHT11x)
{
	UINT8_T temp[5] = { 0 };
	UINT8_T i = 0;

	//---启动数据的读取并检查设备是否存在
	if (DHT11_START(DHT11x) != OK_0)
	{
		return ERROR_1;
	}
	//---读取数据
	for (i = 0; i < 5; i++)
	{
		temp[i] = DHT11_ReadByte(DHT11x);
	}
	#ifndef USE_MCU_STM32
		GPIO_SET_WRITE(DHT11x->msgPort, DHT11x->msgBit);
	#endif // !USE_MCU_STM32
	//---释放总线
	GPIO_OUT_1(DHT11x->msgPort, DHT11x->msgBit);

	//---数据校验
	if ((temp[0] + temp[1] + temp[2] + temp[3]) != temp[4])
	{
		return ERROR_2;
	}
	//---湿度整数部分
	DHT11x->msgShiDuX1000 = temp[0];
	//---湿度小数部分
	DHT11x->msgShiDuX1000 = (DHT11x->msgShiDuX1000 *1000) + temp[1];
	//---温度整数部分
	DHT11x->msgWenDuX1000 = temp[2];
	//---温度小数部分
	DHT11x->msgWenDuX1000 = (DHT11x->msgWenDuX1000 *1000) + temp[3];
	return OK_0;
}