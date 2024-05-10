#include <REGX52.H>
#include "MatrixLED.h"
#define MATEIX_LED_PORT P0
void main()
{

    Matrix_LEDInit();//初始化

    //    MATEIX_LED_PORT = 0;//将现象转移到点阵屏
    //    _74HC595_WriteByte_(0xaa);

    while (1)
    {
        MatrixLED_ShowColumn(0, 0x80);
        MatrixLED_ShowColumn(1, 0x40);
        MatrixLED_ShowColumn(2, 0x20);
        MatrixLED_ShowColumn(3, 0x10);
    }
}
