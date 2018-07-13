#ifndef CRC_TASK_H_
#define CRC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "crc_lib.h"
//---º¯Êý¶¨Òå
void	 CRCTask_Init(void);
UINT32_T CRCTask_CRC32(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCTask_CRC16(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCTask_CRC8(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCTask_CheckSum(UINT8_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*CRC_TASK_H_ */