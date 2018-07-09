#ifndef ONE_WIRE_LIB_H_
#define ONE_WIRE_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "one_wire_cfg.h"
//===º¯Êý¶¨Òå
UINT8_T OneWireLib_Init(OneWire_HandlerType *OneWirex, void(*Delayus)(UINT32_T delay));
UINT8_T OneWireLib_DeInit(OneWire_HandlerType *OneWirex);
UINT8_T OneWireLib_START(OneWire_HandlerType *OneWirex);
UINT8_T OneWireLib_WriteByte(OneWire_HandlerType *OneWirex, UINT8_T val);
UINT8_T OneWireLib_ReadByte(OneWire_HandlerType *OneWirex);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ONE_WIRE_LIB_H_ */