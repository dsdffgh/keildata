#include <REGX52.H>
#include "Delay.h"

sbit Buzzer = P2 ^ 5;
unsigned int i;

void Buzzer_delay500us() // 误差 -0.868055555556us
{
    unsigned char a, b;
    for (b = 1; b > 0; b--)
        for (a = 227; a > 0; a--)
            ;
}

void Buzzer_Time(unsigned int ms)
{

    for (i = 0; i < ms * 2; i++)
    {
        Buzzer = !Buzzer;
        // Delay(1);//500HZ响500ms
        Buzzer_delay500us(); // 1000HZ
    }
}