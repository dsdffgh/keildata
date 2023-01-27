#include <REGX52.H>
#include <stdio.h>

sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_IO = P3 ^ 4;
sbit DS1302_CE = P3 ^ 5;

#define DS1302_SECOND   0X80
#define DS1302_MINTUE   0X82
#define DS1302_HOUR     0X84
#define DS1302_DATE     0X86
#define DS1302_MONTH    0X88
#define DS1302_WEEK     0X8A
#define DS1302_YEAR     0X8C
#define DS1302_WP       0X8E

char DS1302_Time[] = {23, 1, 28, 23, 00, 59, 1};

/*
 *  @brief   DS1302初始化，使时钟和使能保持低电平
 *  @param   无
 *  @retva   无
 */
void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

/*
 *  @brief   读取地址和写入时间数据
 *  @param   Command 命令字，时间数据的地址，   Data 要写入的时间数据
 *  @retva   无
 */
void DS1302_WriteByte(unsigned char Command, unsigned char Data)
{
    unsigned char i;
    DS1302_CE = 1; // 首先使能

    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i); // 取出最低位
        DS1302_SCLK = 1;                   // 上升沿
        DS1302_SCLK = 0;
    }
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Data & (0x01 << i); // 取出最低位
        DS1302_SCLK = 1;                // 上升沿
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}

/*
 *  @brief   读取地址和返回时间数据
 *  @param   Command 命令字，时间数据的地址
 *  @retva   Data 时间数据
 */
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i, Data = 0x00;
    DS1302_CE = 1;   // 首先使能
    Command |= 0x01; // 把写的地址转换为读的地址，读取的最低位必为1
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i); // 取出最低位
        DS1302_SCLK = 0;                   // 下降沿
        DS1302_SCLK = 1;                   // 先给下降沿是保证结束时为 1
    }

    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 1; // 重复置一可以去掉一个脉冲
        DS1302_SCLK = 0; // 保证结束时为零
        if (DS1302_IO)
        {
            Data |= (0x01 << i);
        }
    }

    DS1302_CE = 0;
    DS1302_IO = 0;
    return Data;
}

/*
 *  @brief   将十进制码转换为BCD码
 *  @param   time 一个unsigned char类型的整数，值为数组内的数据
 *  @retva   BCD码，以便DS1302读取
 */
unsigned char to_BCD(unsigned char time)
{
    return (time / 10 * 16 + time % 10);
}

unsigned char to_BCD__(unsigned char *time)
{
    return *time / 10 * 16 + *time % 10;
}

/*
 *  @brief   将BCD码转换为十进制码
 *  @param   time 一个unsigned char类型的整数，值为数组内的数据
 *  @retva   十进制码，以便读取DS1302
 */
unsigned char from_BCD(unsigned char time)
{
    return (time / 16 * 10 + time % 16);
}

/*
 *  @brief   设置时间，将数组里贮存的时间数据写入寄存器
 *  @param   无
 *  @retva   无
 */
void DS1302_SetTime()
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 解除写保护
    DS1302_WriteByte(DS1302_YEAR,   to_BCD__(DS1302_Time));
    DS1302_WriteByte(DS1302_MONTH,  to_BCD__(DS1302_Time + 1));
    DS1302_WriteByte(DS1302_DATE,   to_BCD__(DS1302_Time + 2));
    DS1302_WriteByte(DS1302_HOUR,   to_BCD__(DS1302_Time + 3));
    DS1302_WriteByte(DS1302_MINTUE, to_BCD__(DS1302_Time + 4));
    DS1302_WriteByte(DS1302_SECOND, to_BCD__(DS1302_Time + 5));
    DS1302_WriteByte(DS1302_WEEK,   to_BCD__(DS1302_Time + 6));
    DS1302_WriteByte(DS1302_WP, 0x80); // 打开写保护
}

/*
 *  @brief   读取时间，将数据写入数组，之后主模块直接调用数组即可
 *  @param   无
 *  @retva   无
 */
void DS1302_ReadTime()
{
    DS1302_Time[0] = from_BCD(DS1302_ReadByte(DS1302_YEAR));
    DS1302_Time[1] = from_BCD(DS1302_ReadByte(DS1302_MONTH));
    DS1302_Time[2] = from_BCD(DS1302_ReadByte(DS1302_DATE));
    DS1302_Time[3] = from_BCD(DS1302_ReadByte(DS1302_HOUR));
    DS1302_Time[4] = from_BCD(DS1302_ReadByte(DS1302_MINTUE));
    DS1302_Time[5] = from_BCD(DS1302_ReadByte(DS1302_SECOND));
    DS1302_Time[6] = from_BCD(DS1302_ReadByte(DS1302_WEEK));
}
