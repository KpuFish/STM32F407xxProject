#include "systick_cfg.h"

//---��������
SysTick_HandlerType		g_SysTick;
pSysTick_HandlerType	pSysTick = &g_SysTick;

#if defined (USE_HAL_DRIVER)
	//---�ⲿ���õ�Hal����ʱ����
	extern HAL_TickFreqTypeDef uwTickFreq;
#endif 

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Suspend(void)
{
	#ifdef USE_MCU_STM32
		//---��ʹ��ϵͳ�δ�ʱ�����ж�
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Resume(void)
{
	#ifdef USE_MCU_STM32
		//---ʹ��ϵͳ�δ�ʱ�����ж�
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� SysTickʹ�õĽṹ��ĳ�ʼ��
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_StructInit(SysTick_HandlerType *sysTickx)
{
	sysTickx->msgInc = 0;
	sysTickx->msgDec = 0;
	sysTickx->msgOVF = 0;
	sysTickx->msgTaskInc = 0;
	sysTickx->msgTaskMax = 0;
	sysTickx->msgFuncTaskHal = NULL;
	sysTickx->msgFuncTaskFunc = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���1ms�ĵδ�ʱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Init(void)
{
	//---��ʼ���ṹ��
	SysTick_StructInit(pSysTick);
	//---���ܳ�ʼ��
	#ifdef USE_MCU_STM32
		//---����δ�ʱ��
		SysTick_Suspend();
		//---����1ms��ʱ��δ���---�ó�ʼ������û��ע���ж�
		LL_InitTick(SystemCoreClock, 1000);
		//---�����ж���ռ����
		NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
		//---���õδ�ʱ���ж�---����Ϊ������ȼ�
		NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
		//---ʹ�ܵδ�ʱ���ж�---Ĭ����1ms
		SysTick_Resume();
		#if defined (USE_HAL_DRIVER)
			//---Hal��������ʱ����
			uwTickFreq = HAL_TICK_FREQ_DEFAULT;
			//---ע��Hal�������
			pSysTick->msgFuncTaskHal = HAL_IncTick;
		#endif
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_DeInit(void)
{
	#ifdef USE_MCU_STM32
		SysTick_Suspend();
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_TickTask(UINT32_T tickFreq, void(*TickTask)(void))
{
	if ((TickTask != NULL) && (pSysTick != NULL))
	{
		//---ע��������
		pSysTick->msgFuncTaskFunc = TickTask;
		//---���������������
		pSysTick->msgTaskInc = 0;
		//---����������������������
		pSysTick->msgTaskMax = tickFreq;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQDecTick(UINT32_T waitDecTick)
{
	if (pSysTick != NULL)
	{
		//---��ʱ����
		pSysTick->msgDec = waitDecTick;
		//---�ȴ�ʱ�䵽��
		while (pSysTick->msgDec != 0)
		{
			WDT_RESET();
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTick(void)
{
	if (pSysTick != NULL)
	{
		return pSysTick->msgInc;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQTask(void)
{
	if (pSysTick != NULL)
	{
		//---�ݼӼ���
		pSysTick->msgInc++;
		pSysTick->msgTaskInc++;
		//---�ж��Ƿ����
		if (pSysTick->msgInc == 0)
		{
			pSysTick->msgOVF++;
		}
		//---ע��hal��ʱ����
		if (pSysTick->msgFuncTaskHal != NULL)
		{
			pSysTick->msgFuncTaskHal();
		}
		//---�ж�������
		if ((pSysTick->msgTaskMax != 0) && (pSysTick->msgTaskMax == pSysTick->msgTaskInc) && (pSysTick->msgFuncTaskFunc != NULL))
		{
			pSysTick->msgTaskInc = 0;
			pSysTick->msgFuncTaskFunc();
		}
		//---�ݼ�����
		if (pSysTick->msgDec != 0)
		{
			pSysTick->msgDec--;
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_WaitTick(UINT32_T usTimer)
{
	#ifdef USE_MCU_STM32
		UINT32_T load = SysTick->LOAD;
		UINT32_T ctrl = SysTick->CTRL;
		UINT32_T val  = SysTick->VAL;
		//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
		SysTick->CTRL = 0x00000004;
		//---����װ��ֵ
		SysTick->LOAD = usTimer*(SYS_CLOCK_MHZ - 1);
		//---���������
		SysTick->VAL = 0x00;
		//---ʹ�ܼ���������
		SysTick->CTRL |= 0x01;
		//---�ȴ�������0
		while (!(SysTick->CTRL & 0x00010000))
		{
			WDT_RESET();
		}
		//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
		SysTick->CTRL = 0x00000004;
		//---�ָ�װ��ֵ
		SysTick->LOAD = load;
		//---��������������
		SysTick->VAL = val;
		//---�ָ�����������
		SysTick->CTRL = ctrl;
	#endif
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����ж�ϵͳ�δ�ʱ���ǲ���1ms�Ķ�ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_1msTick(void)
{
	#ifdef USE_MCU_STM32
		//---�ж�ʱ��Դ�Ƿ����8��Ƶ
		if ((SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk)!=0)
		{
			//===ʱ��Դû�н���8��Ƶ
			if (SysTick->LOAD != (SYS_CLOCK_KHZ - 1))
			{
				return ERROR_1;
			}
		}
		else
		{
			//===ʱ��Դ����8��Ƶ
			if (SysTick->LOAD != (SYS_CLOCK_KHZ/8 - 1))
			{
				return ERROR_1;
			}
		}
	#endif 
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ȡ��������Ĵ�С
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTickOVF(void)
{
	return pSysTick->msgOVF;
}