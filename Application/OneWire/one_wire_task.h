#ifndef ONE_WIRE_TASK_H_
#define ONE_WIRE_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "one_wire_lib.h"
//===��������
UINT8_T OneWireTask_Init(OneWire_HandlerType *OneWirex, void(*msgDelay)(UINT32_T delay));
UINT8_T OneWireTask_DeInit(OneWire_HandlerType *OneWirex);
UINT8_T OneWireTask_START(OneWire_HandlerType *OneWirex);
UINT8_T OneWireTask_WriteByte(OneWire_HandlerType *OneWirex, UINT8_T val);
UINT8_T OneWireTask_ReadByte(OneWire_HandlerType *OneWirex);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ONE_WIRE_TASK_H_ */