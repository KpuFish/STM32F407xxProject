#include "iwdg_cfg.h"

//---全局变量的定义
IWDG_HandlerType g_IWDG =
{
	.msgIWDGx = IWDG,
};

//---指向全局的指针变量
pIWDG_HandlerType pIWDG = &g_IWDG;

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明： 在初始化看门狗的时候需要注意关闭全局中断，否则会导致看门狗的设置失败，但是寄存器操作无影响
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Init(IWDG_HandlerType *IWDGx)
{
	//---检查看门狗是否赋值，默认使用独立看门狗
	if (IWDGx->msgIWDGx == NULL)
	{
		IWDGx->msgIWDGx = IWDG;
	}
	//---关闭中断
	CLI();
	//---使能看门狗
	LL_IWDG_Enable(IWDGx->msgIWDGx);
	//---使能预分频寄存器和重装载寄存器可写（取消寄存器的写保护）
	LL_IWDG_EnableWriteAccess(IWDGx->msgIWDGx);
	//---设置预分频器值
	LL_IWDG_SetPrescaler(IWDGx->msgIWDGx, LL_IWDG_PRESCALER_64);
	//---设置重装载寄存器值
	LL_IWDG_SetReloadCounter(IWDGx->msgIWDGx, 625);
	//---等待准备完成
	while (LL_IWDG_IsReady(IWDGx->msgIWDGx) != 1);
	//---复位看门狗
	LL_IWDG_ReloadCounter(IWDGx->msgIWDGx);
	//---开启中断
	SEI();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_DeInit(IWDG_HandlerType *IWDGx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能： 看门狗复位操作
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Reset(IWDG_HandlerType *IWDGx)
{
	//---检查看门狗是否赋值，默认使用独立看门狗
	if (IWDGx->msgIWDGx == NULL)
	{
		IWDGx->msgIWDGx = IWDG;
	}
	//---复位看门狗
	LL_IWDG_ReloadCounter(IWDGx->msgIWDGx);
	return OK_0;
}