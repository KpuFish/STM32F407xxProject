#include "random_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函	   数：void RandomCfg_Init(void)
//////功	   能：随机数的初始化
//////输入参数: 
//////输出参数: 
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
void Random_Init(void)
{
	#ifdef USE_MCU_STM32
		#ifdef RNG
			//---使能随机数总线时钟
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_RNG);
			//---使能随机产生器
			LL_RNG_Enable(RNG);
			//---等待随机数就绪
			while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1);
		#endif 
	#endif 
}
///////////////////////////////////////////////////////////////////////////////
//////函	   数：void RandomCfg_DeInit(void)
//////功	   能：随机数的注销
//////输入参数: 
//////输出参数: 
//////说	   明：
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
//////函	   数：
//////功	   能：
//////输入参数: 
//////输出参数: 
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetVal(void)
{
	#if defined(USE_MCU_STM32)&&defined(RNG)
		//---等待随机数就绪
		while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1);
		//---读取产生的随机数
		return LL_RNG_ReadRandData32(RNG);
	#else
		return rand();
	#endif 
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：UINT32_T RandomCfg_GetRandomRang(UINT32_T minVal,UINT32_T maxVal)
//////功	   能：生成在指定最小值和指定最大值范围的随机数
//////输入参数: 
//////输出参数: 当前的随机数
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetRand(UINT32_T minVal,UINT32_T maxVal)
{
	//---获取当前的随机数
	UINT32_T randomVal = 0;
	//---返回值
	UINT32_T _return = 0;
	//---判断调用的随机数函数
	#if defined(USE_MCU_STM32)&&defined(RNG)
		randomVal = Random_GetVal();
	#else
		//---判断选取的随机数种子
		if (minVal<maxVal)
		{
			randomVal = maxVal;
		}
		else
		{
			randomVal = minVal;
		}
		//---随机数的种子范围
		srand(randomVal);
		//---获取随机数
		randomVal = rand();
	#endif
	//---计算返回的随机数
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