#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h" 
#define SPEED 500

sbit Buzzer = P2 ^ 5;

unsigned int  FreqTable[] = {63628, 63731, 63835, 63928, 64021, 64103, 64185, 64260, 64331, 64400, 64463, 64528,
								 64580, 64633, 64684, 64732, 64777, 64820, 64860, 64898, 64934, 64968, 65000, 65030,
								 65058, 65085, 65110, 65134, 65157, 65178, 65198, 65217, 65235, 65252, 65268, 65283,
								 0};

unsigned char SheetMusic[][14] = {{12, 12, 19, 19, 21, 21, 19, 17, 17, 16, 16, 14, 14, 12},
									  {4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8}};

unsigned char FreqSelsect, Sheet_Select, time_Select;

void Timer0_Rountine() interrupt 1 // 中断子程序
{
	TL0 = FreqTable[FreqSelsect] % 256; // 设置定时初始值
	TH0 = FreqTable[FreqSelsect] / 256; // 设置定时初始值
	Buzzer = !Buzzer;
}

void main()
{
	Timer0Init();
	while (1)
	{
		FreqSelsect = SheetMusic[0][Sheet_Select];
		Sheet_Select++;
		Delay(3);
//		Delay(SPEED / 4 * SheetMusic[1][time_Select++]);
		TR0 = 0;//抬手
		Delay(3);
		TR0 = 1; 
	}
}