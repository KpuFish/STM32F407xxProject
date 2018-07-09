#include "iwdg_cfg.h"

//---ȫ�ֱ����Ķ���
IWDG_HandlerType g_IWDG =
{
	.msgIWDGx = IWDG,
};

//---ָ��ȫ�ֵ�ָ�����
pIWDG_HandlerType pIWDG = &g_IWDG;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ���� �ڳ�ʼ�����Ź���ʱ����Ҫע��ر�ȫ���жϣ�����ᵼ�¿��Ź�������ʧ�ܣ����ǼĴ���������Ӱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Init(IWDG_HandlerType *IWDGx)
{
	//---��鿴�Ź��Ƿ�ֵ��Ĭ��ʹ�ö������Ź�
	if (IWDGx->msgIWDGx == NULL)
	{
		IWDGx->msgIWDGx = IWDG;
	}
	//---�ر��ж�
	CLI();
	//---ʹ�ܿ��Ź�
	LL_IWDG_Enable(IWDGx->msgIWDGx);
	//---ʹ��Ԥ��Ƶ�Ĵ�������װ�ؼĴ�����д��ȡ���Ĵ�����д������
	LL_IWDG_EnableWriteAccess(IWDGx->msgIWDGx);
	//---����Ԥ��Ƶ��ֵ
	LL_IWDG_SetPrescaler(IWDGx->msgIWDGx, LL_IWDG_PRESCALER_64);
	//---������װ�ؼĴ���ֵ
	LL_IWDG_SetReloadCounter(IWDGx->msgIWDGx, 625);
	//---�ȴ�׼�����
	while (LL_IWDG_IsReady(IWDGx->msgIWDGx) != 1);
	//---��λ���Ź�
	LL_IWDG_ReloadCounter(IWDGx->msgIWDGx);
	//---�����ж�
	SEI();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_DeInit(IWDG_HandlerType *IWDGx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ� ���Ź���λ����
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Reset(IWDG_HandlerType *IWDGx)
{
	//---��鿴�Ź��Ƿ�ֵ��Ĭ��ʹ�ö������Ź�
	if (IWDGx->msgIWDGx == NULL)
	{
		IWDGx->msgIWDGx = IWDG;
	}
	//---��λ���Ź�
	LL_IWDG_ReloadCounter(IWDGx->msgIWDGx);
	return OK_0;
}