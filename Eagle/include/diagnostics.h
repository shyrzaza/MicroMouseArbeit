#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#define MAX_DEBUG_LENGTH 57 //maximum number of Chars per flushDebug() call; Should be floor(5760/flushes_per_second)

void sendDiagnostics();
void debugFloat(char* name, float value);
void debugInt(char* name, int value);
void flushDebug(); //call at THE END of the timerinterrupt

#endif
