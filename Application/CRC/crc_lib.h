#ifndef CRC_LIB_H_
#define CRC_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "crc_cfg.h"
//---º¯Êý¶¨Òå
void	 CRC32Lib_Init(UINT8_T isHW);
UINT32_T CRC32Lib_HWGetCalc8BitsData(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC32Lib_HWGetCalc32BitsData(UINT32_T *pVal, UINT32_T length);
UINT32_T CRC32Lib_SWGetCalc8BitsData(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC32Lib_SWGetCalc32BitsData(UINT32_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CRC_LIB_H_ */