#include "stm32f10x.h"                  // Device header
#include "CountSensor.h"

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//	AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	//	EXIT
	EXTI_InitTypeDef EXIT_InitStruct;
	EXIT_InitStruct.EXTI_Line = EXTI_Line14 ;
	EXIT_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXIT_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXIT_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXIT_InitStruct);
	
	//	NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET )
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

