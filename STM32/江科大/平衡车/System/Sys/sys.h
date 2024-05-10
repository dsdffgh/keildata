#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"
#include "Delay/Delay.h"
#include "Usart/usart.h"
// #include "usart3.h"
#include "LED.h"
#include "OLED.h"
#include "key.h"
#include "pwm.h"
// #include "usb.h"
#include "Timer.h"
// #include "ADC/adc.h"
// #include "UltrasonicWave.h"
#include "motor.h"
#include "PID.h"
#include "encoder.h"
#include "MPU6050jkd.h"
#include "mpu6050_i2c.h"
#include "MPU6050_exti.h"
#include "MPU6050_Reg.h"
#include "mpuiic.h"
#include "MyI2C.h"
#include "eMPL/inv_mpu.h"
#include "eMPL/inv_mpu_dmp_motion_driver.h"
#include "eMPL/dmpKey.h"
#include "eMPL/dmpmap.h"
// #include "MODE_Select.h"
////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// 位带操作,实现51类似的GPIO控制功能
// 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
// IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 12) // 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12) // 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12) // 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12) // 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12) // 0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8) // 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8) // 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8) // 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8) // 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8) // 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8) // 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8) // 0x40011E08

// IO口操作,只对单一的IO口!
// 确保n的值小于16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) // 输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  // 输入

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) // 输出
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  // 输入

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) // 输出
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  // 输入

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) // 输出
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  // 输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) // 输出
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  // 输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) // 输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // 输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) // 输出
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  // 输入

/////////////////////////////////////////////////////////////////
// Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6

#define FTIR 1 // 下降沿触发
#define RTIR 2 // 上升沿触发

// JTAG模式设置定义
#define JTAG_SWD_DISABLE 0X02
#define SWD_ENABLE 0X01
#define JTAG_SWD_ENABLE 0X00

extern float Voltage; // 电池电压采样相关的变量

extern float Pitch, Roll, Yaw;                         // 欧拉角
extern int16_t gyro_X, gyro_Y, gyro_Z;                      // 加速度传感器原始数据
extern int16_t acc_X, acc_Y, acc_Z;                         // 陀螺仪原始数据
extern int Encoder_left, Encoder_right;                // 左右编码器的脉冲计数
extern int Moto1, Moto2;                               // 计算出来的最终赋给电机的PWM
extern float UltrasonicWave_Distance;                  // 超声波测距
extern int Flag_Qian, Flag_Hou, Flag_Left, Flag_Right; // 蓝牙遥控相关的变量
extern uint8_t flag_UltrasonicWave;
extern uint8_t flag_fall;
void NVIC_Configuration(void); // 中断优先级设置
#endif
