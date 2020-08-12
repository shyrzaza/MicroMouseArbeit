#include "controller.h"
#include "motor.h"

// PID-Controller Gains
float K_p[NUM_CONTROLLERS];
float K_i[NUM_CONTROLLERS];
float K_d[NUM_CONTROLLERS];

//maximum integration value
float max_I[NUM_CONTROLLERS];
float min_I[NUM_CONTROLLERS];

static float accumulatedError[NUM_CONTROLLERS];
static float previousError[NUM_CONTROLLERS];

void initController(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I);
void updateControlValues(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I);

void initController(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I)
{
    updateControlValues(id, _K_p, _K_i, _K_d, _min_I, _max_I);
    accumulatedError[id] = 0.0f;
    previousError[id] = 0.0f;
}

void updateControlValues(uint8_t id, float _K_p, float _K_i, float _K_d, float _min_I, float _max_I)
{
    K_p[id] = _K_p;
    K_i[id] = _K_i;
    K_d[id] = _K_d;
    max_I[id] = _max_I;
    min_I[id] = _min_I;
}
float GetControl(uint8_t id, float error)
{
    float result = 0;
    accumulatedError[id] += error;
    float pi_error = (error * K_p[id]) + (accumulatedError[id] * K_i[id]);
    if (K_i[id] != 0.0) //clamp integrated value such that the PI part yields at most max_I
    {
        if (pi_error > max_I[id]) {
            accumulatedError[id] = (max_I[id] - error * K_p[id]) / K_i[id];
            pi_error = max_I[id];
        } else if (pi_error < min_I[id]) {
            accumulatedError[id] = (min_I[id] - error * K_p[id]) / K_i[id];
            pi_error = min_I[id];
        }
    }
    result = pi_error + ((error - previousError[id]) * K_d[id]);
    previousError[id] = error;

    return result;
}
