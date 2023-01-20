#include <REGX52.H>
#include "Timer0.h"
#include "key.h"
#include <intrins.h>
//#include "lcd1602.h"

/*定时器介绍：51单片机的定时器属于单片机的内部资源，其电路的连接和运转均在单片机内部完成
	定时器作用：
	（1）用于计时系统，可实现软件计时，或者使程序每隔一固定时间完成一项操作
	（2）替代长时间的Delay，提高CPU的运行效率和处理速度
	（…）
	
	定时器在单片机内部就像一个小闹钟一样，根据时钟的输出信号，每隔“一秒”，计数单元的数值就增加一，
	当计数单元数值增加到“设定的闹钟提醒时间”时，计数单元就会向中断系统发出中断申请，产生“响铃提醒”，
	使程序跳转到中断服务函数中执行

*/

//按键控制流水灯模式

unsigned int T0Count = 0;
unsigned char keynum,LEDMode;

//	void Timer0_Init()
//	{
//	//	TMOD = 0x01;
//		TMOD = TMOD & 0XF0;	//高四位不变，低四位清零
//		TMOD = TMOD | 0X01;	//高四位不变，最低位置1
//		TF0 = 0;//配置TCON
//		TR0 = 1;
//		TH0 = 64535/256;
//		TL0 = 64535%256;
//		ET0 = 1;
//		EA = 1;
//		PT0 = 0;
//	}

void Timer0_Rountine()	interrupt 1	//中断子程序
{
	
//	TH0 = 64535/256;//保证每次计数都是1ms
//	TL0 = 64535%256;//但是实际上这样每次会少1us
	
	TMOD &= 0xF0;			
	TMOD |= 0x01;	
	T0Count++;
	if(T0Count >= 12)
	{
		T0Count = 0;
		//P2_0 = ~P2_0;//验证中断是否到达

		if(LEDMode == 0){
			
			P2 = _crol_(P2,1);//左移一位
			//LCD_ShowHexNum(1,1,P2,6);
		}
		if(LEDMode == 1){
			P2 = _cror_(P2,1);
			//LCD_ShowHexNum(1,1,P2,6);
		}
	}
}

void main()
{
	P2 = 0XFE;
	Timer0Init();
	while(1)
	{
		keynum = key();
//		if(keynum == 1)	{P2_1 = ~P2_1;}
//		if(keynum == 2)	{P2_2 = ~P2_2;}
//		if(keynum == 3)	{P2_3 = ~P2_3;}
//		if(keynum == 4)	{P2_4 = ~P2_4;}
//测试是否有误
		
		if(keynum == 1)	{
			LEDMode++;
			if(LEDMode > 1)
				LEDMode = 0;
		}
		
			
	}
}
