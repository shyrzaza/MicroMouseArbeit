#ifndef GPIO_H
#define GPIO_H
#include "xc.h"

// Inputs
#define SW1 PORTBbits.RB14 // Utility Button (UT_BUTTON)

// Outputs
#define LEDF LATCbits.LATC4 // Front LED (LED1)
#define LEDB LATCbits.LATC5 // Back  LED (LED2)
#define LED0 LATBbits.LATB8 // Low Current LED (LC_LED0)
#define LED1 LATCbits.LATC3 // Low Current LED (LC_LED1)
#define LED2 LATAbits.LATA9 // Low Current LED (LC_LED2)

#define DIR00 LATBbits.LATB11 // Motor 0 Direction 0
#define DIR01 LATBbits.LATB13 // Motor 0 Direction 1
#define DIR10 LATAbits.LATA10 // Motor 1 Direction 0
#define DIR11 LATAbits.LATA7 // Motor 1 Direction 1

void initPins();
#endif
