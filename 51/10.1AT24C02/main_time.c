#include <REGX52.H>
#include "Delay.h"
#include "key.h"
#include "Timer0.h"
#include "NixieTube.h"

unsigned char temp,keynum;
void Timer0_Rountine()	interrupt 1	//中断子程序
{
	static unsigned int T0Count1,T0Count2;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count1++;
	if(T0Count1 >= 20)
	{
		T0Count1 = 0;
		Key_Loop();
	}
	T0Count2++;
	if(T0Count2 >= 2)
	{
		T0Count2 = 0;
		Nixie_Loop();
	}
} 

void main()
{
	Timer0Init();
	while(1)
	{
		keynum = key();
		if(keynum){
			Nixie_SetBuffer[1,keynum];
			Nixie_SetBuffer[2,keynum];
			Nixie_SetBuffer[3,keynum];
		}
		/* 
		if(keynum){
			temp = key();
		}
		Nixie_Scan(1,temp); */
	}
}