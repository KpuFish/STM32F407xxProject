#ifndef DELAY_CFG_H_
#define DELAY_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
//---使用包含的头文件
#include "complier_lib.h"
#ifdef USE_MCU_STM32
#include "systick_task.h"
#endif
//---函数定义
void Delay_us(UINT32_T us);
void Delay_ms(UINT32_T ms);
void Delay_s(UINT32_T s);
void DelayN_us(UINT32_T us);
void DelayN_ms(UINT32_T ms);
void DelayN_s(UINT32_T s);
void Delay_nop(UINT32_T nop);
void Delay_1us(UINT32_T us);
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DELAY_CFG_H_ */
