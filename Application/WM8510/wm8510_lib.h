#ifndef WM8510_LIB_H_
#define WM8510_LIB_H_
///////////////////////////////////////////////////////////////////////////////////////////

#include "wm8510_cfg.h"

//===º¯Êý¶¨Òå
UINT8_T WM8510Lib_Init(WM8510_HandlerType *WM8510x, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C);
UINT8_T WM8510Lib_DeInit(WM8510_HandlerType *WM8510x, UINT8_T isHWI2C);
UINT8_T WM8510Lib_SetFreqHz(WM8510_HandlerType *WM8510x, UINT32_T freq);
UINT8_T WM8510Lib_SetFreqKHz(WM8510_HandlerType *WM8510x, float freq);
UINT8_T WM8510Lib_SetFreqMHz(WM8510_HandlerType *WM8510x, float freq);
///////////////////////////////////////////////////////////////////////////////////////////
#endif /* WM8510_LIB_H_ */