#include "diagnostics.h"
#include "uart.h"

#include <stdio.h>
#include <string.h>

char debugString[MAX_DEBUG_LENGTH + 1];
int spaceLeft;

void initDebug()
{
    *debugString = 0;
    spaceLeft = MAX_DEBUG_LENGTH;
}

void flushDebug()
{
    strcat(debugString, "\n");
    sendStringAsync(debugString);
    *debugString = 0; //Should be safe and not conflict with anything
    spaceLeft = MAX_DEBUG_LENGTH;
}

int appendStringToDebug(char* string)
{
    int l = strlen(string);
    if (l > spaceLeft)
        l = spaceLeft;
    strncat(debugString, string, l);
    return spaceLeft -= l;
}

void debugFloat(char* name, float value)
{
    if (!appendStringToDebug(name))
        return;
    char valString[10];
    sprintf(valString, "%f", (double)value);
    if (!appendStringToDebug(valString))
        return;
    if (!appendStringToDebug(","))
        return; //Separator (optional)
}

void debugInt(char* name, int value)
{
    if (!appendStringToDebug(name))
        return;
    char valString[10];
    sprintf(valString, "%d", value);
    if (!appendStringToDebug(valString))
        return;
    if (!appendStringToDebug(","))
        return; //Separator (optional)
}

//@Ceddo bitte nutze hier nur die debugInt/Float und appendStringToDebug.
// Du hast MAX_DEBUG_LENGTH Zeichen pro flush().
// Wenn das nicht reicht, musst du seltener senden (z.B. alle 0.1s => 576 Zeichen)
void sendDiagnostics()
{
    /*
    char infoString[30] = "";

    int32_t res = GetPos();

    char* l = "Pos:";
    strcat(infoString, l);
    //sendStringLib(infoString);

    char posString[10];
    sprintf(posString, "%ld", res);
    //sendStringLib(posString);
    strcat(infoString, posString);

    l = ":";
    //sendStringLib(l);
    strcat(infoString, l);

    l = "Velocity:";
    //sendStringLib(l);
    strcat(infoString, l);

    float vel = GetCurrentVelocity(1);
    sprintf(posString, "%f", (double)vel);
    strcat(infoString, posString);

    //sendStringLib(posString);
    l = "\n";
    strcat(infoString, l);
    sendStringLib(infoString);

     */
}
