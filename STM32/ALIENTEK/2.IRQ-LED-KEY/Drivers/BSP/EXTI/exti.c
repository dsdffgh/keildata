/*
 * =====================================================================================
 *
 *       Filename:  exti.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  3/10/2024 11:46:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Theonesssssssss (), whyunotdo@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "./BSP/EXTI/exti.h"

void exti_init(void)
{
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	GPIO_InitTypeDef gpio_init_struct;

    gpio_init_struct.Pin = GPIO_PIN_4;                   
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;           
    gpio_init_struct.Pull = GPIO_PULLUP;                   
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);       //	PE4 : KEY0

	HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	
}

void EXTI4_IRQHandler(void)
{
	//	调用公共处理函数
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//	按键按下，消抖
	delay_ms(20);
	
	if(GPIO_Pin == GPIO_PIN_4)
	{
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4) == 0 )
		{
			//	翻转LED
			HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
		}
	}
	
}
