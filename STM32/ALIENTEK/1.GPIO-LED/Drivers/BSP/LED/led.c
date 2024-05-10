/*
 * =====================================================================================
 *
 *       Filename:  led.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  3/8/2024 8:23:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Theonesssssssss (), whyunotdo@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "./BSP/LED/led.h"

void led_init()
{
    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_GPIOB_CLK_ENABLE();

    gpio_init_struct.Pin = GPIO_PIN_5;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}