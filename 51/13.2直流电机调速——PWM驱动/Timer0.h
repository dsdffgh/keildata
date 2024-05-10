#ifndef __TIMER0_H__
#define __TIMER0_H__

#define FOSC 1104000l                  // Frequency of Oscillator
#define TIMS (65536 - FOSC / 12 / 1000) // Timer Initial Value for 100us
void Timer0_Init();

#endif
