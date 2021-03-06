/*
 * File:   main.c
 * Author: a2-lenz
 *
 * Created on April 5, 2019, 11:20 AM
 */

// FBS
#pragma config BWRP = WRPROTECT_OFF // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
#pragma config GWRP = OFF // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = PRIPLL // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
#pragma config IESO = ON // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = OFF // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS1 // Watchdog Timer Postscaler (1:1)
#pragma config WDTPRE = PR128 // WDT Prescaler (1:128)
#pragma config WINDIS = OFF // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR1 // POR Timer Value (Disabled)
#pragma config ALTI2C = OFF // Alternate I2C  pins off
#pragma config LPOL = ON // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1 // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include "adc.h"
#include "controller.h"
#include "dma.h"
#include "gpio.h"
#include "motor.h"
#include "pwm.h"
#include "qie.h"
#include "timer.h"
#include "uart.h"
#include "xc.h"

#define IN_SIMULATION_MODE 0

//int dat[256];
int main(void)
{
    /*** oscillator setup --------------------------------------------------
    Here we are using PPL for 16MHz to generate 80MHz clock.
    FCY = 0.5 * (16MHz*20/(2*2)) = 40 MIPS
    ---------------------------------------------------------------------***/
    PLLFBD = 18; //set PPL to M=20 (18+2)
    CLKDIVbits.PLLPRE = 0; //N1 = input/2
    CLKDIVbits.PLLPOST = 0; //N2 = output/2
    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x03); // Initiate Clock Switch to Primary

    // Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(OSCCON || 0x01); // Start clock switching
    while (OSCCONbits.COSC != 0b011)
        ;

    if (IN_SIMULATION_MODE != 1) {
        while (OSCCONbits.LOCK != 1)
            ; //Wait for PPL to lock
    }

    //              id              K_p     K_i     K_d     min_I   max_I
    initController(CTRL_VEL_LEFT, 0.3, 0.1, .2, -2, 2);
    initController(CTRL_VEL_RIGT, 0.3, 0.1, .2, -2, 2);
    initPins();
    initPWM();
    initUART();
    initQIE();
    //initDmaChannel4();
    //setupADC1();
    //startADC1();
    initTimer1((int)(625000 * TIMER_INTERVAL)); //625.000 is 1s, based on a 1.6 us base = 40MIPS with 64 prescaler
    startTimer1();
    initTimer2((int)(625000 * TIMER_INTERVAL * 2)); //625.000 is 1s, based on a 1.6 us base = 40MIPS with 64 prescaler
    startTimer2();

    //driveMotorWithVelocity(1, 1.5);

    while (1)
        ;
    return 0;
}
