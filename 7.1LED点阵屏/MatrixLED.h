#ifndef __MATIRXLED__H__
#define __MATIRXLED__H__

		void Matrix_LEDInit();
    void _74HC595_WriteByte_(unsigned char Byte);
    void MatrixLED_ShowColumn(unsigned char Column , unsigned char Data);

#endif