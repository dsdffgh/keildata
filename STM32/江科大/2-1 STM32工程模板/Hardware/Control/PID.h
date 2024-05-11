#ifndef __PID_H__
#define __PID_H__


int VerticalPidCalc(float Med, float Angle, float Gyro_Y);
int VelocityPidCalc(const int Target, const int realSpeed);
int TurnPidCalc(int Gyro_z);
void EXTI9_5_IRQHandler(void);

#endif
