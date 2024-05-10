#include <REGX52.H>

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	//_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us(unsigned int x)	//@11.0592MHz
{
	unsigned char data i;
do{
	i = 2;
	while (--i);
}while(--x);
}


void Delay10ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

//void Delay(unsigned int x) //@11.0592MHz
//{
//	unsigned char i, j;

//	i = 2;
//	j = 199;
//	do
//	{
//		do
//		{
//			while (--j)
//				;
//		} while (--i);
//	} while (--x);
//}
