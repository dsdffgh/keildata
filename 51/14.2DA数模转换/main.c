#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

#define uchar unsigned char
#define uint unsigned int

sbit DA = P2 ^ 1;

uchar Count = 0, Criterion = 0;
uchar i;

void Timer0_Rountine() interrupt 1
{
    TL0 = TIMS;
    TH0 = TIMS >> 8;
    Count++;
    Count %= 100;

    if (Count < Criterion)
    {
        DA = 1;
    }
    else
        DA = 0;
}

void main()
{
	//uchar i;
    Timer0_Init();
    while (1)
    {
			for(i = 0; i < 100; i++)
			{
				Criterion = i;
				Delay(10);
			} 
			for(i = 100;i > 0;i--)
			{
				Criterion = i;
				Delay(10);
			}
    }
}