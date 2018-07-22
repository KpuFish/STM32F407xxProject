#ifndef CRC_LIB_H_
#define CRC_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "crc_cfg.h"
//---º¯Êý¶¨Òå
void	 CRCLib_Init(void);
UINT8_T  CRCLib_Enable(void);
UINT32_T CRCLib_CRC32(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCLib_CRC16(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCLib_CRC8(UINT8_T *pVal, UINT32_T length);
UINT32_T CRCLib_CheckSum(UINT8_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CRC_LIB_H_ */