#ifndef DS18B20_CFG_H_
#define DS18B20_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////

#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "delay_task.h"
#endif
#include "one_wire_task.h"

//===定义结构体
typedef struct _DS18B20_HandlerType				DS18B20_HandlerType;
//===定义指针结构
typedef struct _DS18B20_HandlerType				*pDS18B20_HandlerType;
//===结构定义
struct _DS18B20_HandlerType
{
	UINT8_T					msgIsPositive;						//0---无数据，1---是负数，2---是正值
	UINT16_T				msgWenDuX100;						//---温度的值，放大100倍的值
	UINT32_T				msgWenDuX10000;						//---温度的值，放大1000倍的值
	OneWire_HandlerType		msgOneWire;							//---一线通信
	void(*msgFuncDelayms)(UINT32_T delay);						//---ms延时函数
};

//===选择使用的任务
#define DS18B20_HandlerType_Device0
//===外部调用
#ifdef DS18B20_HandlerType_Device0
extern DS18B20_HandlerType g_DS18B20Device0;
extern pDS18B20_HandlerType pDS18B20Device0;
#endif

//===函数的定义
UINT8_T  DS18B20_Init(DS18B20_HandlerType *DS18B20x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
UINT8_T  DS18B20_Device0_Init(DS18B20_HandlerType *DS18B20x);
UINT8_T  DS18B20_DeInit(DS18B20_HandlerType *DS18B20x);
UINT8_T  DS18B20_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
UINT16_T DS18B20_ReadWenDu(DS18B20_HandlerType *DS18B20x);
UINT16_T DS18B20_ReadWenDuByID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_CFG_H_ */
