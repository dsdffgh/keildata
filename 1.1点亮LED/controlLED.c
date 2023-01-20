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

 void main()
 {
		while(1)
		{
			if(P3_1 == 0)
			{
				Delay(10);//消除按键抖动
				while(P3_1 == 0)//检测松手
					;
				Delay(10);//松手抖动
				
				P2_0 = ~P2_0;
			}
		}
 }
