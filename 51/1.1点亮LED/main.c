#include <REGX52.H>

void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	
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
	#if 0
	//p2 = 1111 1110	Set the lowest bit to zero 
	P2 = 0xFE;
	P2 = 0xFF;
	while(1){}//let it light up once and then turn off
		#endif
		
		
		#if 1
	while(1){
		
		P2 = 0xFE;
		Delay1000ms();
		P2 = 0xFF;
		Delay1000ms();
	}
	#endif
}