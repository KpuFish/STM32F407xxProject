#ifndef I2C_CFG_H_
#define I2C_CFG_H_
///////////////////////////////////////////////////////////////////////////////
//////使用该函数，首先保证GPIO的时钟已经使能，函数内部已经将端口配置为开漏输出
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "gpio_task.h"
#endif

//===定义结构体
typedef struct _I2C_HandlerType					I2C_HandlerType;
//===定义指针结构体
typedef	struct _I2C_HandlerType					*pI2C_HandlerType;

//===结构定义
struct _I2C_HandlerType
{
	I2C_TypeDef		*msgI2Cx;																				//---使用的I2C接口
	GPIO_TypeDef	*msgSclPort;																			//---SCL端口
	GPIO_TypeDef	*msgSdaPort;																			//---SDA端口
	UINT32_T		msgSclBit;																				//---SCL引脚
	UINT32_T		msgSdaBit;																				//---SDA引脚
	UINT8_T			msgModelIsHW;																			//---工作模式，默认是软件模拟---0，硬件模式---1
	UINT8_T			msgPluseWidth;																			//---脉冲宽度，软件模拟使用
	UINT16_T		msgAddr;																				//---设备的地址
	UINT32_T		msgClockSpeed;																			//---硬件I2C的时钟速度
	void(*msgFuncDelay)(UINT32_T delay);															            //---延时参数
};
//===函数定义
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2Cx, void(*msgDelay)(UINT32_T delay));
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_START(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2Cx, UINT8_T isNACK);
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val);
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2Cx);
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_CFG_H_ */
