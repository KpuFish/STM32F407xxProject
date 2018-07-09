#ifndef DELAY_LIB_H_
#define DELAY_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
//---使用包含的头文件
#include "delay_cfg.h"
//---函数定义
void DelayLib_us(UINT32_T us);
void DelayLib_ms(UINT32_T ms);
void DelayLib_s(UINT32_T s);
void DelayNLib_us(UINT32_T us);
void DelayNLib_ms(UINT32_T ms);
void DelayNLib_s(UINT32_T s);
void DelayLib_nop(UINT32_T nop);
void DelayLib_1us(UINT32_T us);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* DELAY_LIB_H_ */