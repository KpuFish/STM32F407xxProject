#ifndef DHT11_LIB_H_
#define DHT11_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "dht11_cfg.h"
//---�ⲿ���ýӿ�
#ifdef DHT11_HandlerType_Device0
	extern DHT11_HandlerType	g_DHT11Device0;
	extern pDHT11_HandlerType	pDHT11Device0;
#endif
//---��������
UINT8_T DHT11Lib_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DHT11Lib_DeInit(DHT11_HandlerType *DHT11x);
UINT8_T DHT11Lib_Read(DHT11_HandlerType *DHT11x);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_LIB_H */