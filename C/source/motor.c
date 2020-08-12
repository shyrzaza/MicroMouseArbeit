#include "motor.h"
#include "controller.h"
#include "diagnostics.h"
#include "gpio.h"
#include "pwm.h"
#include "qie.h"
#include "timer.h"
#include "uart.h"

#define DIR_RIGHT 1
#define DIR_STOP 0
#define DIR_LEFT -1

float velocity[NO_MOTORS];
int32_t posCountLastUpdate[NO_MOTORS];
float desiredVelocity[NO_MOTORS];

void driveMotorControlled(uint8_t motorID, float controllerValue);

void setDirection(uint8_t motorID, int8_t direction)
{
    switch (direction) {
    case DIR_RIGHT:
        if (motorID == LEFT_MOTOR) {
            DIR00 = 1;
            DIR01 = 0;
        } else if (motorID == RIGHT_MOTOR) {
            DIR10 = 1;
            DIR11 = 0;
        }
        break;
    case DIR_LEFT:
        if (motorID == LEFT_MOTOR) {
            DIR00 = 0;
            DIR01 = 1;
        } else if (motorID == RIGHT_MOTOR) {
            DIR10 = 0;
            DIR11 = 1;
        }
        break;
    case DIR_STOP:
        if (motorID == LEFT_MOTOR) {
            DIR00 = 0;
            DIR01 = 0;
        } else if (motorID == RIGHT_MOTOR) {
            DIR10 = 0;
            DIR11 = 0;
        }
        break;
    }
}

//Specify which Motor to control and with what velocity (enables controller)
void driveMotorWithVelocity(uint8_t motorID, float velocity)
{
    desiredVelocity[motorID] = velocity;
}

//Specify which Motor to control and which which percentage of maximum power (does not enable controller)
void driveMotorWithValue(uint8_t motorID, float power)
{
    //get direction
    if (power > 0) {
        setDirection(motorID, DIR_RIGHT);
        //Drive pwm using power percentage
        PWMchangeDutyCycle(PWM_LEFT_MOTOR, power); //TODO change this function to support multiple motors
    } else {
        setDirection(motorID, DIR_LEFT);
        //Drive pwm using power percentage
        PWMchangeDutyCycle(PWM_LEFT_MOTOR, -power);
    }
}

//Returns velocity of specified motor
float getCurrentVelocity(uint8_t motorID)
{
    return velocity[motorID];
}

//update should be called regularly
//it updates the current velocity and gets input from the controller
//to drive the motors
void updateMotorValues()
{
    int motorID = 0;
    for (; motorID < NO_MOTORS; motorID++) {
        int32_t pos = GetPos(motorID);
        velocity[motorID] = (pos - posCountLastUpdate[motorID]) / (TIMER_INTERVAL * SIGNALS_PER_ROTATION);
        posCountLastUpdate[motorID] = pos;
        //get control value
        float error = desiredVelocity[motorID] - velocity[motorID];

        float controlValue = GetControl(motorID, error);
        //debugFloat("CV: ", controlValue);
        
        //todo optimieren
        if(motorID==0)
        {
            //debugFloat("M1 des", desiredVelocity[0]);            
            //debugFloat("M1 cur", velocity[0]);
            //debugInt("M1 pos", pos);
        }
        if(motorID==1)
        {
            
        }
        driveMotorControlled(motorID, controlValue);
    }
}

//Drives the motor using the values from the controller
void driveMotorControlled(uint8_t motorID, float controllerValue)
{
    //use controllerValue to derive pwm duty percentage and output via PWM
    if (desiredVelocity[motorID] == 0.0f) //to save on nerves :/
    {
        setDirection(motorID, DIR_STOP);
        if(motorID == 0)
        {
            //PWM_RIGHT_MOTOR is 0    
            PWMchangeDutyCycle(PWM_RIGHT_MOTOR, 0);    
        }
        if(motorID == 1)
        {
            PWMchangeDutyCycle(PWM_LEFT_MOTOR, 0);        
        }
    } else if (controllerValue > 0) {
        //turn right
        setDirection(motorID, DIR_RIGHT);
        //Drive pwm using power percentage
        if(motorID == 0)
        {
            //PWM_RIGHT_MOTOR is 0    
            PWMchangeDutyCycle(PWM_RIGHT_MOTOR, controllerValue);    
        }
        if(motorID == 1)
        {
            PWMchangeDutyCycle(PWM_LEFT_MOTOR, controllerValue);        
        }
    } else {
        //turn left
        setDirection(motorID, DIR_LEFT);
        if(motorID == 0)
        {
            //PWM_RIGHT_MOTOR is 0    
            PWMchangeDutyCycle(PWM_RIGHT_MOTOR, -controllerValue);    
        }
        if(motorID == 1)
        {
            PWMchangeDutyCycle(PWM_LEFT_MOTOR, -controllerValue);        
        }
    }
}
