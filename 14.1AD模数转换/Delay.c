#include <REGX52.H>

void Delay1ms(unsigned int x)		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		do
		{
			while (--j);
		} while (--i);
	}while(--x);
}

void Delay(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 199;
	do
	{
	do
	{
		while (--j);
	} while (--i);
	}while(--x);
}
