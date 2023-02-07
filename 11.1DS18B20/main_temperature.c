#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "DS18B20.h"

//unsigned char Ack;
float T;

void main()
{
//	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
//	Delay(5);
	LCD_Init();
	LCD_ShowString(1, 1, "temperature:");
//	Ack = OneWire_Init();
//	LCD_ShowNum(2, 1, Ack, 3);
	while (1)
	{
		DS18B20_CovertT();
		T = DS18B20_ReadT();
		if (T < 0)
		{
			LCD_ShowChar(2, 1, '-');
			T = -T;
		}
		else
			LCD_ShowChar(2, 1, '+');

		LCD_ShowNum(2, 2, T, 3);
		LCD_ShowChar(2, 5, '.');
		LCD_ShowNum(2, 6, (unsigned long)(T * 10000) % 10000, 4);
	}
}