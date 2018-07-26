#ifndef USART_CFG_H_
#define USART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//===头文件定义
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "gpio_task.h"
#endif

typedef struct _USART_HandlerType						 USART_HandlerType;
typedef struct _USART_HandlerType						* pUSART_HandlerType;

//===接收数据结构体
typedef struct _USART_HandlerTypeDef					USART_RxHandlerType;
typedef struct _USART_HandlerTypeDef					*pUSART_RxHandlerType;

//===发送数据结构体
typedef struct _USART_HandlerTypeDef					USART_TxHandlerType;
typedef struct _USART_HandlerTypeDef					* pUSART_TxHandlerType;

//===串口数据结构体定义
struct _USART_HandlerTypeDef
{
	UINT8_T    msgCheckSum;								//---校验和
	UINT8_T    msgCRCFlag;								//---校验标志位  0 ---无校验，1 ---校验和，2---CRC8校验，3---CRC16校验，4---CRC32校验
	UINT8_T	   msgTaskState;							//---判断任务是否结束 0---未结束，1---结束
	VLTUINT8_T msgStep;									//---步序
	UINT16_T   msgIndexW;								//---写序号
	UINT16_T   msgIndexR;								//---读序号
	UINT16_T   msgCount;								//---读写数据的长度
	UINT16_T   msgSize;									//---数据缓存区的大小
	UINT8_T*   pMsgVal;									//---缓存区(需要提前定义好数据的缓存区)
};

//===串口数据定义
struct _USART_HandlerType
{
	VLTUINT8_T				msgIndex;					//---USART端口的索引号
	VLTUINT8_T				msgRxID;					//---接收报头
	VLTUINT8_T				msgTxID;					//---发送报头
	VLTUINT8_T				msgOverFlow;				//---超时标志位
	UINT32_T				msgNowTime;					//---超时时间开始至
	UINT32_T				msgEndTime;					//---超时时间结束值
	UINT32_T				msgMaxTime;					//---超时时间
	UINT32_T				msgTxBit;					//---发送GPIO端口
	GPIO_TypeDef*			msgTxPort;					//---USART的GPIO端口号
	USART_TypeDef*			msgUSART;					//---USART端口
	USART_TxHandlerType		msgTxHandler;				//---发送函数
	USART_RxHandlerType		msgRxHandler;				//---接收函数
	UINT32_T(*msgFuncSysTick)(void);					//---用于超时计数
};

#define USE_USART_PRINTF

//===使用的校验方式
#define USART_CRC_NONE							0
#define USART_CRC_CHECKSUM						1
#define USART_CRC_CRC8							2
#define USART_CRC_CRC16							3
#define USART_CRC_CRC32							4

//===发送端口的配置
#define USART_TXGPIO_SET_INPUT					0
#define USART_TXGPIO_SET_OUTPUT					1

//===外部调用接口
extern USART_HandlerType  g_USART1;
extern pUSART_HandlerType pUSART1;

//===函数定义
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
