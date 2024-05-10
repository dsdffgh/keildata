/*
 * =====================================================================================
 *
 *       Filename:  key.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  3/8/2024 9:27:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Theonesssssssss (), whyunotdo@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "./BSP/KEY/key.h"

void key_init()
{
    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_GPIOE_CLK_ENABLE();

    gpio_init_struct.Pin = GPIO_PIN_4;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(GPIOE, &gpio_init_struct);

}

uint8_t key_scan()
{
    if( HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0 )
    {
        delay_ms( 10 );                         /* 消抖 */

        if( HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0 )
        {
            while(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0 );
            return 1;
        }

    }
    return 0;
}