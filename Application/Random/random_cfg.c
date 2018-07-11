#include "random_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����void RandomCfg_Init(void)
//////��	   �ܣ�������ĳ�ʼ��
//////�������: 
//////�������: 
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void Random_Init(void)
{
	#ifdef USE_MCU_STM32
		#ifdef RNG
			//---ʹ�����������ʱ��
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_RNG);
			//---ʹ�����������
			LL_RNG_Enable(RNG);
			//---�ȴ����������
			while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1);
		#endif 
	#endif 
}
///////////////////////////////////////////////////////////////////////////////
//////��	   ����void RandomCfg_DeInit(void)
//////��	   �ܣ��������ע��
//////�������: 
//////�������: 
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void Random_DeInit(void)
{
	#ifdef USE_MCU_STM32
		#ifdef RNG
			LL_AHB2_GRP1_DisableClock( LL_AHB2_GRP1_PERIPH_RNG );
			LL_RNG_DeInit( RNG );
		#endif 
	#endif 
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������: 
//////�������: 
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetVal(void)
{
	#if defined(USE_MCU_STM32)&&defined(RNG)
		//---�ȴ����������
		while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1);
		//---��ȡ�����������
		return LL_RNG_ReadRandData32(RNG);
	#else
		return rand();
	#endif 
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����UINT32_T RandomCfg_GetRandomRang(UINT32_T minVal,UINT32_T maxVal)
//////��	   �ܣ�������ָ����Сֵ��ָ�����ֵ��Χ�������
//////�������: 
//////�������: ��ǰ�������
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetRand(UINT32_T minVal,UINT32_T maxVal)
{
	//---��ȡ��ǰ�������
	UINT32_T randomVal = 0;
	//---����ֵ
	UINT32_T _return = 0;
	//---�жϵ��õ����������
	#if defined(USE_MCU_STM32)&&defined(RNG)
		randomVal = Random_GetVal();
	#else
		//---�ж�ѡȡ�����������
		if (minVal<maxVal)
		{
			randomVal = maxVal;
		}
		else
		{
			randomVal = minVal;
		}
		//---����������ӷ�Χ
		srand(randomVal);
		//---��ȡ�����
		randomVal = rand();
	#endif
	//---���㷵�ص������
	if (minVal<maxVal)
	{
		_return = randomVal % ( maxVal - minVal + 1 ) + minVal;
	}
	else
	{
		_return = randomVal % ( minVal - maxVal + 1 ) + maxVal;
	}
	return _return;
}