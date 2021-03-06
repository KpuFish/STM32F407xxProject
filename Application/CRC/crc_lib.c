#include "crc_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void CRCLib_Init(void)
{
	CRC_Init();
	pCRC->msgCRCInit = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T CRCLib_Enable(void)
{
	return pCRC->msgCRCInit;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T CRCLib_CRC32(UINT8_T *pVal, UINT32_T length)
{
	if ((pCRC != NULL) && (pCRC->msgFuncCRC32 != NULL))
	{
		return pCRC->msgFuncCRC32(pVal, length);
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T CRCLib_CRC16(UINT8_T *pVal, UINT32_T length)
{
	if ((pCRC != NULL) && (pCRC->msgFuncCRC16 != NULL))
	{
		return pCRC->msgFuncCRC16(pVal, length);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T CRCLib_CRC8(UINT8_T *pVal, UINT32_T length)
{
	if ((pCRC != NULL) && (pCRC->msgFuncCRC8 != NULL))
	{
		return pCRC->msgFuncCRC8(pVal, length);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T CRCLib_CheckSum(UINT8_T *pVal, UINT32_T length)
{
	if ((pCRC != NULL) && (pCRC->msgFuncCheckSum != NULL))
	{
		return pCRC->msgFuncCheckSum(pVal, length);
	}
	return 0;
}