#include <REGX52.H>
#include "Delay.h"
#include "key.h"
#include "NixieTube.h"
#include "Buzzer.h"

unsigned char KeyNum;




void main()
{
    while (1)
    {
        KeyNum = key();
        if (KeyNum)
        {
            Buzzer_Time(500);
            NixieTube(1, KeyNum);
        }
    }
}