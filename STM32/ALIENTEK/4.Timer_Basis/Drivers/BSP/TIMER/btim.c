/*
 * =====================================================================================
 *
 *       Filename:  btim.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  3/15/2024 7:11:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Theonesssssssss (), whyunotdo@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_tim_handle;

/* 定時器中斷初始化函數 */
void btim_timx_int_init(uint16_t psc, uint16_t arr)
{
    --psc;
	--arr;
	g_tim_handle.Instance = TIM6;
    g_tim_handle.Init.Prescaler = psc;
    g_tim_handle.Init.Period = arr;
    HAL_TIM_Base_Init(&g_tim_handle);

    HAL_TIM_Base_Start_IT(&g_tim_handle);
}

/* 定時器基礎MSP初始化函數 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{

    if ( htim->Instance == TIM6 ) {
        __HAL_RCC_TIM6_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM6_IRQn, (uint32_t)1, (uint32_t)3);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
    }
}

/* 定時器6中斷服務函數 */
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_tim_handle);
}

/* 定時器溢出中斷中斷回調函數 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    //  toggle led

    if ( htim->Instance == TIM6 ) {
        LED1_TOGGLE();
    }
}