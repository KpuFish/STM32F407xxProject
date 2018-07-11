#ifndef PCF8563_CFG_H_
#define PCF8563_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//------------使用包含的头文件
#include "i2c_task.h"
#ifdef USE_MCU_STM32
	#include "delay_task.h"
#endif

//---寄存器定义
#define PCF8563_REG_STATUS1						0x00
#define PCF8563_REG_STATUS2						0x01
#define PCF8563_REG_SECOND						0x02
#define PCF8563_REG_MINUTE						0x03
#define PCF8563_REG_HOURS						0x04
#define PCF8563_REG_DAY							0x05
#define PCF8563_REG_WEEK						0x06
#define PCF8563_REG_MONTH						0x07
#define PCF8563_REG_YEAR						0x08
#define PCF8563_REG_MINUTE_ALARM				0x09
#define PCF8563_REG_HOURS_ALARM					0x0A
#define PCF8563_REG_DAY_ALARM					0x0B
#define PCF8563_REG_WEEK_ALARM					0x0C
#define PCF8563_REG_CLKOUT						0x0D
#define PCF8563_REG_TIMER_CTR					0x0E
#define PCF8563_REG_TIMER 						0x0F

//---I2C设备地址
#define PCF8563_WRITE_ADDR						0xA2
#define PCF8563_READ_ADDR						0xA3

//---CLKOUT的输出
#define PCF8563_CLKOUT_32768HZ					0
#define PCF8563_CLKOUT_1024HZ					1
#define PCF8563_CLKOUT_32HZ						2
#define PCF8563_CLKOUT_1HZ						3

//===结构体定义
typedef struct _RTC_HandlerType					RTC_HandlerType;
//===定义指针结构体
typedef struct _RTC_HandlerType					*pRTC_HandlerType;
//===时钟结构体的定义
struct _RTC_HandlerType
{
	UINT8_T second;								//---秒
	UINT8_T minute;								//---分
	UINT8_T hour;								//---时
	UINT8_T day;								//---天
	UINT8_T week;								//---星期
	UINT8_T month;								//---月
	UINT8_T year;								//---年
	UINT8_T century;							//---世纪
};
//===结构体定义
typedef struct _PCF8563_HandlerType				PCF8563_HandlerType;
//===指针结构体定义
typedef struct _PCF8563_HandlerType				*pPCF8563_HandlerType;
//==PCF853的数据结构体
struct _PCF8563_HandlerType
{
	RTC_HandlerType	msgRTC;						//---实时时钟
	I2C_HandlerType msgI2C;						//---使用的I2C
};

#define PCF8563_HandlerType_Device0
//===外部调用的接口函数
#ifdef PCF8563_HandlerType_Device0
	extern PCF8563_HandlerType g_PCF8563Device0;
	extern pPCF8563_HandlerType pPCF8563Device0;
#endif

//===函数定义
UINT8_T PCF8563_Init(PCF8563_HandlerType *PCF8563HandlerType, void(*msgDelay)(UINT32_T delay));
UINT8_T PCF8563_DeInit(PCF8563_HandlerType *PCF8563HandlerType);
UINT8_T PCF8563_Device0_Init(PCF8563_HandlerType *PCF8563HandlerType);
UINT8_T PCF8563_Device1_Init(PCF8563_HandlerType *PCF8563HandlerType);
UINT8_T PCF8563_ClockOut(PCF8563_HandlerType *PCF8563HandlerType, UINT8_T preVal);
UINT8_T PCF8563_ReadRTC(PCF8563_HandlerType *PCF8563HandlerType);
UINT8_T PCF8563_WriteRTC(PCF8563_HandlerType *PCF8563HandlerType, RTC_HandlerType rtc);
///////////////////////////////////////////////////////////////////////////////
#endif /* PCF8563_CFG_H_ */