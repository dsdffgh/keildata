#include "Sys/sys.h"
uint8_t ID;								//定义用于存放ID号的变量
float Pitch, Roll, Yaw;			 // 欧拉角
int16_t gyro_X, gyro_Y, gyro_Z;	 // 加速度传感器原始数据
int16_t acc_X, acc_Y, acc_Z;		 // 陀螺仪原始数据
int Encoder_left, Encoder_right; // 左右编码器的脉冲计数
int Moto1, Moto2;				 // 计算出来的最终赋给电机的PWM
// loat UltrasonicWave_Distance;					// 超声波测距
// int Flag_Qian, Flag_Hou, Flag_Left, Flag_Right; // 蓝牙遥控相关的变量
// uint8_t flag_UltrasonicWave;
uint8_t flag_fall; // 摔倒标志位

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化k
	//MPU6050_Init();		 // 陀螺仪硬件i2c初始化
	//OLED_ShowString(4, 1, "ID:");		//显示静态字符串
	//ID = MPU6050_ReadReg(MPU_DEVICE_ID_REG);				//获取MPU6050的ID//号
	//OLED_ShowHexNum(4, 4, ID, 2);		//OLED显示ID号
	MPU_Init();		//MPU6050初始化
	//delay_ms(1000);

	//while(mpu_dmp_init());		 // 陀螺仪DMP初始化
//OLED_Clear();
	/*显示ID号*/

	
	while (1)
	{

		MPU6050_GetData(&acc_X, &acc_Y, &acc_Z,&gyro_X, &gyro_Y, &gyro_Z);
		//MPU_Get_Gyroscope(&gyro_X, &gyro_Y, &gyro_Z);
		//MPU_Get_Accelerometer(&acc_X, &acc_Y, &acc_Z);
		OLED_ShowSignedNum(1, 1, gyro_X, 5); 
		OLED_ShowSignedNum(2, 1, gyro_Y, 5); 
		OLED_ShowSignedNum(3, 1, gyro_Z, 5); 
		OLED_ShowSignedNum(1, 8, acc_X, 5); 
		OLED_ShowSignedNum(2, 8, acc_Y, 5); 
		OLED_ShowSignedNum(3, 8, acc_Z, 5); 
	}
}
