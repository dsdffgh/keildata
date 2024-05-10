#include <REGX52.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM                    0XCC
#define DS18B20_SEARCH_ROM                  0XF0
#define DS18B20_READ_ROM                    0X33
#define DS18B20_ALARM_ROM                   0XEC
#define DS18B20_CONVERT_T                   0X44
#define DS18B20_WRITE_SCRATCHPAD            0X4E
#define DS18B20_READ_SCRATCHPAD             0XBE
#define DS18B20_WRITE_COPY_SCRATCHPAD       0X48
#define DS18B20_WRITE_RECALL_E2             0XB8
#define DS18B20_WRITE_READ_POWER_SUPPLY     0XB4

void DS18B20_CovertT()
{
    OneWire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_CONVERT_T);
}

float DS18B20_ReadT()
{
    unsigned char TLS_B, TMS_B;
    int Temp;
    float T;
    OneWire_Init();
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
    TLS_B = OneWire_ReceiveByte();
    TMS_B = OneWire_ReceiveByte();

    Temp = (TMS_B << 8) | TLS_B;
    T = Temp / 16.0;
    return T;
}