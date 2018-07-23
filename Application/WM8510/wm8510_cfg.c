#include "wm8510_cfg.h"
//===��������
WM8510_HandlerType  g_WM8510Device0;
pWM8510_HandlerType pWM8510Device0=&g_WM8510Device0;
///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void WM8510_StructInit(WM8510_HandlerType *WM8510x)
{
	WM8510x->mclkDIV = 1;
	WM8510x->bclkDIV = 1;
	WM8510x->preDIV = 0;
	WM8510x->pll_N = 0;

	WM8510x->R0[0] = 0x00;
	WM8510x->R0[1] = 0x00;

	WM8510x->R1[0] = 0x02;
	WM8510x->R1[1] = 0x23;

	WM8510x->nowR6[0]  = 0x0D;
	WM8510x->nowR6[1]  = 0x41;
	WM8510x->lastR6[0] = 0x0D;
	WM8510x->lastR6[1] = 0x41;


	WM8510x->nowR36[0]  = 0x00;
	WM8510x->nowR36[1]  = 0x00;
	WM8510x->lastR36[0] = 0x00;
	WM8510x->lastR36[1] = 0x00;

	WM8510x->nowR37[0] = 0x00;
	WM8510x->nowR37[1] = 0x00;
	WM8510x->lastR37[0] = 0x00;
	WM8510x->lastR37[1] = 0x00;

	WM8510x->nowR38[0] = 0x00;
	WM8510x->nowR38[1] = 0x00;
	WM8510x->lastR38[0] = 0x00;
	WM8510x->lastR38[1] = 0x00;

	WM8510x->nowR39[0] = 0x00;
	WM8510x->nowR39[1] = 0x00;
	WM8510x->lastR39[0] = 0x00;
	WM8510x->lastR39[1] = 0x00;
	
	WM8510x->pll_K = 0;
	WM8510x->oscFreq = WM8510_MCLK_HZ;
	WM8510x->freqHz = WM8510_OUT_MIN_FREQ;
	WM8510x->pllRate = 0;

	WM8510x->msgFuncSendCMD = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_Device0_Init(WM8510_HandlerType *WM8510x)
{
	WM8510x->msgI2C.msgI2Cx = NULL;
	WM8510x->msgI2C.msgSclPort = GPIOB;
	WM8510x->msgI2C.msgSdaPort = GPIOB;
	WM8510x->msgI2C.msgSclBit = LL_GPIO_PIN_8;
	WM8510x->msgI2C.msgSdaBit = LL_GPIO_PIN_9;
	WM8510x->msgI2C.msgModelIsHW = 0;
	WM8510x->msgI2C.msgPluseWidth = 1;
	WM8510x->msgI2C.msgFuncDelay = NULL;
	WM8510x->msgI2C.msgAddr = WM8510_WADDR;
	WM8510x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_Device1_Init(WM8510_HandlerType *WM8510x)
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
UINT8_T WM8510_Init(WM8510_HandlerType *WM8510x, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	WM8510_StructInit(WM8510x);
	WM8510_Device0_Init(WM8510x);
	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//_return= I2CTask_MHW_Init(&(WM8510x->msgI2C), msgDelay);
	}
	else
	{
		_return = I2CTask_MSW_Init(&(WM8510x->msgI2C), msgDelay);
		//---ע�������
		WM8510x->msgFuncSendCMD = WM8510_SWI2C_WriteReg;
		//---��������
		WM8510_SendCMD(WM8510x, WM8510x->R0);
		WM8510_SendCMD(WM8510x, WM8510x->R0);
		WM8510_SendCMD(WM8510x, WM8510x->R1);
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
UINT8_T WM8510_DeInit(WM8510_HandlerType *WM8510x, UINT8_T isHWI2C)
{
	//---ע����д����
	WM8510x->msgFuncSendCMD = NULL;
	//---ע��I2C�豸
	if (isHWI2C)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(WM8510x->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_SWI2C_WriteReg(WM8510_HandlerType *WM8510x, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������д����
	_return = I2CTask_MSW_START(&(WM8510x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i=0;i<length;i++)
	{
		//---��������
		I2CTask_MSW_SendByte(&(WM8510x->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(WM8510x->msgI2C));
		//---�ж�Ӧ��
		if (_return)
		{
			_return = ERROR_3 + i;
			goto GoToExit;
		}
	}
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(WM8510x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� Ӳ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_HWI2C_WriteReg(WM8510_HandlerType *WM8510x, UINT8_T *pVal, UINT8_T length)
{
	return ERROR_1;
}
///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_SendCMD(WM8510_HandlerType *WM8510x, UINT8_T *pVal)
{
	if ((WM8510x != NULL) && (WM8510x->msgFuncSendCMD != NULL))
	{
		return WM8510x->msgFuncSendCMD(WM8510x, pVal, 2);
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
void WM8510_Calc_PllRate(WM8510_HandlerType *WM8510x,UINT32_T freq)
{
	//---�����У����Ƶ�ʻᷢ���ı䣬��ÿ��ʹ�õ�ʱ����Ҫ���¸�ֵ
	WM8510x->oscFreq = WM8510_MCLK_HZ;
	//---���Ƶ��
	if (freq > WM8510_OUT_MAX_FREQ)
	{
		//---������Ƶ��
		freq = WM8510_OUT_MAX_FREQ;
	}
	//---��СƵ��
	if (freq < WM8510_OUT_MIN_FREQ)
	{
		//---��С���Ƶ��
		freq = WM8510_OUT_MIN_FREQ;
	}
	//---�趨�����Ƶ��
	WM8510x->freqHz = freq;
	//===�������㣬�����WM8510��ʱ�Ӿ�����12M����Щ������Ҫ���¼���
	if (freq > PDIV0_MDIV1_BDIV1_MIN)			//18000000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_1;
		WM8510x->bclkDIV = BCLK_DIV_1;
	}
	else if (freq>PDIV0_MDIV1D5_BDIV1_MIN)		//12000000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_1D5;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq =(freq* 3)/2;	// ����1.5
	}
	else if (freq > PDIV0_MDIV2_BDIV1_MIN)		//9000000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_2;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *=2;	// ����2
	}
	else if (freq > PDIV0_MDIV3_BDIV1_MIN)		//6000000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_3;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *= 3;	// ����3
	}
	else if (freq > PDIV0_MDIV4_BDIV1_MIN)		//4500000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_4;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *= 4;	// ����4
	}
	else if (freq > PDIV0_MDIV6_BDIV1_MIN)		//3000000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_6;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *= 6;	// ����6
	}
	else if (freq > PDIV0_MDIV8_BDIV1_MIN)		//2250000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *= 8;	// ����8
	}
	else if (freq > PDIV0_MDIV12_BDIV1_MIN)		//1500000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_1;
		freq *= 12;	// ����12
	}
	else if (freq > PDIV0_MDIV8_BDIV2_MIN)		//1125000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_2;
		freq *= 16;	// ����16
	}
	else if (freq > PDIV0_MDIV12_BDIV2_MIN)		//750000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_2;
		freq *= 24;	// ����24
	}
	else if (freq > PDIV0_MDIV8_BDIV4_MIN)		//562500
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_4;
		freq *= 32;	// ����32
	}
	else if (freq > PDIV0_MDIV12_BDIV4_MIN)		//375000
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_4;
		freq *= 48;	// ����48
	}
	else if (freq > PDIV0_MDIV8_BDIV8_MIN)		//281250
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_8;
		freq *= 64;	// ����64
	}
	else if (freq > PDIV0_MDIV12_BDIV8_MIN)		//187500
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_8;
		freq *= 64;	// ����96
	}
	else if (freq > PDIV0_MDIV4_BDIV32_MIN)		//140625
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_4;
		WM8510x->bclkDIV = BCLK_DIV_32;
		freq *= 128;	// ����128
	}
	else if (freq > PDIV0_MDIV6_BDIV32_MIN)		//93750
	{
		WM8510x->preDIV = 0;
		WM8510x->mclkDIV = MCLK_DIV_6;
		WM8510x->bclkDIV = BCLK_DIV_32;
		freq *= 192;	// ����192
	}
	else if (freq > PDIV1_MDIV8_BDIV16_MIN)		//70313
	{
		WM8510x->preDIV = 1;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_16;
		freq *= 128;	// ����128
		WM8510x->oscFreq >>= 1;
	}
	else if (freq > PDIV1_MDIV12_BDIV16_MIN)	//46875
	{
		WM8510x->preDIV = 1;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_16;
		freq *= 192;	// ����192
		WM8510x->oscFreq >>= 1;
	}
	else if (freq > PDIV1_MDIV8_BDIV32_MIN)		//35156
	{
		WM8510x->preDIV = 1;
		WM8510x->mclkDIV = MCLK_DIV_8;
		WM8510x->bclkDIV = BCLK_DIV_32;
		freq *= 256;	// ����256
		WM8510x->oscFreq >>= 1;
	}
	else
	{
		WM8510x->preDIV = 1;
		WM8510x->mclkDIV = MCLK_DIV_12;
		WM8510x->bclkDIV = BCLK_DIV_32;
		freq *= 384;	// ����384
		WM8510x->oscFreq >>= 1;
	}
	freq *= 4;	// ����4
	//---���������ı�ֵ(5��16֮��)
	WM8510x->pllRate = (float)freq / WM8510x->oscFreq;
	//---ȡ����
	WM8510x->pll_N = (UINT8_T)WM8510x->pllRate;
	//---ȡ��Kֵ
	WM8510x->pll_K = (UINT32_T)((WM8510x->pllRate - WM8510x->pll_N) * (float)0xFFFFFF);

	//===WM8510�����ݸ�ʽ�Ǹ�λ��ǰ����λ�ں�
	//---����ģʽ���Ƿ�ƵPLL�����ֵ
	WM8510x->nowR6[0] = (6 << 1) | 0x01;
	WM8510x->nowR6[1] = (UINT8_T)WM8510x->mclkDIV << 5;
	WM8510x->nowR6[1] |= (UINT8_T)WM8510x->bclkDIV << 2;
	//---BCLK���ʱ��
	WM8510x->nowR6[1] |= 0x01;

	WM8510x->nowR36[0] = 36 << 1;
	WM8510x->nowR36[1] = (WM8510x->preDIV == 0) ? 0 : (1 << 4);
	WM8510x->nowR36[1] |= WM8510x->pll_N;

	WM8510x->nowR37[0] = 37 << 1;
	WM8510x->nowR37[1] = (UINT8_T)((WM8510x->pll_K & 0xFC0000) >> 18);

	WM8510x->nowR38[0] = (UINT8_T)((38 << 1) | ((WM8510x->pll_K & (UINT32_T)0x20000) == 0 ? 0 : 1));
	WM8510x->nowR38[1] = (UINT8_T)((WM8510x->pll_K & 0x1FE00) >> 9);

	WM8510x->nowR39[0] = (UINT8_T)((39 << 1) | ((WM8510x->pll_K & (UINT32_T)0x100) == 0 ? 0 : 1));
	WM8510x->nowR39[1] = (UINT8_T)(WM8510x->pll_K & 0xFF);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_SetFreqHz(WM8510_HandlerType *WM8510x,UINT32_T freq)
{
	UINT8_T _return = OK_0;
	//---��������Ĵ�����ֵ
	WM8510_Calc_PllRate(WM8510x, freq);
	//===�жϼĴ����Ƿ����ı䣬���ı��򲻸�������
	if (memcmp(WM8510x->nowR6,WM8510x->lastR6,2)!=0)
	{
		WM8510x->lastR6[0] = WM8510x->nowR6[0];
		WM8510x->lastR6[1] = WM8510x->nowR6[1];
		_return=WM8510_SendCMD(WM8510x, WM8510x->nowR6);
		if (_return!=OK_0)
		{
			_return = ERROR_1;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->nowR36, WM8510x->lastR36, 2) != 0)
	{
		WM8510x->lastR36[0] = WM8510x->nowR36[0];
		WM8510x->lastR36[1] = WM8510x->nowR36[1];
		_return=WM8510_SendCMD(WM8510x, WM8510x->nowR36);
		if (_return != OK_0)
		{
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->nowR37, WM8510x->lastR37, 2) != 0)
	{
		WM8510x->lastR37[0] = WM8510x->nowR37[0];
		WM8510x->lastR37[1] = WM8510x->nowR37[1];
		_return = WM8510_SendCMD(WM8510x, WM8510x->nowR37);
		if (_return != OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->nowR38, WM8510x->lastR38, 2) != 0)
	{
		WM8510x->lastR38[0] = WM8510x->nowR38[0];
		WM8510x->lastR38[1] = WM8510x->nowR38[1];
		_return = WM8510_SendCMD(WM8510x, WM8510x->nowR38);
		if (_return != OK_0)
		{
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->nowR39, WM8510x->lastR39, 2) != 0)
	{
		WM8510x->lastR39[0] = WM8510x->nowR39[0];
		WM8510x->lastR39[1] = WM8510x->nowR39[1];
		_return = WM8510_SendCMD(WM8510x, WM8510x->nowR39);
		if (_return != OK_0)
		{
			_return = ERROR_5;
		}
	}
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  WM8510_SetFreqKHz(WM8510_HandlerType *WM8510x, float freq)
{
	UINT32_T temp = (UINT32_T)(freq * 1000);
	return WM8510_SetFreqHz(WM8510x,temp);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  WM8510_SetFreqMHz(WM8510_HandlerType *WM8510x, float freq)
{
	UINT32_T temp = (UINT32_T)(freq * 1000000);
	return WM8510_SetFreqHz(WM8510x, temp);
}
