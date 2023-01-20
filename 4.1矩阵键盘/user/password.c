#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MATRIXKEY.H"

unsigned char KeyNum;
unsigned int password = 0,count = 0;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)																//如果去掉判断，会显示0，因为1被刷掉了
		{
			if(KeyNum <= 10)
				{																			//S1-10为密码按键
				if(count < 4)													//密码只有四位
					{											
						password *= 10;										//左移
						password += KeyNum % 10;					//使得S10为0，获取一位密码
						count++;													//记录位数，多的不算
					}
					LCD_ShowNum(2,1,password,4);
				}
			else if(KeyNum == 11)//确认
				{									
					if(password == 4297){
						LCD_ShowString(1,12,"   OK");
						password = 0;count = 0;							//清零
						LCD_ShowNum(2,1,password,4);
					}
					else{
						LCD_ShowString(1,12,"ERROR");
						password = 0;count = 0;
						LCD_ShowNum(2,1,password,4);
					}
				}
			else if(KeyNum == 12)											//取消
				{					
					password = 0;count = 0;
					LCD_ShowNum(2,1,password,4);
				}
			else if(KeyNum == 13)											//删除
				{					
					password /= 10;count--;
					LCD_ShowNum(2,1,password,4);
				}
		}
	}
}
