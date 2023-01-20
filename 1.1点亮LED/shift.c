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
	unsigned char LEDnum = 0;
	P2 =~0x01;
	
	while(1)
	{
		if(P3_1 == 0)//左移
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			if(LEDnum >= 8)
			{
				LEDnum = 0;
			}
			P2 = ~( 0x01 << ++LEDnum);
		}
		if(P3_0 == 0)//右移,一次性置零，但是之后左移恢复原状态，所以实现不太理想
		{
			Delay(10);
			while(P3_0 == 0)
				;
			Delay(10);
			
			if(LEDnum <= 0)
			{
				LEDnum = 8;
			}
			P2 =~ ( 0x01 >> --LEDnum);
		}
	}
}
#endif

#if 0
//这个也是流水灯
void main()
{
	unsigned char LEDnum = 0;
	while(1)
	{
		
			if(LEDnum >= 8)
			{
				LEDnum = 0;
			}
			P2 =~ ( 0x01 << LEDnum++);
			Delay(10);
		
	}
}
#endif

#if 0
//发现了一个有意思的东西，还不知道咋命名
void main()
{
	unsigned char LEDnum = 1;
	P2 =~0x01;
	
	while(1)
	{
		if(P3_1 == 0)//左移
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			if(P2 == ~0xAA)
			{
				P2 = ~0x01;
			}
			Delay(10);
			P2 = ~( P2 << LEDnum);
		}
		if(P3_0 == 0)//右移，完全清零
		{
			Delay(10);
			while(P3_0 == 0)
				;
			Delay(10);
			
			P2 =~ ( 0x01 >> LEDnum);
		}
	}
}
#endif

#if 1
void main()
{
	unsigned char LEDplus = 0;
	unsigned char LEDsub = 0;
	P2 =~0x01;
	
	while(1)
	{
		if(P3_1 == 0)//左移
		{
			Delay(10);
			while(P3_1 == 0)
				;
			Delay(10);
			
			if(LEDplus >= 8)
			{
				LEDplus = 0;
			}
			P2 = ~( 0x01 << ++LEDplus);
		}
		if(P3_0 == 0)//右移
		{
			Delay(10);
			while(P3_0 == 0)
				;
			Delay(10);
			
			if(LEDplus == 0)
			{
				LEDplus = 7;
			}
			else
				LEDplus--;
			P2 = ~( 0x01 << LEDplus);//不是真的往右移，而是相对于前面的少往右移动一位，就相当于左移。
		}
	}
}
#endif