#include "qie.h"

int32_t LNG1CNT = 0;
int32_t LNG2CNT = 0;


void initQIE()
{
    //MOTOR LEFT QIE
    QEI1CONbits.QEISIDL = 0;
    QEI1CONbits.QEIM = 0b111;
    QEI1CONbits.SWPAB = 0;
    QEI1CONbits.PCDOUT = 0;
    QEI1CONbits.POSRES = 0;
    QEI1CONbits.TQCS = 0;
    DFLT1CONbits.QEOUT = 0;

    MAX1CNT = 0xffff;
    POS1CNT = 0x0000;

    IFS3bits.QEI1IF = 0;
    IEC3bits.QEI1IE = 1;
    IPC14bits.QEI1IP = 5;
    
    
    //MOTOR RIGHT QIE
    QEI2CONbits.QEISIDL = 0;
    QEI2CONbits.QEIM = 0b111;
    QEI2CONbits.SWPAB = 0;
    QEI2CONbits.PCDOUT = 0;
    QEI2CONbits.POSRES = 0;
    QEI2CONbits.TQCS = 0;
    DFLT2CONbits.QEOUT = 0;

    MAX2CNT = 0xffff;
    POS2CNT = 0x0000;

    IFS4bits.QEI2IF = 0;
    IEC4bits.QEI2IE = 1;
    IPC18bits.QEI2IP = 5;
}

void __attribute__((__interrupt__, auto_psv)) _QEI1Interrupt(void)
{
    //check if we have under or overflow
    if (POS1CNT > 0x7fff) {
        //underflow
        LNG1CNT -= 65536;
    } else {
        //overflow
        LNG1CNT += 65536;
    }

    IFS3bits.QEI1IF = 0;
}

void __attribute__((__interrupt__, auto_psv)) _QEI2Interrupt(void)
{
    //check if we have under or overflow
    if (POS2CNT > 0x7fff) {
        //underflow
        LNG2CNT -= 65536;
    } else {
        //overflow
        LNG2CNT += 65536;
    }

    IFS4bits.QEI2IF = 0;
}


int32_t GetPos(uint8_t motorID)
{
    if(motorID == 0)
    {
        return LNG2CNT + (POS2CNT);
    }
    if(motorID == 1)
    {
        return LNG1CNT + (POS1CNT);
    }
    
    return 0;
}

uint16_t GetPosShort(uint8_t motorID)
{
    return POS1CNT;
}
