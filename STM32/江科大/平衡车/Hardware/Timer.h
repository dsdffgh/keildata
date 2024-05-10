#ifndef __TIMER_H
#define __TIMER_H


#define TIM__IRQN TIM3_IRQn 
#define TIM_IRQHandler TIM3_IRQHandler
#define TIM_CLK RCC_APB1Periph_TIM3
#define TIMER TIM3

void Timer3_Init(uint16_t arr, uint16_t psc);

#endif
