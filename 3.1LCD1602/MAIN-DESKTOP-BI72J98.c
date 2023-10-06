#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD_Init();//LCD1602  初始化函数
    LCD_ShowChar(1,1,'1');
	LCD_ShowChar(1,2,'9');
	LCD_ShowChar(1,3,'8');
	LCD_ShowChar(1,4,'9');

    LCD_ShowString(2,1,"Hello world");
    while(1)
    {
        
    }
}