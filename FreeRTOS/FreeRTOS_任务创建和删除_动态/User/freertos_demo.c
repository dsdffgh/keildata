/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 移植实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 战舰F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1
#define START_TASK_STACK_SIZE 128
TaskHandle_t start_task_handler;
void start_task(void *pvParameters);

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO 2
#define TASK1_STACK_SIZE 128
TaskHandle_t task1_handler;
void task1_task(void *pvParameters);

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO 3
#define TASK2_STACK_SIZE 128
TaskHandle_t task2_handler;
void task2_task(void *pvParameters);

/* TASK3 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO 4
#define TASK3_STACK_SIZE 128
TaskHandle_t task3_handler;
void task3_task(void *pvParameters);
/******************************************************************************************************/
/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    xTaskCreate((TaskFunction_t)start_task,
                (char *)"start_task", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                (configSTACK_DEPTH_TYPE)START_TASK_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)START_TASK_PRIO,
                (TaskHandle_t *)start_task_handler);
    vTaskStartScheduler(); // 创建任务之后必须开启任务调度器函数，任务才会调度
}
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); // 进入临界区，屏蔽更高优先级的中断
    xTaskCreate((TaskFunction_t)task1_task,
                (char *)"task1", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                (configSTACK_DEPTH_TYPE)TASK1_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_PRIO,
                (TaskHandle_t *)task1_handler);
    xTaskCreate((TaskFunction_t)task2_task,
                (char *)"task2", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                (configSTACK_DEPTH_TYPE)TASK2_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_PRIO,
                (TaskHandle_t *)task2_handler);
    xTaskCreate((TaskFunction_t)task3_task,
                (char *)"task3", /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                (configSTACK_DEPTH_TYPE)TASK3_STACK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_PRIO,
                (TaskHandle_t *)task3_handler);
    vTaskDelete(NULL);
    taskEXIT_CRITICAL(); // 退出临界区
}
/*
 * LED 500ms Toggle
 */
void task1_task(void *pvParameters)
{
    while (1)
    {
        printf("task1正在运行\r\n");
        LED0_TOGGLE();
        vTaskDelay(500);
    }
}

/*
 * LED 500ms Toggle
 */
void task2_task(void *pvParameters)
{
    while (1)
    {
        printf("task2正在运行\r\n");
        LED1_TOGGLE();
        vTaskDelay(500);
    }
}

/*
 * 判断按键key0，按下删除task1
 */
void task3_task(void *pvParameters)
{
    uint8_t key = 0;
    while (1)
    {
        printf("task3正在运行\r\n");
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
            if (task1_handler != NULL)
            {
                printf("task3正在删除\r\n");
                vTaskDelete(task1_handler);
            }
        }

        vTaskDelay(10);
    }
}
