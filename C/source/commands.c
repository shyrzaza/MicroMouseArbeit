#include "commands.h"

#include "gpio.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//use this to define commands stored in $command
//keep in mind that not everything should be done in an interrupt
void processCommand(char* command)
{
    if (!strcmp(command, "LED ON")) {
        //sendCharacter(0xFF);
        LED1 = 1;
    }
    if (!strcmp(command, "LED OFF"))
        LED1 = 0;
    if (!strcmp(command, "LED SWITCH"))
        LED1 = ~LED1;
    if (!strncmp(command, "ECHO ", 5))
        ;
    //sendCharacter(command[5]);
    if (!strncmp(command, "FREQ ", 5))
        freq = atoi(command + 5);
}
