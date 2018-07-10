#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ϵͳʱ�ӵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---����FLASH����ʱ��ȡ������
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---�ȴ�FLASH��ʱ�������---�ж������Ƿ�ɹ�
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
	//---�����ڲ��������������ѹ
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	//---ʹ���ⲿ����
	LL_RCC_HSE_Enable();
	//---�ȴ��ⲿ�����ȶ�
	while (LL_RCC_HSE_IsReady() != 1)
	{
	}
	//---ʹ���ڲ���Ƶ����
	LL_RCC_LSI_Enable();
	//---�ȴ��ڲ���Ƶ�����ȶ�
	while (LL_RCC_LSI_IsReady() != 1)
	{
	}
	//---ʹ�ܱ�����ķ���
	LL_PWR_EnableBkUpAccess();
	//---ǿ�Ʊ�����ĸ�λ
	LL_RCC_ForceBackupDomainReset();
	//---�ͷŶԱ�����ķ���
	LL_RCC_ReleaseBackupDomainReset();
	//---����RTCʱ��
	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE);
	//---����RTCʱ�ӷ�Ƶ��
	LL_RCC_SetRTC_HSEPrescaler(LL_RCC_RTC_HSE_DIV_8);
	//---ʹ��RTC
	LL_RCC_EnableRTC();
	//---����ϵͳ��PLL
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
	//---����USBʱ��
	LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	//---ʹ��PLL
	LL_RCC_PLL_Enable();
	//---�ȴ�PLL�ȶ�
	while (LL_RCC_PLL_IsReady() != 1)
	{
	}
	//---����AHB����ʱ�ӷ�Ƶ
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	//---����APB1����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	//---����APB2����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	//---����ϵͳʱ��
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	//--- �ȴ�ϵͳʱ���ȶ�
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}
	//---����ϵͳ�δ�ʱ����ʱ��Ϊϵͳ����ʱ��--ʹ�ܵδ�ʱ����ʱ��
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	//---����ϵͳʱ��
	LL_SetSystemCoreClock(168000000);
	//---ʹ��Flash��Ԥ��ȡ����
	LL_FLASH_EnablePrefetch();
	//---ʹ�����ݻ���
	LL_FLASH_EnableDataCache();
	//---ʹ��ָ����ٻ���
	LL_FLASH_EnableInstCache();
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void NVIC_Init(void)
{
	//---PWRʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	//---����NVIC�ķ���ģʽ
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* BusFault_IRQn interrupt configuration */
	NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* UsageFault_IRQn interrupt configuration */
	NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* SVCall_IRQn interrupt configuration */
	NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* DebugMonitor_IRQn interrupt configuration */
	NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* PendSV_IRQn interrupt configuration */
	NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void Sys_Init(void)
{
	SystemClock_Config();
	NVIC_Init();
	GPIOTask_Init();
	SysTickTask_Init();
	RandomTask_Init();

	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(GPIOB, 1);
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = LL_GPIO_PIN_13;						//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;					//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;				//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---����ʹ��
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;				//---�˿ڸ���ģʽ
#endif
															//---��ʼ���˿�
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_OUT_1(GPIOB, LL_GPIO_PIN_13);

	DHT11_Init(pDHT11Device0,DelayTask_us,DelayTask_ms);
	DHT11_Read(pDHT11Device0);

}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	//---ϵͳ��ʼ������
	Sys_Init();
	//---��ѭ��
	while (1)
	{
        DHT11_Read(pDHT11Device0);
		DelayTask_ms(500);
		DelayTask_ms(500);
	}
}