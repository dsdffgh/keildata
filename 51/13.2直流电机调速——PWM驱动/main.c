#include <REGX52.H>
//#include "Delay.h"
#include "key.h"
#include "NixieTube.h"
#include "Timer0.h"

#define uchar unsigned char
#define uint unsigned int
//#define Criterion 50

//sbit LED = P2 ^ 0;
sbit Motor = P1 ^ 0;

uchar Count = 0, Criterion = 0;

void Timer0_Rountine() interrupt 1
{
    TL0 = TIMS;
    TH0 = TIMS >> 8;
    Count++;
    Count %= 100;

    if (Count < Criterion)
    {
        Motor = 1;
    }
    else
        Motor = 0;
}

void main()
{
uchar KeyNum = 0;
uchar Speed = 0;
    Timer0_Init();
    while (1)
    {
        KeyNum = key();
        if (KeyNum == 1)
        {
            Speed++;
            Speed %= 4; // 4个档
            if (Speed == 0)
                Criterion = 0;
            else if (Speed == 1)
                Criterion = 5;
            else if (Speed == 2)
                Criterion = 50;
            else if (Speed == 3)
                Criterion = 100;
        }
        NixieTube(1, Speed);
    }
}