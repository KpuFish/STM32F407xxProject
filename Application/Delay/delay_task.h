#ifndef DELAY_TASK_H_
#define DELAY_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
//---ʹ�ð�����ͷ�ļ�
#include "delay_lib.h"
//---��������
void DelayTask_us(UINT32_T us);
void DelayTask_ms(UINT32_T ms);
void DelayTask_s(UINT32_T s);
void DelayTask_nop(UINT32_T nop);
void DelayTask_1us(UINT32_T us);
//////////////////////////////////////////////////////////////////////////////////////
#endif /* DELAY_TASK_H_ */