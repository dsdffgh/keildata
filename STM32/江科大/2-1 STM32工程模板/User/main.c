#include "Sys/sys.h"

uint8_t ID;						 // 定义用于存放ID号的变量
float Pitch, Roll, Yaw;			 // 欧拉角
int16_t gyro_X, gyro_Y, gyro_Z;	 // 加速度传感器原始数据
int16_t acc_X, acc_Y, acc_Z;	 // 陀螺仪原始数据
int Encoder_left, Encoder_right; // 左右编码器的脉冲计数
int Moto1, Moto2;				 // 计算出来的最终赋给电机的PWM
// loat UltrasonicWave_Distance;					// 超声波测距
// int Flag_Qian, Flag_Hou, Flag_Left, Flag_Right; // 蓝牙遥控相关的变量
// uint8_t flag_UltrasonicWave;
uint8_t flag_fall; // 摔倒标志位
int16_t Speed;

int main(void)
{
	/*模块初始化*/
	delay_init();
	OLED_Init(); // OLED初始化
	NVIC_Configuration();
	//Timer3_Init(100,1);	 // 定时中断初始化
	OLED_Clear(); // OLED清屏
	MPU_Init(); // 陀螺仪软件i2c初始化
	// MPU6050_Init();		 // 陀螺仪硬件i2c初始化
	mpu_dmp_init(); // 陀螺仪DMP初始化
	MPU6050_EXTI_Init(); // 陀螺仪中断初始化
	Encoder_TIM2_Init(); // 不分频
	Encoder_TIM4_Init(); // 不分频
	PWM_Init(0, 7200);	 // PWM初始化, TIM1
	Motor_Init();		 // 电机初始化
	delay_ms(1000);		 // 延时1s
	delay_ms(1000);		 // 延时1s
	//OLED_ShowString(1, 7, "Moto1:", 5); 
	//OLED_ShowString(1, 6, "Moto2:", 5); 	
	uart1_init(9600);
	// OLED_ShowString(4, 1, "ID:");		//显示静态字符串
	// ID = MPU6050_GetID();				//获取MPU6050的ID号
	// OLED_ShowHexNum(4, 4, ID, 2);		//OLED显示ID号
	while (1)
	{
		// MPU6050_GetData(&acc_X, &acc_Y, &acc_Z,&gyro_X, &gyro_Y, &gyro_Z);
		MPU_Get_Gyroscope(&gyro_X, &gyro_Y, &gyro_Z);		MPU_Get_Accelerometer(&acc_X, &acc_Y, &acc_Z);
		OLED_ShowString(7, 1, "gyro", 4); 		OLED_ShowString(70, 1, "acc", 3); 
		OLED_Float(2, 1, gyro_X, 1);		OLED_Float(3, 1, gyro_Y, 1);		OLED_Float(4, 1, gyro_Z, 1);
		//OLED_Float(2, 66, acc_X, 1);		OLED_Float(3, 66, acc_Y, 1);		OLED_Float(4, 66, acc_Z, 1);
		//printf("acc_x = %d\tacc_y = %d\tacc_z = %d\n",acc_X,acc_Y,acc_Z);
		//mpu_dmp_get_data(&Pitch, &Roll, &Yaw);
		//OLED_Float(5, 66, Pitch, 1);		OLED_Float(6, 66, Roll, 1);		OLED_Float(7, 66, Yaw, 1);
		//printf("Pitch = %.2f\tRoll = %.2f\tYaw = %.2f\n\n\n",Pitch, Roll, Yaw);		
		//printf("%.2f\n",Pitch);
		//OLED_Clear(); // OLED清屏
		Encoder_left = Encoder_Get(2);OLED_Float(7, 50, Encoder_left, 2);
		Encoder_right = Encoder_Get(4);OLED_Float(6, 50, Encoder_right, 2);
		Load_Motor(20,20);
	}
}
