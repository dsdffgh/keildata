#ifndef __MPU6050_H
#define __MPU6050_H

#include "Sys/sys.h"
#include "MPU6050/MPU6050_Reg.h"
#include "MPU6050/eMPL/inv_mpu.h"

#define MPU6050_ADDRESS 0xD0 // MPU6050的I2C从机地址
#define MPU6050_GPIO_CLK RCC_APB2Periph_GPIOB
#define MPU6050_I2C2 I2C2
#define MPU6050_I2C_CLK RCC_APB1Periph_I2C2
#define MPU6050_I2C_SCL GPIO_Pin_10
#define MPU6050_I2C_SDA GPIO_Pin_11

int MPU6050_WaitEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
uint8_t MPU6050_ReadRegs(uint8_t Address, uint8_t RegAddress, uint8_t Length, uint8_t *pBuffer);
uint8_t MPU6050_WriteRegs(uint8_t Address, uint8_t RegAddress, uint8_t Length, const uint8_t *pBuffer);

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
					  int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
void MPU6050_GETAccelerometer(int16_t *AccX, int16_t *AccY, int16_t *AccZ);
void MPU6050_GETGyroscope(int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

#endif
