#include "one_wire_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWireLib_Init(OneWire_HandlerType *OneWirex, void(*Delayus)(UINT32_T delay))
{
	return OneWire_Init(OneWirex, Delayus);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWireLib_DeInit(OneWire_HandlerType *OneWirex)
{
	return OneWire_DeInit(OneWirex);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWireLib_START(OneWire_HandlerType *OneWirex)
{
	return OneWire_START(OneWirex);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWireLib_WriteByte(OneWire_HandlerType *OneWirex, UINT8_T val)
{
	return OneWire_WriteByte(OneWirex, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWireLib_ReadByte(OneWire_HandlerType *OneWirex)
{
	return OneWire_ReadByte(OneWirex);
}