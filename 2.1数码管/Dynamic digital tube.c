#include <REGX52.H>
#include "Delay.h"
#include "NixieTube.h"


	void main()
{	
	
	while(1)
	{
//		NixieTube(2,3);
//		Delay(0);
//		NixieTube(3,4);
//		Delay(0);
//		NixieTube(5,7);
//		Delay(0);
//		位选 段选 位选 段选 位选 段选
		
		NixieTube(1,3);

		NixieTube(3,4);

		NixieTube(5,7);
		//单片机直接扫描，会消耗大量cpu时间
	}
}