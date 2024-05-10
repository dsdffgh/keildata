#ifndef __XPT2406_H__
#define __XPT2406_H__

#define XPT2046_XP_8 0x9C		//0x8C
#define XPT2046_YP_8 0xDC
#define XPT2046_V_BAT_8 0xAC
#define XPT2046_AUX_IN_8 0xEC

#define XPT2046_XP_12 0x94
#define XPT2046_YP_12 0xD4
#define XPT2046_V_BAT_12 0xA4
#define XPT2046_AUX_IN_12 0xE4

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif