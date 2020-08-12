#ifndef TIMER_H
#define TIMER_H
#include "stdint.h"
#include "xc.h"

#define TIMER_INTERVAL 0.01

extern float freq;

void initTimer1(unsigned int period);
void startTimer1(void);
void initTimer2(unsigned int period);
void startTimer2(void);
#endif
