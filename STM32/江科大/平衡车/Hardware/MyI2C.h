#ifndef __MYI2C_H
#define __MYI2C_H

/*引脚配置层*/
#define I2C_GPIO GPIOB
#define I2C_SCL_PIN GPIO_Pin_10
#define I2C_SDA_PIN GPIO_Pin_11
#define RCC_APB2Periph_I2C_GPIO RCC_APB2Periph_GPIOB
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif
 