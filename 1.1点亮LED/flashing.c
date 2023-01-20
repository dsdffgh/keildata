#include <REGX52.H>
#include <INTRINS.H>
void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}




void main()
{
	//p2 = 1111 1110	Set the lowest bit to zero 
	#if 1
	while(1){
		
		P2 = 0xFE;
		Delay1000ms();
		P2 = 0xFF;
		Delay1000ms();
	}
	#endif
		//let it light up once and then turn off
}