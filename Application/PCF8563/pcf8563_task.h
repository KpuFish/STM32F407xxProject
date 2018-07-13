#ifndef PCF8563_TASK_H_
#define PCF8563_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//------------使用包含的头文件
#include "pcf8563_lib.h"

//---函数定义
UINT8_T PCF8563Task_Init(PCF8563_HandlerType *PCF8563x, void(*msgDelay)(UINT32_T delay),UINT8_T isHWI2C);
UINT8_T PCF8563Task_DeInit(PCF8563_HandlerType *PCF8563x);
UINT8_T PCF8563Task_ClockOut(PCF8563_HandlerType *PCF8563x, UINT8_T preVal);
UINT8_T PCF8563Task_ReadRTC(PCF8563_HandlerType *PCF8563x);
UINT8_T PCF8563Task_WriteRTC(PCF8563_HandlerType *PCF8563x, RTC_HandlerType rtc);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* PCF8563_TASK_H_ */