#ifndef DHT11_LIB_H_
#define DHT11_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "dht11_cfg.h"

//===��������
UINT8_T DHT11Lib_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DHT11Lib_DeInit(DHT11_HandlerType *DHT11x);
UINT8_T DHT11Lib_Read(DHT11_HandlerType *DHT11x);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_LIB_H_*/