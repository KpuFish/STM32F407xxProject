#ifndef USART_CFG_H_
#define USART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//===ͷ�ļ�����
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "gpio_task.h"
#endif

typedef struct _USART_HandlerType						 USART_HandlerType;
typedef struct _USART_HandlerType						* pUSART_HandlerType;

//===�������ݽṹ��
typedef struct _USART_HandlerTypeDef					USART_RxHandlerType;
typedef struct _USART_HandlerTypeDef					*pUSART_RxHandlerType;

//===�������ݽṹ��
typedef struct _USART_HandlerTypeDef					USART_TxHandlerType;
typedef struct _USART_HandlerTypeDef					* pUSART_TxHandlerType;

//===�������ݽṹ�嶨��
struct _USART_HandlerTypeDef
{
	UINT8_T    msgCheckSum;								//---У���
	UINT8_T    msgCRCFlag;								//---У���־λ  0 ---��У�飬1 ---У��ͣ�2---CRC8У�飬3---CRC16У�飬4---CRC32У��
	UINT8_T	   msgTaskState;							//---�ж������Ƿ���� 0---δ������1---����
	VLTUINT8_T msgStep;									//---����
	UINT16_T   msgIndexW;								//---д���
	UINT16_T   msgIndexR;								//---�����
	UINT16_T   msgCount;								//---��д���ݵĳ���
	UINT16_T   msgSize;									//---���ݻ������Ĵ�С
	UINT8_T*   pMsgVal;									//---������(��Ҫ��ǰ��������ݵĻ�����)
};

//===�������ݶ���
struct _USART_HandlerType
{
	VLTUINT8_T				msgIndex;					//---USART�˿ڵ�������
	VLTUINT8_T				msgRxID;					//---���ձ�ͷ
	VLTUINT8_T				msgTxID;					//---���ͱ�ͷ
	VLTUINT8_T				msgOverFlow;				//---��ʱ��־λ
	UINT32_T				msgNowTime;					//---��ʱʱ�俪ʼ��
	UINT32_T				msgEndTime;					//---��ʱʱ�����ֵ
	UINT32_T				msgMaxTime;					//---��ʱʱ��
	UINT32_T				msgTxBit;					//---����GPIO�˿�
	GPIO_TypeDef*			msgTxPort;					//---USART��GPIO�˿ں�
	USART_TypeDef*			msgUSART;					//---USART�˿�
	USART_TxHandlerType		msgTxHandler;				//---���ͺ���
	USART_RxHandlerType		msgRxHandler;				//---���պ���
	UINT32_T(*msgFuncSysTick)(void);					//---���ڳ�ʱ����
};

#define USE_USART_PRINTF

//===ʹ�õ�У�鷽ʽ
#define USART_CRC_NONE							0
#define USART_CRC_CHECKSUM						1
#define USART_CRC_CRC8							2
#define USART_CRC_CRC16							3
#define USART_CRC_CRC32							4

//===���Ͷ˿ڵ�����
#define USART_TXGPIO_SET_INPUT					0
#define USART_TXGPIO_SET_OUTPUT					1

//===�ⲿ���ýӿ�
extern USART_HandlerType  g_USART1;
extern pUSART_HandlerType pUSART1;

//===��������
UINT8_T  USART_StructInit(USART_HandlerType*  USARTx);
UINT8_T  USART_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*sysTickFunc)(void));
UINT8_T  USART_EnableIT_TXE(USART_HandlerType*  USARTx, UINT8_T isEnable);
UINT32_T USART_IsEnabledIT_TXE(USART_HandlerType*  USARTx);
UINT32_T USART_IsActiveFlag_TXE(USART_HandlerType*  USARTx);
UINT8_T  USART_EnableIT_TC(USART_HandlerType*  USARTx, UINT8_T isEnable);
UINT32_T USART_IsEnabledIT_TC(USART_HandlerType*  USARTx);
UINT32_T USART_IsActiveFlag_TC(USART_HandlerType*  USARTx);
UINT8_T  USART_ClearFlag_TC(USART_HandlerType*  USARTx);
UINT8_T  USART_EnableIT_RX(USART_HandlerType*  USARTx, UINT8_T isEnable);
UINT8_T  USART_EnableIT_IDLE(USART_HandlerType*  USARTx, UINT8_T isEnable);
UINT8_T  USART_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput);
UINT8_T  USART_WriteData8Bits(USART_HandlerType*USARTx, UINT8_T val);
UINT8_T  USART_ReadData8Bits(USART_HandlerType*USARTx);
UINT8_T  USART_EnableCRC_RX(USART_HandlerType*USARTx, UINT8_T crcFlag);
UINT8_T  USART_GetCRC_RX(USART_HandlerType*USARTx);
UINT8_T  USART_EnableCRC_TX(USART_HandlerType*USARTx, UINT8_T crcFlag);
UINT8_T  USART_GetCRC_TX(USART_HandlerType*USARTx);
UINT8_T  USART_TimeTick_Init(USART_HandlerType*USARTx);
UINT8_T  USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut);
UINT8_T  USART_GetOVF(USART_HandlerType* USARTx);
UINT8_T  USART_ClearOVF(USART_HandlerType* USARTx);
UINT8_T  USART_SendByte(USART_HandlerType*USARTx, UINT8_T  val);
UINT8_T  USART_SendString(USART_HandlerType*USARTx, char *pVal);
UINT8_T  USART_GetOVF(USART_HandlerType* USARTx);
UINT8_T  USART_ClearOVF(USART_HandlerType* USARTx);
UINT8_T  USART_GetReadState(USART_HandlerType* USARTx);
UINT8_T  USART_ClearReadState(USART_HandlerType* USARTx);
UINT8_T  USART_GetWriteState(USART_HandlerType* USARTx);
UINT8_T  USART_ClearWriteState(USART_HandlerType* USARTx);
void     USART_Printf(USART_HandlerType*USARTx, char*fmt, ...);
UINT8_T  USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable);
UINT8_T  USART_DeInit(USART_HandlerType*USARTx);
UINT8_T  USART1_Init(USART_HandlerType*USARTx);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_CFG_H_ */
