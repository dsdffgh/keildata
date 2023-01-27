#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "MatrixKey.h"
#include "Timer0.h"

unsigned char KeyNum, ClockMode;
unsigned char TimeSelect; // 时钟设置位选择
unsigned char TimeCal_FlashFlag;
unsigned char i = 0;

void Time_Cross_Judgment()
{
    *DS1302_Time %= 99;
    if (DS1302_Time[1] >= 13)
    {
        DS1302_Time[1] = 1;
    }
    else if (DS1302_Time[1] < 1)
    {
        DS1302_Time[1] = 12;
    }
    if (DS1302_Time[1] == 2) // 闰月
    {
        if (*DS1302_Time % 4 == 0) // 年份范围是2000-2099，不必判断整百年
        {
            if (DS1302_Time[2] > 29)
            {
                DS1302_Time[2] = 1;
            }
            if (DS1302_Time[2] < 1)
            {
                DS1302_Time[2] = 29;
            }
        }
        else
        {
            if (DS1302_Time[2] > 28)
            {
                DS1302_Time[2] = 1;
            }
            if (DS1302_Time[2] < 1)
            {
                DS1302_Time[2] = 28;
            }
        }
    }
    else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 9 || DS1302_Time[1] == 6 || DS1302_Time[1] == 11)
    {
        if (DS1302_Time[2] > 30)
        {
            DS1302_Time[2] = 1;
        }
        if (DS1302_Time[2] < 1)
        {
            DS1302_Time[2] = 30;
        }
    }
    else
    {

        if (DS1302_Time[2] > 31)
        {
            DS1302_Time[2] = 1;
        }
        if (DS1302_Time[2] < 1)
        {
            DS1302_Time[2] = 31;
        }
    }
    DS1302_Time[3] %= 24;
    if (DS1302_Time[3] < 0)
    {
        DS1302_Time[3] = 23;
    }
    DS1302_Time[4] %= 60;
    if (DS1302_Time[4] < 0)
    {
        DS1302_Time[4] = 59;
    }
    DS1302_Time[5] %= 60;
    if (DS1302_Time[5] < 0)
    {
        DS1302_Time[5] = 59;
    }

    if (DS1302_Time[1] > 7)
    {
        DS1302_Time[1] = 1;
    }
}

void TimeShow()
{
    LCD_ShowNum(1, 1, DS1302_Time[0], 2);
    LCD_ShowNum(1, 4, DS1302_Time[1], 2);
    LCD_ShowNum(1, 7, DS1302_Time[2], 2);
    LCD_ShowNum(2, 1, DS1302_Time[3], 2);
    LCD_ShowNum(2, 4, DS1302_Time[4], 2);
    LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

void TimeCalibrating()
{
    if (KeyNum == 2)
    {
        TimeSelect++;
        TimeSelect %= 6; // 超过 5 自动清零
        //LCD_ShowNum(2, 10, TimeSelect, 2);
    }
    if (KeyNum == 3)
    {
        DS1302_Time[TimeSelect]++;
    }
    else if (KeyNum == 4)
    {
        DS1302_Time[TimeSelect]--;
    }
    Time_Cross_Judgment();

	if (TimeSelect == 0 && TimeCal_FlashFlag == 1){LCD_ShowString(1, 1, "  ");}else{LCD_ShowNum(1, 1, DS1302_Time[0], 2);}
	if (TimeSelect == 1 && TimeCal_FlashFlag == 1){LCD_ShowString(1, 4, "  ");}else{LCD_ShowNum(1, 4, DS1302_Time[1], 2);}
	if (TimeSelect == 2 && TimeCal_FlashFlag == 1){LCD_ShowString(1, 7, "  ");}else{LCD_ShowNum(1, 7, DS1302_Time[2], 2);}
	if (TimeSelect == 3 && TimeCal_FlashFlag == 1){LCD_ShowString(2, 1, "  ");}else{LCD_ShowNum(2, 1, DS1302_Time[3], 2);}
	if (TimeSelect == 4 && TimeCal_FlashFlag == 1){LCD_ShowString(2, 4, "  ");}else{LCD_ShowNum(2, 4, DS1302_Time[4], 2);}
	if (TimeSelect == 5 && TimeCal_FlashFlag == 1){LCD_ShowString(2, 7, "  ");}else{LCD_ShowNum(2, 7, DS1302_Time[5], 2);}

    //LCD_ShowNum(2, 13, TimeCal_FlashFlag, 2);
    DS1302_SetTime();
}


void Timer0_Rountine() interrupt 1 // 中断子程序
{
    static unsigned int T0Count;
    TMOD &= 0xF0;
    TMOD |= 0x01;
    T0Count++;
    if (T0Count >= 13)
    {
        T0Count = 0;
        TimeCal_FlashFlag = !TimeCal_FlashFlag;
    }
}

void main()
{
    LCD_Init();
    DS1302_Init();
    Timer0Init();

    DS1302_SetTime();
    while (1)
    {
        KeyNum = MatrixKey();
        if (KeyNum == 1)
        {
            ClockMode = ~ClockMode;
        }
        if (ClockMode)
        {
            TimeCalibrating();
        }
        else
        {
            DS1302_ReadTime();
            TimeShow();
        }
    }
}