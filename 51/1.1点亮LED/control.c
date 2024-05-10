#include <REGX52.H>
#if 0
//按着就亮
void main()
{
	while(1)
	{
		if(P3_1 == 0)
		{
			P2_0 = 0;//the lowest bit 
		}
		else{
			P2_0 = 1;
		}
	}
}
#endif

#if 1
void main()  //只会执行一次
{  
	if(P3_1 == 0)
		{
			P2_0 = 0;//the lowest bit 
		}
		else{
			P2_0 = 1;
		}
	while(1)
	{
	
	}
}
#endif
