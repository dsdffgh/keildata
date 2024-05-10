#include <REGX52.H>

// 引脚配置：
sbit LCD_RS = P2 ^ 6;
sbit LCD_RW = P2 ^ 5;
sbit LCD_EN = P2 ^ 7;
#define LCD_DataPort P0

// 函数定义：
/**
 * @brief  LCD1602延时函数，12MHz调用可延时1ms
 * @param  无
 * @retval 无
 */
void LCD_Delay()
{
    unsigned char i, j;

    i = 2;
    j = 239;
    do
    {
        while (--j)
            ;
    } while (--i);
}

/**
 * @brief  LCD1602写命令
 * @param  Command 要写入的命令
 * @retval 无
 */
void LCD_WriteCommand(unsigned char Command)
{
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_DataPort = Command;
    LCD_EN = 1;
    LCD_Delay(); // stay and over
    LCD_EN = 0;
    LCD_Delay();
}

/**
 * @brief  LCD1602写数据
 * @param  Data 要写入的数据
 * @retval 无
 */
void LCD_WriteData(unsigned char Data)
{
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_DataPort = Data;
    LCD_EN = 1;
    LCD_Delay();
    LCD_EN = 0;
    LCD_Delay();
}

/**
 * @brief  LCD1602初始化函数
 * @param  无
 * @retval 无
 */
void LCD_INIT()
{
    LCD_WriteCommand(0x38); // 八位数据接口，两行显示，5*7点阵
    LCD_WriteCommand(0x0c); // 显示开，光标关，闪烁关
    LCD_WriteCommand(0x06); // 数据读写操作后，光标自动加一，画面不动
    LCD_WriteCommand(0x01); // 光标复位，清屏
}

/**
 * @brief  在LCD1602指定位置上显示一个字符
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符
 * @retval 无
 */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
    if (Line == 1)
    {
        LCD_WriteCommand(0x80 | (Column - 1));
    }
    else if (Line == 2)
    {
        LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
    }
    LCD_WriteData(Char);
}