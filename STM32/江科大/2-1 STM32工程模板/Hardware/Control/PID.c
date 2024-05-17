#include "Sys/sys.h"
#include "Control/PID.h"
//  PWM_out=Kp×e(k)+Ki×Σe(k)+Kd×[e(k)-e(k-1)]
#define LowPass_exper 0.7 // 低通滤波经验参数
#define Limit_Uppper 10000
#define Limit_Lower -10000

float Med_Angle = 3.932846655791188; // 机械中值，能使得小车真正平衡住的角度
float Target_Speed = 0;  // 期望速度。---二次开发接口，用于控制小车前进后退及其速度。
float
    Vertical_Kp = 200,
    Vertical_Kd = 0.5; // 直立环Kp、Kd
float
    Velocity_Kp = 0.30,
    Velocity_Ki = 0.0015; // 速度环Kp、Ki（正反馈）
float
    Turn_Kp = -0.6;
int Vertical_out, Velocity_out, Turn_out; // 直立环&速度环&转向环的输出变量

void EXTI9_5_IRQHandler(void)
{
  int PWM_out;
  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    if (PBin(5))
    {
      // 陀螺仪中断
      EXTI_ClearITPendingBit(EXTI_Line5);
      /*  读取陀螺仪数据 ，Encoder_left和Encoder_right 在主函数里定义的 */
      Encoder_left = -Encoder_Get(2);
      Encoder_right = Encoder_Get(4);

      /* 读取角度 */
      mpu_dmp_get_data(&Pitch, &Roll, &Yaw);
      // MPU6050_GETGyroscope(&gyro_X, &gyro_Y, &gyro_Z);  // 读取角速度
      // MPU6050_GETAccelerometer(&acc_X, &acc_Y, &acc_Z); // 读取加速度
      MPU_Get_Gyroscope(&gyro_X, &gyro_Y, &gyro_Z);
      MPU_Get_Accelerometer(&acc_X, &acc_Y, &acc_Z);

      /* 进入闭环控制 ，计算控制输出量 */
      Velocity_out = VelocityPidCalc(Target_Speed, Encoder_left + Encoder_right);
      Vertical_out = VerticalPidCalc(Velocity_out + Med_Angle, Roll, gyro_Y);
      Turn_out = TurnPidCalc(gyro_Z);
      PWM_out = Vertical_out;
      /* 电机控制 */
      Moto1 = PWM_out + Turn_out;
      Moto2 = PWM_out - Turn_out;
      Limit_Motor(&Moto1, &Moto2);
      //Turn_off();
      Load_Motor(Moto1, Moto2); // 电机控制
    }
  }
}

/* 直立环
 * Kp×Ek+Kd×Ek_D
 *     Ek=真实角度-期望角度（Angle-Med，由陀螺仪MPU6050测得）
 *     Ek_D=真实角速度（gyro_Y，由陀螺仪MPU6050测得）
 * 参数： Med：期望位置，机械中值
 *       Angle：当前位置，真实角度
 *       Gyro_Y：陀螺仪Y轴角速度
 */
int VerticalPidCalc(float Med, float Angle, float Gyro_Y)
{
  int PWM_out;
  PWM_out = Vertical_Kp * (Angle - Med) + Vertical_Kd * (Gyro_Y - 0);
  return PWM_out;
}
/* 速度环
 * Kp×Ek+Kd×Ek_S
 *      Ek=真实速度-期望速度（真实速度：左电机速度+右电机速度；期望速度：0）
 *      Ek_S=速度偏差的累加
 *  参数：
 */
int VelocityPidCalc(const int Target, const int realSpeed)
{
  static int PWM_out;
  static int Encoder_error;
  static int Encoder_error_last;
  static int Encoder_error_sum;
  static int Encoder_err_tmp;
  Encoder_err_tmp = (realSpeed - Target);

  // 低通滤波
  Encoder_error = LowPass_exper * Encoder_error_last + (1 - LowPass_exper) * Encoder_err_tmp; // 使得波形更加平滑，滤除高频干扰，放置速度突变
  Encoder_error_last = Encoder_error;                                                         // 防止速度过大影响直立环的正常工作

  Encoder_error_sum += Encoder_error;                                                                                                        // 误差累加
  Encoder_error_sum = Encoder_error_sum > Limit_Uppper ? Limit_Uppper : (Encoder_error_sum < Limit_Lower ? Limit_Lower : Encoder_error_sum); // 积分限幅

  PWM_out = Velocity_Kp * Encoder_error + Velocity_Ki * Encoder_error_sum;

  return PWM_out;
}
/* 转向环 */
int TurnPidCalc(int Gyro_z)
{
  return ((-0.6) * Gyro_z);
}
