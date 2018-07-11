#ifndef RANDOM_TASK_H_
#define RANDOM_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "random_lib.h"

//===º¯Êý¶¨Òå
void RandomTask_Init(void);
void RandomTask_DeInit(void);
UINT32_T RandomTask_GetVal(void);
UINT32_T RandomTask_GetRand(UINT32_T minVal, UINT32_T maxVal);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RANDOM_LIB_H_ */