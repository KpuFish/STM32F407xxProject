#ifndef RANDOM_CFG_H_
#define RANDOM_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
//===�ⲿ���ýӿ�
#ifdef RNG
extern volatile UINT32_T g_HASH_RNG_Val;
#endif
//===��������
void Random_Init(void);
void Random_DeInit(void);
UINT32_T Random_GetVal(void);
UINT32_T Random_GetRand(UINT32_T minVal, UINT32_T maxVal);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*__random_cfg_H */