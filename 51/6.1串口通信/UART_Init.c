#include <REGX52.H>
/*
  *  @brief   串口初始化	4800bps@11.0592MHz
  *  @param   无
  *  @retva   无
  */
void UartInit(void) 
{
	PCON |= 0x80; // 使能波特率倍速位SMOD
	SCON = 0x50;  // 8位数据,可变波特率
	//*************
//	AUXR &= 0xBF;		//定时器时钟12T模式
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//  89c52没有这种选择
	TMOD &= 0x0F; 	// 设置定时器模式
	TMOD |= 0x20; 	// 设置定时器模式
	TL1 = 0xF4;	  	// 设置定时初始值
	TH1 = 0xF4;	  	// 设置定时重载值
	ET1 = 0;	  	// 禁止定时器中断
	TR1 = 1;	  	// 定时器1开始计时

	ES = 1;		  	//启用串口中断
	EA = 1;
}

/*
  *  @brief   串口发送一个字节数据
  *  @param   byte 要发送的一个字节数据
  *  @retva   无
  */
void UART_SendByte(unsigned char byte)
{
	SBUF = byte;
	// 检测发送完成
	while (TI == 0) // TI:发送中断请求标志位，8位数据发送结束时，自动置为1，发送中断，之后要复位
		;
	TI = 0; // 复位
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
//	P2 = 0X00;//测试能否传入中断
	if(RI == 1)
	{
		
		RI = 0;
	}
}
*/