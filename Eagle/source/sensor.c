/*
 * File:   sensor.c
 * Author: thomas
 *
 * Created on 6. Dezember 2019, 12:06
 */

#include "dma.h"
#include "uart.h"
#include "xc.h"

int adcValues[] = { 3071, 2717, 2392, 2065, 1854, 1640, 1490, 1348, 1250, 1154, 1082, 934, 835, 757, 684, 649, 599, 550, 517, 474, 449 };
float cmValues[] = { 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

// returns the measured distance in cm
float adcToDistance(int data)
{
    int lbi = 0;
    while (lbi < 20) {
        if (adcValues[lbi + 1] < data)
            break;
        lbi++;
    }
    //DebugInt("TMP: ", lbi);
    if (lbi == 20)
        return cmValues[20];
    float m1 = (cmValues[lbi + 1] - cmValues[lbi]);
    float m2 = (adcValues[lbi] - adcValues[lbi + 1]);
    float d = (adcValues[lbi] - data);

    return cmValues[lbi] + d * m1 / m2;
}

//TODO take average over multiple samples
int getSensor(uint8_t sensor)
{
    return adcData[0];
}

float getSensorDistance(uint8_t sensor)
{
    return adcToDistance(getSensor(sensor));
}
