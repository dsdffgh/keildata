#include <REGX52.H>
#include "Delay.h"
/*
  *  @brief   获取独立按键键码
  *  @param   无
  *  @retva   按键范围0~4
  */

unsigned char key()
{
	unsigned char keynum = 0;
	
	if (P3_1 == 0) {Delay(5);while(P3_1 == 0) ; Delay(5);keynum = 1;}
	if (P3_0 == 0) {Delay(5);while(P3_0 == 0) ; Delay(5);keynum = 2;}
	if (P3_2 == 0) {Delay(5);while(P3_2 == 0) ; Delay(5);keynum = 3;}
	if (P3_3 == 0) {Delay(5);while(P3_3 == 0) ; Delay(5);keynum = 4;}
	
	
	return keynum;
}