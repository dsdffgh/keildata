#include <REGX52.H>
#define FOSC 1104000l                  // Frequency of Oscillator
#define TIMS (65536 - FOSC / 12 / 1000) // Timer Initial Value for 100us

void Timer0_Init()
{
    // set timer0 as mode 1 (16-bit)
    TMOD &= 0xF0;
    TMOD |= 0x01;
    // initial timer0
    TL0 = TIMS;
    TH0 = TIMS >> 8;
    // clear TF0 flag
    TF0 = 0;
    //timer0 star running
    TR0 = 1;
    // enable timer0 interrupt
    ET0 = 1;
    // OPEN global interrupt switch
    EA = 1;

    PT0 = 0;
}

/* 中断函数模板
void Timer0_Rountine()	interrupt 1	//中断子程序
{
	static unsigned int T0Count;
	TL0 = TIMS;				//设置定时初始值
	TH0 = TIMS >> 8;	//设置定时初始值
	T0Count++;
	if(T0Count >= 1000)
	{
		T0Count = 0
		// your operate
	}
} */
