#include "iwdg_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGLib_Init(IWDG_HandlerType *IWDGx)
{
	return IWDG_Init(IWDGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGLib_DeInit(IWDG_HandlerType *IWDGx)
{
	return IWDG_DeInit(IWDGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDGLib_Reset(IWDG_HandlerType *IWDGx)
{
	return IWDG_Reset(IWDGx);
}