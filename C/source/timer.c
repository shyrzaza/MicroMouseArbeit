#include "timer.h"

#include "diagnostics.h"
#include "gpio.h"
#include "motor.h"

#include "adc.h"
#include "sensor.h"
#include "pwm.h"
#include "uart.h"

void initTimer1(unsigned int period)
{
    T1CON = 0; // ensure Timer 1 is in reset state
    T1CONbits.TGATE = 0; // gated time accumulation disabled
    T1CONbits.TCKPS = 0b10; // FCY divide by 64: tick = 1.6us
    T1CONbits.TCS = 0; // select internal FCY clock source
    TMR1 = 0;
    PR1 = period - 1; // set Timer 1 period register ()
    IFS0bits.T1IF = 0; // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4; // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1; // enable Timer 1 interrupt
    T1CONbits.TON = 0; // leave timer disabled initially
}

void startTimer1(void)
{
    T1CONbits.TON = 1;
}

void initTimer2(unsigned int period)
{
    T2CON = 0; // ensure Timer 1 is in reset state
    T2CONbits.TGATE = 0; // gated time accumulation disabled
    T2CONbits.TCKPS = 0b10; // FCY divide by 64: tick = 1.6us
    T2CONbits.TCS = 0; // select internal FCY clock source
    TMR2 = 0;
    PR2 = period - 1; // set Timer 1 period register ()
    IFS0bits.T2IF = 0; // reset Timer 1 interrupt flag
    IPC1bits.T2IP = 4; // set Timer1 interrupt priority level to 4
    IEC0bits.T2IE = 1; // enable Timer 1 interrupt
    T2CONbits.TON = 0; // leave timer disabled initially
}

void startTimer2(void)
{
    T2CONbits.TON = 1;
}

static float t = 0.0;
float t2 = 0.0;
float freq = 0.5;

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    static int count = 0;
    t = t + TIMER_INTERVAL;

    if (count < 49) {
        count++;

    } else {
        LED0 = ~LED0;
        LED2 = ~LED2;
        LEDB = ~LEDB;
        //LEDF = ~LEDF;
        count = 0;
    }
    //debugInt("Test: ", 42);

    //driveMotorWithVelocity(LEFT_MOTOR, 5);
    //driveMotorWithVelocity(RIGHT_MOTOR, 5);
    //PWMchangeDutyCycle(PWM_LEFT_MOTOR,1);
    //PWMchangeDutyCycle(PWM_RIGHT_MOTOR,1);
    updateMotorValues();
    
    
    debugFloat("Sensor0", getSensorDistance(0));
    debugFloat("Sensor1", getSensorDistance(1));
    debugFloat("Sensor2", getSensorDistance(2));

    
    flushDebug();

    //flushDebug();
    IFS0bits.T1IF = 0; // reset Timer 1 interrupt flag
}

void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
{
    static int count2 = 0;

    if (count2 < 49) {
        count2++;

    } else {
        LED1 = ~LED1;
        count2 = 0;
    }

    IFS0bits.T2IF = 0; // reset Timer 1 interrupt flag
}