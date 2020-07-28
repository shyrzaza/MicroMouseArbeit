#include "uart.h"

#include "commands.h"
#include "xc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//command storage for up to 31 chars (+0x00)
static char command[32];
static int cmd_index = 0;
static char* stringToSend = 0; //0 if there is no string to send

void sendCharacterOfString();

void initUART()
{

    U1MODEbits.UARTEN = 0; //1bits, disable uart

    U1BRG = 42; //set baudrate (57,6k)

    U1MODEbits.LPBACK = 0; //1bit, deactivate loopback
    U1MODEbits.WAKE = 0; //1 bit, do not wake up on serial activity
    U1MODEbits.ABAUD = 0; //1 bit, no autobaud detection
    U1MODEbits.PDSEL = 0b00; //2bits, set databits
    U1MODEbits.STSEL = 0; //1bits, number of stopbits -1
    U1STAbits.URXISEL = 0b00; //2bits, react on how many characters?

    IFS0bits.U1RXIF = 0; //1bit, clear interruptflag
    IFS0bits.U1TXIF = 0; //1bit, clear transmission interrupt flag
    IPC2bits.U1RXIP = 4; //receive interrupt priority?
    IEC0bits.U1RXIE = 1; //enable receive interrupts
    IEC0bits.U1TXIE = 1; //enable transmit interrupts

    U1MODEbits.UARTEN = 1; //1 bit enable uart
    U1STAbits.UTXEN = 1; //1 bit enable transmission

    memset(command, 0, 32); //reset command storage
}

void sendCharacter(char c)
{
    U1TXREG = c;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    //safety measure, enter "\n" if you ever get stuck
    if (cmd_index > 30)
        cmd_index = 0;

    //Read a character and store it
    char character = U1RXREG;
    if (character != '\n')
        command[cmd_index++] = character;

    //full command read
    else {
        processCommand(command);
        memset(command, 0, 32); //reset command storage
        cmd_index = 0;
    }

    IFS0bits.U1RXIF = 0; //clear interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    if (stringToSend)
        sendCharacterOfString(); //send next chars
    IFS0bits.U1TXIF = 0; //clear interrupt flag
}

int sendStringAsync(char* s)
{
    //check if the last string has send, otherwise deny the new one
    if (stringToSend)
        return 1;
    stringToSend = s;
    IFS0bits.U1TXIF = 0; //clear transmission interrupt flag
    sendCharacterOfString(); //send first character

    return 0;
}

void sendCharacterOfString()
{
    //write in the buffer
    //as long as buffer is not full (buffer fits exactly 4 chars, 4 Byte)
    while (!U1STAbits.UTXBF && *stringToSend) {
        U1TXREG = *(stringToSend++); //Send next char
    }
    if (!*stringToSend)
        stringToSend = 0; //We are done
}
