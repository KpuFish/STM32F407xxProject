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

//===消息体模式
//---SDA端口
#define I2C_SDA_OUT_0(name,index)				GPIO_OUT_0(		name,index )
#define I2C_SDA_OUT_1(name,index)				GPIO_OUT_1(		name,index )
#define I2C_SDA_STATE(name,index)				GPIO_GET_STATE(	name,index )
#define I2C_SDA_READ(name,index)				GPIO_SET_READ(	name,index )
#define I2C_SDA_WRITE(name,index)				GPIO_SET_WRITE(	name,index )

//---SCL端口
#define I2C_SCL_OUT_0(name,index)				GPIO_OUT_0(		name,index )
#define I2C_SCL_OUT_1(name,index)				GPIO_OUT_1(		name,index )
#define I2C_SCL_STATE(name,index)				GPIO_GET_STATE(	name,index )
#define I2C_SCL_READ(name,index)				GPIO_SET_READ(	name,index )
#define I2C_SCL_WRITE(name,index)				GPIO_SET_WRITE(	name,index )

//---结构体定义
typedef struct _I2C_HandlerType					I2C_HandlerType;
typedef	struct _I2C_HandlerType					*pI2C_HandlerType;

//---消息体的I2C
struct _I2C_HandlerType
{
	I2C_TypeDef		*msgI2Cx;																				//---使用的I2C接口
	GPIO_TypeDef	*msgSclPort;																			//---SCL端口
	GPIO_TypeDef	*msgSdaPort;																			//---SDA端口
	UINT32_T		msgSclBit;																				//---SCL引脚
	UINT32_T		msgSdaBit;																				//---SDA引脚
	UINT8_T			msgModelIsHW;																			//---工作模式，默认是软件模拟---0，硬件模式---1
	UINT8_T			msgPluseWidth;																			//---脉冲宽度，软件模拟使用
	void(*msgDelay)(UINT32_T delay);															//---延时参数
	UINT16_T		msgAddr;																				//---设备的地址
	UINT32_T		msgClockSpeed;																			//---硬件I2C的时钟速度
	UINT8_T(*msgTask)(I2C_HandlerType I2CxHandlerType, UINT16_T length, UINT8_T *pVal, UINT8_T msg);	//---消息体处理函数
};

//---函数定义
UINT8_T I2C_HandlerType_Init(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2CxHandlerType, void(*msgDelay)(UINT32_T delay));
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_START(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2CxHandlerType, UINT8_T isNACK);
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2CxHandlerType, UINT8_T val);
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum);
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2CxHandlerType);
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2CxHandlerType, UINT8_T *pVal, UINT8_T bitNum);
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2CxHandlerType, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);

//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_CFG_H_ */
