#include <REGX52.H>
#include "Delay.h"

// 将P3_5重新命名，比较方便
sbit RCK = P3 ^ 5; // RCLK上升沿锁存
sbit SCK = P3 ^ 6; // SERCLK上升沿移位
sbit SER = P3 ^ 4; // SER
#define MATEIX_LED_PORT P0

/*
 *  @brief   点阵屏初始化
 *  @param   无
 *  @retva   无
 */
void Matrix_LEDInit()
{
    SCK = 0;
    RCK = 0; // 初始化
}

/*
 *  @brief   74HC595写入一个字节的数据
 *  @param   Byte 要写入的字节
 *  @retva   无
 */
void _74HC595_WriteByte_(unsigned char Byte)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SER = Byte & (0x80 >> i); //&取出最高位 . SER会被赋值为1000 0000或者0000 0000,代表高电平或低电平,非零即一
        SCK = 1;
        SCK = 0; // 时钟信号上升沿
        /*
        SER = Byte & 0x40;
        SCK = 1;SCK = 0;
        SER = Byte & 0x20;
        SCK = 1;SCK = 0
        将byte的每一位移进去，因为595是串行输入并行输出
        */
    }
    RCK = 1; // 上升沿将数据移到 I/O 口
    RCK = 0;
}

/*
 *  @brief   LED点阵屏显示一列数据
 *  @param   Column 要选择的列 范围0-7，0在最左边
 *  @param		Data 选择列显示的数据，高位在上，1为亮
 *  @retva
 */
void MatrixLED_ShowColumn(unsigned char Column, unsigned char Data)
{
    _74HC595_WriteByte_(Data);
    MATEIX_LED_PORT = ~(0x80 >> Column);
    Delay(1);               // 消影
    MATEIX_LED_PORT = 0xff; // 位清零
}
