#ifndef PWM_H
#define PWM_H
#include "xc.h"

#define PWM_LEFT_MOTOR 1
#define PWM_RIGHT_MOTOR 0
#define PWM_SPEAKER 2

void initPWM();
void PWMchangeDutyCycle(uint8_t modulator, float dc);

#endif
