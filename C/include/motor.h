#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"

#define NO_MOTORS 2

#define LEFT_MOTOR 1
#define RIGHT_MOTOR 0

#define SIGNALS_PER_ROTATION 2112.0

void driveMotorWithVelocity(uint8_t motorID, float velocity);
float getCurrentVelocity(uint8_t motorID);
void updateMotorValues();

#endif
