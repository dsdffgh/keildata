#include <REGX52.H>

sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;

/*
 *  @brief   I2C开始
 *  @param
 *  @retva
 */
void I2C_Start()
{
    I2C_SDA = 1;
    I2C_SCL = 1;

    I2C_SDA = 0;
    I2C_SCL = 0;
}

/*
 *  @brief   I2C停止
 *  @param
 *  @retva
 */
void I2C_Stop()
{
    I2C_SDA = 0;
    I2C_SCL = 1;

    I2C_SDA = 1;
}

/*
 *  @brief   I2C发送一个字节
 *  @param   Byte 要发送的字节
 *  @retva
 */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0; i < 8 ;i++)
    {
        I2C_SDA = Byte & (0x80 >> i);
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}

/*
 *  @brief   I2C接受一个字节
 *  @param   无
 *  @retva   Byte 接收到的字节数据
 */
unsigned char I2C_ReceiveByte()
{
    unsigned char i;
    unsigned char Byte = 0x00;
    I2C_SDA = 1;
    for (i = 0; i < 8 ;i++)
    {
        I2C_SCL = 1;
        if (I2C_SDA)
        {
            Byte |= (0x80 >> i);
        }
        I2C_SCL = 0;
    }
    return Byte;
}

/*
 *  @brief   I2C发送应答
 *  @param   ACKBit 应答位，0为应答，1为非应答
 *  @retva
 */
void I2C_SendACK(bit ACKBit)
{
    I2C_SDA = ACKBit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}

/*
 *  @brief   I2C接受应答位
 *  @param   无
 *  @retva   ACKBit 接收到的应答位
 */
unsigned char I2C_ReceviceACK()
{
    bit ACKBit;
    I2C_SDA = 1;
    I2C_SCL = 1;
    ACKBit = I2C_SDA;
    I2C_SCL = 0;

    return ACKBit;
}