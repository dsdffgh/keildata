#include <REGX52.H>

void Delay(unsigned int x)		//@12.000MHz
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