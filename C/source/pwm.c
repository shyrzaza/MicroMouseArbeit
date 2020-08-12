#include "pwm.h"

void initPWM()
{
    // Disable PWMs
    P1TCONbits.PTEN = 0;
    P2TCONbits.PTEN = 0;

    // Set Pins to I/O or PWM output
    PWM1CON1bits.PEN1H = 0;
    //PWM1CON1bits.PEN1L = 0;
    //PWM1CON1bits.PEN2H = 0;
    PWM1CON1bits.PEN2L = 0;
    //PWM1CON1bits.PEN3H = 0;
    PWM1CON1bits.PEN3L = 0;
    PWM2CON1bits.PEN1H = 0;
    PWM2CON1bits.PEN1L = 0;

    //2bits divide by 4
    P1TCONbits.PTCKPS = 0b01;
    P1TCONbits.PTOPS = 0b0000;
    P1TCONbits.PTSIDL = 1;
    P2TCONbits.PTCKPS = 0b01;
    P2TCONbits.PTOPS = 0b0000;
    P2TCONbits.PTSIDL = 1;

    //15bits aber verdoppelt, max vermutlich

    //jetzt 10 Mhz
    //maximale frequenz ist 40MHZ / FFFF waeren 1220Hz
    P1TPER = 10000 - 1; // 1khz
    P2TPER = 10000 - 1; // 1khz

    // initial pdc 00% (16 bit values)
    P1DC1 = 0;
    P1DC2 = 0;
    P1DC3 = 0;
    P2DC1 = 0;

    //1bit independent mode
    PWM1CON1bits.PMOD1 = 1;
    PWM1CON1bits.PMOD2 = 1;
    PWM1CON1bits.PMOD3 = 1;
    PWM2CON1bits.PMOD1 = 1;

    // enable output
    PWM1CON1bits.PEN3H = 1; // Motors
    
    //old motor 0 broken and thus disabled
    PWM1CON1bits.PEN2H = 0;
    //new motor0
    PWM2CON1bits.PEN1L = 1; // Speaker (currently disabled)

    // enable PWMs
    P1TCONbits.PTEN = 1;
    P2TCONbits.PTEN = 1;
}

// Warning: Maximum DC for the motors is 2/3 !
// Using 9V, everything above may break them
float maximumDC[] = { 0.55f, 0.55f, 1.0f };

void PWMchangeDutyCycle(uint8_t modulator, float dc)
{
    //clamp values to prevent hardware damage
    if (dc > maximumDC[modulator])
        dc = maximumDC[modulator];
    if (dc < 0.0)
        dc = 0.0;

    switch (modulator) {
    case PWM_LEFT_MOTOR:
        P1DC3 = ((P1TPER + 1) * 2) * dc;
        break;
    case PWM_RIGHT_MOTOR:
        //P1DC2 = ((P1TPER + 1) * 2) * dc;
        P2DC1 = ((P2TPER + 1) * 2) * dc;
        break;
    case PWM_SPEAKER:
        P2DC1 = ((P2TPER + 1) * 2) * dc;
        break;
    }
}