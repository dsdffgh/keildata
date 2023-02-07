#include <REGX52.H>
#include "Timer0.h"
#include "lcd1602.h"
#include <Delay.h>

unsigned char Second = 55,Mintue = 59,Hour = 23;

void Timer0_Rountine() interrupt 1//中断函数不宜执行过长任务
{
	static unsigned int T0Count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count >= 1000)
	{
		T0Count = 0;
		Second++;
		if(Second >= 60)
		{
			Second = 0;
			Mintue++;
			if(Mintue >= 60)
			{
				Mintue = 0;
				Hour++;
				if(Hour >= 24)	Hour = 0;
			}
		}
	}
}

void main()
{
	LCD_Init();
	Timer0Init();

	LCD_ShowString(1,1,"hello_clock:");
	LCD_ShowString(2,3,":  :");

	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Mintue,2);
		LCD_ShowNum(2,7,Second,2);
	}
}