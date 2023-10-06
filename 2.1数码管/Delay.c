#include <REGX52.H>

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
