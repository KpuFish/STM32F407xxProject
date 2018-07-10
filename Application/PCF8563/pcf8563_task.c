#include "pcf8563_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563Task_Init(PCF8563_HandlerType *PCF8563HandlerType, void(*msgDelay)(UINT32_T delay))
{
	return PCF8563Lib_Init(PCF8563HandlerType, msgDelay);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563Task_DeInit(PCF8563_HandlerType *PCF8563HandlerType)
{
	return PCF8563Lib_DeInit(PCF8563HandlerType);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563Task_ClockOut(PCF8563_HandlerType *PCF8563HandlerType, UINT8_T preVal)
{
	return PCF8563Lib_ClockOut(PCF8563HandlerType, preVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563Task_ReadRTC(PCF8563_HandlerType *PCF8563HandlerType)
{
	return PCF8563Lib_ReadRTC(PCF8563HandlerType);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563Task_WriteRTC(PCF8563_HandlerType *PCF8563HandlerType, RTC_HandlerType rtc)
{
	return PCF8563Lib_WriteRTC(PCF8563HandlerType, rtc);
}