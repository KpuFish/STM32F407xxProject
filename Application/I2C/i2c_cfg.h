#ifndef I2C_CFG_H_
#define I2C_CFG_H_
///////////////////////////////////////////////////////////////////////////////
//////ʹ�øú��������ȱ�֤GPIO��ʱ���Ѿ�ʹ�ܣ������ڲ��Ѿ����˿�����Ϊ��©���
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "gpio_task.h"
#endif

//===��Ϣ��ģʽ
//---SDA�˿�
#define I2C_SDA_OUT_0(name,index)				GPIO_OUT_0(		name,index )
#define I2C_SDA_OUT_1(name,index)				GPIO_OUT_1(		name,index )
#define I2C_SDA_STATE(name,index)				GPIO_GET_STATE(	name,index )
#define I2C_SDA_READ(name,index)				GPIO_SET_READ(	name,index )
#define I2C_SDA_WRITE(name,index)				GPIO_SET_WRITE(	name,index )

//---SCL�˿�
#define I2C_SCL_OUT_0(name,index)				GPIO_OUT_0(		name,index )
#define I2C_SCL_OUT_1(name,index)				GPIO_OUT_1(		name,index )
#define I2C_SCL_STATE(name,index)				GPIO_GET_STATE(	name,index )
#define I2C_SCL_READ(name,index)				GPIO_SET_READ(	name,index )
#define I2C_SCL_WRITE(name,index)				GPIO_SET_WRITE(	name,index )

//---�ṹ�嶨��
typedef struct _I2C_HandlerType					I2C_HandlerType;
typedef	struct _I2C_HandlerType					*pI2C_HandlerType;

//---��Ϣ���I2C
struct _I2C_HandlerType
{
	I2C_TypeDef		*msgI2Cx;																				//---ʹ�õ�I2C�ӿ�
	GPIO_TypeDef	*msgSclPort;																			//---SCL�˿�
	GPIO_TypeDef	*msgSdaPort;																			//---SDA�˿�
	UINT32_T		msgSclBit;																				//---SCL����
	UINT32_T		msgSdaBit;																				//---SDA����
	UINT8_T			msgModelIsHW;																			//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
	UINT8_T			msgPluseWidth;																			//---�����ȣ����ģ��ʹ��
	void(*msgDelay)(UINT32_T delay);															//---��ʱ����
	UINT16_T		msgAddr;																				//---�豸�ĵ�ַ
	UINT32_T		msgClockSpeed;																			//---Ӳ��I2C��ʱ���ٶ�
	UINT8_T(*msgTask)(I2C_HandlerType I2CxHandlerType, UINT16_T length, UINT8_T *pVal, UINT8_T msg);	//---��Ϣ�崦����
};

//---��������
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
