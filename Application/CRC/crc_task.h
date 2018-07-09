#ifndef CRC_TASK_H_
#define CRC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "crc_lib.h"
//---º¯Êý¶¨Òå
void	 CRC32Task_Init(UINT8_T isHW);
UINT32_T CRC32Task_GetCalc8BitsData(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC32Task_GetCalc32BitsData(UINT32_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*CRC_TASK_H_ */