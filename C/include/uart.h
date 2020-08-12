#ifndef UART_H
#define UART_H
#include "stdint.h"

void initUART();
int sendStringAsync(char* buffer);
void sendCharacter(char c);
#endif
