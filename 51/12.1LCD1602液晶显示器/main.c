#include <REGX52.H>
#include "LCD1602_Refactor.h"

void main()
{
	LCD_INIT();
	LCD_ShowChar(1,5,'A');
	while(1)
	{}
}