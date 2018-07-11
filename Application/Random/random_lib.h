#ifndef RANDOM_LIB_H_
#define RANDOM_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "random_cfg.h"
//===º¯Êý¶¨Òå
void RandomLib_Init( void );
void RandomLib_DeInit( void );
UINT32_T RandomLib_GetVal(void);
UINT32_T RandomLib_GetRand( UINT32_T minVal , UINT32_T maxVal );
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RANDOM_LIB_H_ */
