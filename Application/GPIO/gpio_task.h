#ifndef GPIO_TASK_H_
#define GPIO_TASK_H_
///////////////////////////////////////////////////////////////////////////////
//---使用包含的头文件
#include "gpio_lib.h"
//---函数定义
void GPIOTask_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable);
void GPIOTask_Init(void);
///////////////////////////////////////////////////////////////////////////////
#endif /* GPIO_TASK_H_ */