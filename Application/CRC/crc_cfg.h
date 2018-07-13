#ifndef CRC_CFG_H_
#define CRC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
//===����ʹ�õ�CRCУ�鷽��
#define USE_CRC32
#define USE_CRC16
#define USE_CRC8
#define USE_CHECKSUM

//===����ṹ��
typedef struct  _CRC_HandlerType				CRC_HandlerType;
//===����ָ��ṹ��
typedef struct  _CRC_HandlerType				*pCRC_HandlerType;
//===�ṹ����
struct _CRC_HandlerType
{
	UINT32_T(*msgFuncCRC32)(UINT8_T *, UINT32_T );
	UINT16_T(*msgFuncCRC16)(UINT8_T *, UINT32_T );
	UINT8_T(*msgFuncCRC8)(UINT8_T *, UINT32_T );
	UINT8_T(*msgFuncCheckSum)(UINT8_T *, UINT32_T );
};

//===�ⲿ���ñ���
extern CRC_HandlerType g_CRC;
extern pCRC_HandlerType pCRC;

//===��������
void CRC_Init(void);
void CRC_DeInit(void);
UINT32_T CRC_CRC32_HWCRC(UINT8_T *pVal, UINT32_T length);
UINT32_T CRC_CRC32_Table(UINT8_T *pVal, UINT32_T length);
UINT16_T CRC_CRC16_Table(UINT8_T *pVal, UINT32_T length);
UINT8_T  CRC_CRC8_Table(UINT8_T *pVal, UINT32_T length);
UINT8_T	 CRC_CRC8_Table(UINT8_T *pVal, UINT32_T length);
UINT8_T  CRC_CheckSum(UINT8_T *pVal, UINT32_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CRC_CFG_H_ */