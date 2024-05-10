#include <REGX52.H>
#include "Delay.h"

// 定义引脚
sbit XPT2046_CS = P3^5;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;
sbit XPT2046_DCLK = P3^6;

#define XPT2046_XP_8 0x9C		//0x8C
#define XPT2046_YP_8 0xDC
#define XPT2046_V_BAT_8 0xAC
#define XPT2046_AUX_IN_8 0xEC 

#define XPT2046_XP_12 0x94
#define XPT2046_YP_12 0xD4
#define XPT2046_V_BAT_12 0xA4
#define XPT2046_AUX_IN_12 0xE4

/**
  * @brief  XPT2046读取AD值
  * @param  Command 命令字，范围：头文件内定义的宏，结尾的数字表示转换的位数
  * @retval AD转换后的数字量，范围：8位为0~255，12位为0~4095
  */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int AD_value = 0;
	XPT2046_CS = 0;
	XPT2046_DCLK = 0;	// initial
	for( i = 0; i < 8; i++)
	{
		XPT2046_DIN = Command & (0x80 >> i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	//Delay(1);
	// coversion
	for( i = 0; i < 16; i++)
	{
		// 此时处于下降沿，先上升
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT)	{	
			AD_value |= (0x8000 >> i); 
		}
	}
	
	XPT2046_CS = 1;		// Finish  
	if(Command&0x08)
		return AD_value >> 8;
	else
		return AD_value >> 4;
}