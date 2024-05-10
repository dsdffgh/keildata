#ifndef __PID_H__
#define __PID_H__

#include "Sys/sys.h"
#include "MPU6050/eMPL/inv_mpu.h"

int VerticalPidCalc(float Med, float Angle, float Gyro_Y);
int VelocityPidCalc(const int Target, const int realSpeed);
int TurnPidCalc(int Gyro_z);
void EXTI9_5_IRQHandler(void);

#endif
