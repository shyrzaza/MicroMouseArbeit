#include <p33FJ128MC804.h>

#include "gpio.h"

void initPins()
{
    int i;

    // set up analogue pins
    AD1CON1bits.ADON = 0; // disable ADC1 module
    AD1PCFGL = 0xFFFF; // all pins are digital

    // set digital port direction
    // Inputs
    TRISBbits.TRISB14 = 1; // Switch

    TRISBbits.TRISB9 = 1; // Encoder
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC8 = 1;
    TRISCbits.TRISC9 = 1;

    // Outputs
    TRISBbits.TRISB10 = 0; // PWM
    TRISBbits.TRISB12 = 0;

    TRISCbits.TRISC4 = 0; // LEDs
    TRISCbits.TRISC5 = 0;
    TRISBbits.TRISB8 = 0;
    TRISCbits.TRISC3 = 0;
    TRISAbits.TRISA9 = 0;

    TRISBbits.TRISB11 = 0; // DIRs
    TRISBbits.TRISB13 = 0;
    TRISAbits.TRISA10 = 0;
    TRISAbits.TRISA7 = 0;

    // disable PMP
    PMCONbits.PMPEN = 1;
    PMAENbits.PTEN = 0;
    PMCONbits.PMPEN = 0;

    DAC1CONbits.DACEN = 0;

    CNEN1 = 0;
    CNEN2 = 0;

    // set up remappable pins
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6 (unlock, they are usually write protected)

    // Configure UART
    RPINR18bits.U1RXR = 6; // UART1 receive U1RX to RP7
    RPOR3bits.RP7R = 3; // UART1 send U1TX to RP6

    // Configure Motor/Quadratur Encoder
    // Motor 1
    RPINR14bits.QEA1R = 9; // QEI1 A
    RPINR14bits.QEB1R = 22; // QEI1 B
    // Motor 2
    RPINR16bits.QEA2R = 24; // QEI2 A
    RPINR16bits.QEB2R = 25; // QEI2 B

    //sensors
    //sensor 0
    TRISBbits.TRISB3 = 1;
    CMCONbits.C1EN = 0;
    RPOR1bits.RP3R = 0;
    
    
    RPOR1bits.RP2R = 0;
    
    
    // default pin output (disable all other peripherals on this pin)
    RPOR10bits.RP20R = 0; // LEDs
    RPOR10bits.RP21R = 0;
    RPOR4bits.RP8R = 0;
    RPOR9bits.RP19R = 0;
    RPOR5bits.RP10R = 0;
    RPOR6bits.RP12R = 0;

    RPOR5bits.RP11R = 0; // DIRs
    RPOR6bits.RP13R = 0;

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers (lock again!)

    for (i = 0; i < 30000; i++)
        ; // short delay
}
