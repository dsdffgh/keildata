#ifndef __PWM_H
#define __PWM_H

#include "Sys/sys.h"

#define PWM_TIM_CLK RCC_APB2Periph_TIM1
#define PWM_GPIO_CLK RCC_APB2Periph_GPIOA
#define PWM_TIMER TIM1
#define PWM_GPIO GPIOA
#define TIM1_CHA1 GPIO_Pin_8
#define TIM1_CHA4 GPIO_Pin_11

// 限幅量
#define PWM_MAX  7200
#define PWM_MIN  -7200

void PWM_Init(uint16_t arr, uint16_t psc);
void PWM_SetCompare3(uint16_t Compare);

#endif
