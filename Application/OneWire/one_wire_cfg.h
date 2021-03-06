#ifndef ONE_WIRE_CFG_H_
#define ONE_WIRE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "delay_task.h"
#include "gpio_task.h"
#endif

//===定义结构体
typedef struct _OneWire_HandlerType		OneWire_HandlerType;

//===定义指针结构体
typedef struct _OneWire_HandlerType		*pOneWire_HandlerType;

//===定义
struct _OneWire_HandlerType
{
	UINT32_T		msgBit;						//---端口序号
	GPIO_TypeDef	*msgPort;					//---端口号
	void(*msgDelayus)(UINT32_T delay);			//---延时函数
};

//===函数定义
UINT8_T OneWire_Init(OneWire_HandlerType *OneWirex, void(*Delayus)(UINT32_T delay));
UINT8_T OneWire_DeInit(OneWire_HandlerType *OneWirex);
UINT8_T OneWire_START(OneWire_HandlerType *OneWirex);
UINT8_T OneWire_WriteBit(OneWire_HandlerType *OneWirex, UINT8_T bitVal);
UINT8_T OneWire_ReadBit(OneWire_HandlerType *OneWirex);
UINT8_T OneWire_WriteByte(OneWire_HandlerType *OneWirex, UINT8_T val);
UINT8_T OneWire_ReadByte(OneWire_HandlerType *OneWirex);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*ONE_WIRE_CFG_H_ */