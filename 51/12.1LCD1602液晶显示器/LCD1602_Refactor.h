#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Delay();
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_INIT();
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char);

#endif