#ifndef DS18B20_LIB_H_
#define DS18B20_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "ds18b20_cfg.h"
//---º¯Êý¶¨Òå
UINT8_T DS18B20Lib_Init(DS18B20_HandlerType *DS18B20x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DS18B20Lib_DeInit(DS18B20_HandlerType *DS18B20x);
UINT8_T DS18B20Lib_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
UINT16_T DS18B20Lib_ReadWenDu(DS18B20_HandlerType *DS18B20x);
UINT16_T DS18B20Lib_ReadWenDuByID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_LIB_H_ */
