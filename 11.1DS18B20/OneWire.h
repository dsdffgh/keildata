#ifndef __ONEWIRE__H__
#define __ONEWIRE__H__

unsigned char OneWire_Init();
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit();
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte();

#endif