#ifndef DHT11_CFG_H_
#define DHT11_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
/////˵��:DHT11����ʱ���Ҫ��Ƚϵĸߣ���ʹ�õ�ʱ��ע����ʱ�����ã��������׳��ִ���
/////���ʱ����ȷ�������������Ӧ���ǳ��ڶ�ȡ���ݵ�ʱ�����ԣ�ʾ����ץȡ���ݶ�ȡ�ĵط�
/////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
#ifdef USE_MCU_STM32
	#include "gpio_task.h"
	#include "delay_task.h"
#endif

//---����ṹ��
typedef struct _DHT11_HandlerType		DHT11_HandlerType;
//---����ָ��ṹ��
typedef struct _DHT11_HandlerType		*pDHT11_HandlerType;

//---����
struct _DHT11_HandlerType
{
	UINT32_T		msgWenDuX1000;				//---�¶�
	UINT32_T		msgShiDuX1000;				//---ʪ��
	UINT32_T		msgBit;						//---�˿����
	GPIO_TypeDef	*msgPort;					//---�˿ں�
	void(*msgDelayus)(UINT32_T delay);			//---us��ʱ����
	void(*msgDelayms)(UINT32_T delay);			//---ms��ʱ����
};

//---ѡ��ʹ�õ�����
#define DHT11_HandlerType_Device0
//---�ⲿ���ýӿ�
#ifdef DHT11_HandlerType_Device0
	extern DHT11_HandlerType	g_DHT11Device0;
	extern pDHT11_HandlerType	pDHT11Device0;
#endif

//---��������
UINT8_T DHT11_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHT11x);
UINT8_T DHT11_DeInit(DHT11_HandlerType *DHT11x);
UINT8_T DHT11_Read(DHT11_HandlerType *DHT11x);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_CFG_H_*/