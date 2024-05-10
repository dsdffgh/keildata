#include <REGX52.H>

#define uchar unsigned char
#define CYCLE 100

sbit LED = P2 ^ 0;

void Delay(unsigned int i)
{
	while(i--);
}


void main()
{
	uchar Time = 0,i;
	while (1)
	{
		for (Time = 0; Time < CYCLE; Time++)
		{
			for (i = 0; i < 20; i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(CYCLE - Time);
			}
		}
		for (Time = CYCLE; Time > 0; Time--)
		{
			for (i = 0; i < 20; i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(CYCLE - Time);
			}
		}
	}
}