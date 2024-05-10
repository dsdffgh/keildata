#include "Sys/sys.h"
#include "Delay/Delay.h"
#include "OLED/OLED.h"
#include "Timer/Timer.h"
#include "Encoder/Encoder.h"

int16_t Speed;					 // 定义在定时器中断里自增的变量
float Pitch, Roll, Yaw;                         // 欧拉角
short gyro_X, gyro_Y, gyro_Z;                      // 加速度传感器原始数据
short acc_X, acc_Y, acc_Z;                         // 陀螺仪原始数据
int Encoder_left, Encoder_right;                // 左右编码器的脉冲计数
int Moto1, Moto2;                               // 计算出来的最终赋给电机的PWM
// loat UltrasonicWave_Distance;					// 超声波测距
// int Flag_Qian, Flag_Hou, Flag_Left, Flag_Right; // 蓝牙遥控相关的变量
// uint8_t flag_UltrasonicWave;
uint8_t flag_fall; // 摔倒标志位

int main(void)
{
	/*模块初始化*/
	OLED_Init(); // OLED初始化
	// Timer3_Init(100,1);	 // 定时中断初始化

	OLED_Clear();		 // OLED清屏
	MPU6050_Init();		 // 陀螺仪初始化
	mpu_dmp_init();		 // 陀螺仪DMP初始化
	MPU6050_EXTI_Init(); // 陀螺仪中断初始化
	Encoder_TIM2_Init(); // 不分频
	Encoder_TIM4_Init(); // 不分频
	Motor_Init();		 // 电机初始化
	PWM_Init(0, 7200);	 // PWM初始化, TIM1
	Delay_ms(1000);		 // 延时1s
	Delay_ms(1000);		 // 延时1s
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Speed:"); // 1行1列显示字符串Num:

	while (1)
	{
		OLED_ShowSignedNum(1, 7, Speed, 5); // 不断刷新显示Num变量
	}
}

/**
 * 函    数：TIM3中断函数
 * 参    数：无
 * 返 回 值：无
 * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
 *           函数名为预留的指定名称，可以从启动文件复制
 *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
 */
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) // 判断是否是TIM3的更新事件触发的中断
	{
		int Speed = Encoder_Get(2);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清除TIM3更新事件的中断标志位
													// 中断标志位必须清除
													// 否则中断将连续不断地触发，导致主程序卡死
	}
}
