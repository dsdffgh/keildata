#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/******************************* RW registers
int main(void)
{
	RCC->APB2ENR = 0x00000008;	// open GPIOB timer 
	GPIOB->CRL = 0x00300000;	// 00:Push-Pull	Pin5 11:max speed 50MHZ
	
//	GPIOB->ODR = 0x00000000;
	GPIOB->ODR = 0x00000020;
	while(1)
	{
	 
	}
}
********************************/

/****************************** 标准库 ****************************/
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	Delay_ms(10);
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
	Delay_ms(10);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
}
