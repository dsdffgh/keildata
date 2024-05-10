#ifndef __ENCODER_H__
#define __ENCODER_H__

void Encoder_TIM2_Init(void); // 编码器1初始化函数
void Encoder_TIM4_Init(void); // 编码器2初始化函数
int16_t Encoder_Get(int TIMx);
void TIM2_IRQHandler(void); // 定时器2中断服务函数
void TIM4_IRQHandler(void); // 定时器4中断服务函数

#endif
