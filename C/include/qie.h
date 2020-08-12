// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef QIE_H
#define QIE_H

#include <xc.h> // include processor files - each processor file is guarded.

void initQIE();
int32_t GetPos(uint8_t motorID);
uint16_t GetPosShort(uint8_t motorID);

#endif /* QIE_H */
