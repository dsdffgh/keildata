#include "PWM/PWM.h"

/**
 * 函    数：PWM初始化
 * 参    数：无
 * 返 回 值：无
 */
void PWM_Init(uint16_t arr, uint16_t psc)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(PWM_TIM_CLK, ENABLE);  // 开启PWM_TIMER的时钟
	RCC_APB2PeriphClockCmd(PWM_GPIO_CLK, ENABLE); // 开启PWM的时钟

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出,权限交给外设控制，输出PWM波形
	GPIO_InitStructure.GPIO_Pin = TIM1_CHA1 | TIM1_CHA4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIO, &GPIO_InitStructure); // 将PA2引脚初始化为复用推挽输出
											  // 受外设控制的引脚，均需要配置为复用模式

	/*配置时钟源*/
	TIM_InternalClockConfig(PWM_TIMER); // 选择PWM_TIMER为内部时钟，若不调用此函数，TIM默认也为内部时钟

	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				// 定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = (arr - 1);				// 计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = (psc - 1);			// 预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			// 重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(PWM_TIMER, &TIM_TimeBaseInitStructure);		// 将结构体变量交给TIM_TimeBaseInit，配置PWM_TIMER的时基单元

	/*输出比较初始化*/
	TIM_OCInitTypeDef TIM_OCInitStructure;						  // 定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);						  // 结构体初始化，若结构体没有完整赋值
																  // 则最好执行此函数，给结构体所有成员都赋一个默认值
																  // 避免结构体初值不确定的问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			  // 输出比较模式，选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // 输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;							  // 初始的CCR值
	TIM_OC1Init(PWM_TIMER, &TIM_OCInitStructure);				  // 将结构体变量交给TIM_OC1Init，配置TIM1的通道1
	TIM_OC4Init(PWM_TIMER, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(PWM_TIMER, ENABLE); // 高级定时器 MOE 主输出使能
	/* 为了避免在更新比较值时产生不希望的PWM波形，可以使用预装载寄存器暂存新的比较值，并在适当的时刻（如当前计数周期结束）一次性更新到实际比较寄存器中。这样可以确保PWM波形平滑且无干扰地变化。*/
	TIM_OC1PreloadConfig(PWM_TIMER, TIM_OCPreload_Enable); // CH1预装载使能
	TIM_OC4PreloadConfig(PWM_TIMER, TIM_OCPreload_Enable); // CH4预装载使能

	TIM_ARRPreloadConfig(PWM_TIMER, ENABLE); // 使能TIMx在ARR上的预装载寄存器

	/*TIM使能*/
	TIM_Cmd(PWM_TIMER, ENABLE); // 使能TIM1，定时器开始运行
}

/**
 * 函    数：PWM设置CCR
 * 参    数：Compare 要写入的CCR的值，范围：0~100
 * 返 回 值：无
 * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
 *           占空比Duty = CCR / (ARR + 1)
 */
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(PWM_TIMER, Compare); // 设置CCR3的值
}
