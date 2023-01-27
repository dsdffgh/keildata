#ifndef __DS1302__H__
#define __DS1302__H__

unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_WriteByte(unsigned char Command, unsigned char Data);
void DS1302_Init();
void DS1302_ReadTime();
void DS1302_SetTime();
void from_BCD(unsigned char* time);
void to_BCD(unsigned char* time);
unsigned char to_BCD__(unsigned char* time);
unsigned char from_BCD__(unsigned char* time);

extern char DS1302_Time[];

#endif