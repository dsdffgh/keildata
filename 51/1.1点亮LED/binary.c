#include <REGX52.H>

void Delay(int x)		//@12.000MHz
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

#if 0
void main()
{
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			//1111 1111
			P2++;//初始都是高电平为0xff，加1后溢出变0x00,所以灯全亮了
			//0000 0000
			
			Delay(5);//所以闪得很暗，加个延迟就行了
			
			P2 = ~P2;
			//1111 1111
		}
	}
}
#endif

#if 0
void main()
{
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			//1111 1111
			P2--;//初始都是高电平为0xff，加1后溢出变0x00,所以灯全亮了
			
		}
	}
}
#endif

#if 1
void main()
{
	unsigned char LEDnum = 0;
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			//1111 1111
			LEDnum++;//初始都是高电平为0xff，加1后溢出变0x00,所以灯全亮了
			P2 = ~LEDnum;
			//1111 1111
		}
	}
}
#endif
