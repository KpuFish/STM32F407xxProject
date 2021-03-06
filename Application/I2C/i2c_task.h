#ifndef I2C_TASK_H_
#define I2C_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#include "i2c_lib.h"
//---��������
UINT8_T I2CTask_MSW_Init(I2C_HandlerType *I2Cx, void(*msgDelay)(UINT32_T delay));
UINT8_T I2CTask_MSW_DeInit(I2C_HandlerType *I2Cx);
UINT8_T I2CTask_MSW_START(I2C_HandlerType *I2Cx, UINT8_T isWrite);
UINT8_T I2CTask_MSW_STOP(I2C_HandlerType *I2Cx);
UINT8_T I2CTask_MSW_ReadACK(I2C_HandlerType *I2Cx);
UINT8_T I2CTask_MSW_SendACK(I2C_HandlerType *I2Cx, UINT8_T isNACK);
UINT8_T I2CTask_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val);
UINT8_T I2CTask_MSW_ReadByte(I2C_HandlerType *I2Cx);
UINT8_T I2CTask_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);
UINT8_T I2CTask_MSW_Send(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT16_T length);
UINT8_T I2CTask_MSW_Read(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT16_T length);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_TASK_H_ */
