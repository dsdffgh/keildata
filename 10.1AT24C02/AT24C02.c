#include <REGX52.H>
#include "I2C.H"
#define uchar unsigned char
#define AT24C02_ADDRESS 0xa0
/**
  *  @brief   AT24C02写入一个字节
  *  @param   WordAddress 要写入字节的地址
	*  @param   Data 要写入的数据
  *  @retva   无
  */
void AT24C02_WriteByte(uchar WordAddress, uchar Data)
{
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);
    I2C_ReceviceACK();
    I2C_SendByte(WordAddress);
    I2C_ReceviceACK();
    I2C_SendByte(Data);
    I2C_ReceviceACK();
    I2C_Stop();
}

/**
  *  @brief   AT24C02读取一个字节
  *  @param   WordAddress 要读出字节的地址
  *  @retva   Data 读出的数据
  */
uchar AT24C02_ReadByte(uchar WordAddress)
{
    uchar Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);
    I2C_ReceviceACK();
    I2C_SendByte(WordAddress);
    I2C_ReceviceACK();

    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS | 0x01);
    I2C_ReceviceACK();
    Data = I2C_ReceiveByte();
    I2C_SendACK(1);
    I2C_Stop();
    return Data;
}