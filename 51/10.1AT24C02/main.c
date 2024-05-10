#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "key.h"
#include "I2C.H"
#include "AT24C02.H"
#define uchar unsigned char

uchar Data,KeyNum;
unsigned int Num;
void main()
{
	LCD_Init();
//	LCD_ShowString(1,1,"hello!");
//	AT24C02_WriteByte(0,144);
//	Delay(5);//写周期是5ms
//	AT24C02_WriteByte(1,215);
//	Delay(5);//写周期是5ms
//	AT24C02_WriteByte(3,300);
//	Delay(5);//写周期是5ms
//	Data = AT24C02_ReadByte(1);
//	LCD_ShowNum(2,1,Data,3);
	LCD_ShowNum(1, 1, Num, 5);
	while (1)
	{
		KeyNum = Key();
		if (KeyNum == 1)
		{
			Num++;
			LCD_ShowNum(1, 1, Num, 5);
		}
		if (KeyNum == 2)
		{
			Num--;
			LCD_ShowNum(1, 1, Num, 5);
		}
		if (KeyNum == 3)
		{
			AT24C02_WriteByte(0, Num % 256);
			Delay(5);
			AT24C02_WriteByte(1, Num / 256);
			Delay(5);
			LCD_ShowString(2, 1, "Write OK");
			Delay(3);
			LCD_ShowString(2, 1, "        ");
		}
		if (KeyNum == 4)
		{
			Num = AT24C02_ReadByte(0);
			Num |= AT24C02_ReadByte(1) << 8;
			LCD_ShowNum(1, 1, Num, 5);
			LCD_ShowString(2, 1, "Read OK");
			Delay(3);
			LCD_ShowString(2, 1, "       ");
		}
	}
}