#include <REGX52.H>
#include "UART_Init.h"
#include "Delay.h"

void main()
{
	UartInit();
	while(1)
	{
		
	}
}

//电脑发送数据的时候触发一个中断
void UART_Routine() interrupt 4
{
//	P2 = 0X00;//测试能否传入中断
	if(RI == 1)
	{
		P2 = ~SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}
