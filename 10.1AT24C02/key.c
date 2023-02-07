#include <REGX52.H>
#include <Delay.h>

unsigned char KEY_keynum;


unsigned char key()
{
	unsigned char temp = 0;
	temp = KEY_keynum;
	KEY_keynum = 0;
	return temp;
}

unsigned char key_GetState()
{
	unsigned char keynum = 0;
	
	if (P3_1 == 0) {keynum = 1;}
	if (P3_0 == 0) {keynum = 2;}
	if (P3_2 == 0) {keynum = 3;}
	if (P3_3 == 0) {keynum = 4;}
	 
	return keynum;
}

void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState = NowState;
	NowState = key_GetState();
	if(LastState == 1 && NowState == 0 ){KEY_keynum = 1;}
	if(LastState == 2 && NowState == 0 ){KEY_keynum = 2;}
	if(LastState == 3 && NowState == 0 ){KEY_keynum = 3;}
	if(LastState == 4 && NowState == 0 ){KEY_keynum = 4;}

}