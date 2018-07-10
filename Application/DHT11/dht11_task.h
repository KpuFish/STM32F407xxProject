#ifndef DHT11_TASK_H_
#define DHT11_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "dht11_lib.h"
//---外部调用接口
#ifdef DHT11_HandlerType_Device0
	extern DHT11_HandlerType	g_DHT11Device0;
	extern pDHT11_HandlerType	pDHT11Device0;
#endif
//---函数定义
UINT8_T DHT11Task_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DHT11Task_DeInit(DHT11_HandlerType *DHT11x);
UINT8_T DHT11Task_Read(DHT11_HandlerType *DHT11x);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_TASK_H_ */