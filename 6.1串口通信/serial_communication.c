#include <REGX52.H>
#include <Delay.h>
#include <UART_Init.h>

unsigned char Second = 0;

void main()
{
	UartInit();
	//	UART_SendByte(0x11);
	while (1)
	{
		UART_SendByte(Second); // 若发送有误差可以延时试一下
		Second++;
		Delay(13);
	}
}