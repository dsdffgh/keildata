#include "Motor/motor.h"
#include "Sys/sys.h"
void Motor_Init(void)
{
    // 额外初始化方向控制的两个引脚
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(MOTOR1_DIR_GPIO_CLK | MOTOR2_DIR_GPIO_CLK, ENABLE); // 开启Motor1的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = MOTOR1_DIR_FORWARD_PIN | MOTOR1_DIR_BACKWARD_PIN | MOTOR2_DIR_FORWARD_PIN | MOTOR2_DIR_BACKWARD_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR1_DIR_GPIO, &GPIO_InitStructure); // 将Motor1和Motor2引脚初始化为推挽输出
    GPIO_Init(MOTOR2_DIR_GPIO, &GPIO_InitStructure);

    PWM_Init(7200, 0);
}

void Limit_Motor(int *motoA, int *motoB)
{
    if (*motoA > PWM_MAX)
        *motoA = PWM_MAX;
    if (*motoA < PWM_MIN)
        *motoA = PWM_MIN;

    if (*motoB > PWM_MAX)
        *motoB = PWM_MAX;
    if (*motoB < PWM_MIN)
        *motoB = PWM_MIN;
}

int abs(int p)
{
    int q;
    q = p > 0 ? p : (-p);
    return q;
}

/*
    * 函数功能：电机控制
    * 参    数：入口参数即为PID运算完成后的最终PWM值
    *           moto1_pwm 电机1的PWM值
    *           moto2_pwm 电机2的PWM值
    * 返 回 值：无
*/
void Load_Motor(int moto1_pwm, int moto2_pwm)
{
    // 1.研究正负号，对应正反转
    if (moto1_pwm > 0)
        Ain1 = 1, Ain2 = 0; // 正转
    else
        Ain1 = 0, Ain2 = 1; // 反转
    // 2.研究PWM值
    TIM_SetCompare1(TIM1, abs(moto1_pwm));

    // 1.研究正负号，对应正反转
    if (moto2_pwm > 0)
        Bin1 = 1, Bin2 = 0;
    else
        Bin1 = 0, Bin2 = 1;
    // 2.研究PWM值
    TIM_SetCompare4(TIM1, abs(moto2_pwm));
}
