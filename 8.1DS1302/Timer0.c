#include <REGX52.H>
/*
  *  @brief   定时器0初始化
  *  @param   无
  *  @retva   无
  */
void Timer0Init()		//1毫秒@12.000MHz
{
//	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

/* 中断函数模板
void Timer0_Rountine()	interrupt 1	//中断子程序
{
	static unsigned int T0Count;
	TMOD &= 0xF0;			
	TMOD |= 0x01;	
	T0Count++;
	if(T0Count >= 12)
	{
		T0Count = 0;
	}
} */