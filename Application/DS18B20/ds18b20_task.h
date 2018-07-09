#ifndef DS18B20_TASK_H_
#define DS18B20_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "ds18b20_lib.h"
//---º¯Êý¶¨Òå
UINT8_T DS18B20Task_Init(DS18B20_HandlerType *DS18B20x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DS18B20Task_DeInit(DS18B20_HandlerType *DS18B20x);
UINT8_T DS18B20Task_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *id);
UINT16_T DS18B20Task_ReadWenDu(DS18B20_HandlerType *DS18B20x);
UINT16_T DS18B20Task_ReadWenDuByID(DS18B20_HandlerType *DS18B20x, UINT8_T *id);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_TASK_H_ */
