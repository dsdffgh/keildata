#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include <stdio.h>

unsigned char Second;

void main()
{
	LCD_Init();
	DS1302_Init();

	/*
	第一版的

	DS1302_WriteByte(0x80, 0x03);

	while (1)
	{
		Second = DS1302_ReadByte(0x81);

		//LCD_ShowNum(1, 1, Second, 3);//因为DS1302是用BCD码来表示时钟，所以9会突变为16
		//LCD_ShowHexNum(2, 1, Second, 3);//可以看到这样就对了

		LCD_ShowNum(1, 1, Second / 16 * 10 + Second % 16, 3);
		Delay(5);
	}
	*/

	DS1302_SetTime();
	while (1)
	{
		DS1302_ReadTime();
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
	}
}