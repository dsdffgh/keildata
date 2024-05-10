#ifndef  _MOTOR_H
#define  _MOTOR_H


#define Ain1  PBout(14)
#define Ain2  PBout(15)

#define Bin1  PBout(13)
#define Bin2  PBout(12)

#define MOTOR1_DIR_GPIO GPIOA
#define MOTOR1_DIR_GPIO_CLK RCC_APB2Periph_GPIOA
#define MOTOR1_DIR_FORWARD_PIN GPIO_Pin_4
#define MOTOR1_DIR_BACKWARD_PIN GPIO_Pin_5
#define MOTOR2_DIR_GPIO GPIOA
#define MOTOR2_DIR_GPIO_CLK RCC_APB2Periph_GPIOA
#define MOTOR2_DIR_FORWARD_PIN GPIO_Pin_4
#define MOTOR2_DIR_BACKWARD_PIN GPIO_Pin_5

void Motor_Init(void);
void Limit_Motor(int *motoA,int *motoB);
int abs(int p);
void Load_Motor(int moto1,int moto2);

#endif
