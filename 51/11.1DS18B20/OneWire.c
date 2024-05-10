#include <REGX52.H>
#include <intrins.h>
#include <Delay.h>

sbit OneWire_DQ = P3 ^ 7;

unsigned char i;

unsigned char OneWire_Init()
{

    unsigned char AckBit;
    OneWire_DQ = 1;
    OneWire_DQ = 0;

    i = 230; //  delay 500us
    while (--i)
        ;

    OneWire_DQ = 1; // 释放
    _nop_();        // 65us
    i = 29;
    while (--i)
        ;

    AckBit = OneWire_DQ;
    i = 230; //  delay 500us
    while (--i)
        ;
    return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
    OneWire_DQ = 0;
    i = 4; // 10us
    while (--i)
        ;
    OneWire_DQ = Bit;
    _nop_(); // 50us
    i = 22;
    while (--i)
        ;

    OneWire_DQ = 0; // 释放
}

unsigned char OneWire_ReceiveBit()
{
    unsigned char Bit;
    OneWire_DQ = 0;
    i = 2; // 5us
    while (--i)
        ;
    OneWire_DQ = 1;
    i = 2; // 5us
    while (--i)
        ;
    Bit = OneWire_DQ;
    _nop_();
    i = 22; // 50us
    while (--i)
        ;
    return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
    for (i = 0; i < 8; i++)
    {
        OneWire_SendBit(Byte & (0x01 << i));
    }
}

unsigned char OneWire_ReceiveByte()
{
    unsigned char Byte = 0x00;
    for (i = 0; i < 8; i++)
    {
        if (OneWire_ReceiveBit())
        {
            Byte |= (0x01 << i);
        }
    }
    return Byte;
}
