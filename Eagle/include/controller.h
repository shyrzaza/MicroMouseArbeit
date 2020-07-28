#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"

#define NUM_CONTROLLERS 4
#define CTRL_VEL_LEFT 0
#define CTRL_VEL_RIGT 1
#define CTRL_POS_2SID 2
#define CTRL_POS_LEFT 3

void initController(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I);
float GetControl(uint8_t id, float error);
void updateControlValues(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I);

#endif
