#include "qie.h"

int32_t LNGCNT = 0;

void initQIE()
{
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
}

void __attribute__((__interrupt__, auto_psv)) _QEI1Interrupt(void)
{
    //check if we have under or overflow
    if (POSCNT > 0x7fff) {
        //underflow
        LNGCNT -= 65536;
    } else {
        //overflow
        LNGCNT += 65536;
    }

    IFS3bits.QEI1IF = 0;
}

int32_t GetPos(uint8_t motorID)
{
    return LNGCNT + (POS1CNT);
}

uint16_t GetPosShort(uint8_t motorID)
{
    return POS1CNT;
}
