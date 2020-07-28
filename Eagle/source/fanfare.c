#include "fanfare.h"

#include "pwm.h"
#include "timer.h"

#include <math.h>

#define TAU 6.2832

float t = 0.0f;

int fanfare_AlleMeineEntchen[] = { 240, 1, //240 Beats per Minute, 1 Channel
    N_C2, N_PAUSE, N_D2, N_PAUSE, //Alle
    N_E2, N_PAUSE, N_F2, N_PAUSE, //meine
    N_G2, N_G2, N_PAUSE, N_PAUSE, //Ent-
    N_G2, N_G2, N_PAUSE, N_PAUSE, //chen
    N_A2, N_PAUSE, N_A2, N_PAUSE, //schwimmen
    N_A2, N_PAUSE, N_A2, N_PAUSE, //auf dem
    N_G2, N_G2, N_G2, N_G2, //See.
    N_PAUSE, N_PAUSE, N_PAUSE, N_PAUSE,
    N_A2, N_PAUSE, N_A2, N_PAUSE, //Schwimmen
    N_A2, N_PAUSE, N_A2, N_PAUSE, //auf dem
    N_G2, N_G2, N_G2, N_G2, //See.
    N_PAUSE, N_PAUSE, N_PAUSE, N_PAUSE,
    N_F2, N_PAUSE, N_F2, N_PAUSE, //Köpfchen
    N_F2, N_PAUSE, N_F2, N_PAUSE, //in das
    N_E2, N_E2, N_PAUSE, N_PAUSE, //Was-
    N_E2, N_E2, N_PAUSE, N_PAUSE, //ser
    N_D2, N_PAUSE, N_D2, N_PAUSE, //Schwänzchen
    N_D2, N_PAUSE, N_D2, N_PAUSE, //in die
    N_C2, N_C2, N_C2, N_C2, //Höh
    N_PAUSE, N_PAUSE, N_PAUSE, N_PAUSE, N_ENDOFSONG };

int16_t* currentSong = 0;
float BPM = 0;
float channelNum = 1;

// creates a sound from a given base frequency (output in [-1,1])
float createSound(float baseFreq)
{
    return sin(TAU * t * baseFreq);
}

// calculates and applies the new duty cycle
void updateFanfare()
{
    if (!currentSong)
        return; //Nothing to play

    t += TIMER_INTERVAL;
    int16_t currentSound = currentSong[2 + (int)(t / 60 * BPM)];

    float amplitude = 0.0f;

    if (currentSound == N_ENDOFSONG)
        currentSong = 0; //Song finished
    if (currentSound != N_PAUSE) //Add frequencies to our sound
    {
        if (currentSound & N_AS1)
            amplitude += createSound(F_AS1);
        if (currentSound & N_B1)
            amplitude += createSound(F_B1);
        if (currentSound & N_C2)
            amplitude += createSound(F_C2);
        if (currentSound & N_CS2)
            amplitude += createSound(F_CS2);
        if (currentSound & N_D2)
            amplitude += createSound(F_D2);
        if (currentSound & N_DS2)
            amplitude += createSound(F_DS2);
        if (currentSound & N_E2)
            amplitude += createSound(F_E2);
        if (currentSound & N_F2)
            amplitude += createSound(F_F2);
        if (currentSound & N_FS2)
            amplitude += createSound(F_FS2);
        if (currentSound & N_G2)
            amplitude += createSound(F_G2);
        if (currentSound & N_GS2)
            amplitude += createSound(F_GS2);
        if (currentSound & N_A2)
            amplitude += createSound(F_A2);
        if (currentSound & N_AS2)
            amplitude += createSound(F_AS2);
        if (currentSound & N_B2)
            amplitude += createSound(F_B2);
        if (currentSound & N_C3)
            amplitude += createSound(F_C3);
    }

    amplitude = 0.5 * amplitude / channelNum + 0.5; //map [-channelNum,channelNum]to[0,1]

    PWMchangeDutyCycle(PWM_SPEAKER, amplitude); //Output Song
}

int16_t* decodeFanfare(int fanfare)
{
    switch (fanfare) {
    case FANFARE_STOP:
        return 0;
    case FANFARE_ALLE_MEINE_ENTCHEN:
        return fanfare_AlleMeineEntchen;
    }
    return 0;
}

void playFanfare(int fanfare)
{
    int16_t* fanRef = decodeFanfare(fanfare);

    t = 0.0f;
    currentSong = fanRef;
    if (currentSong) {
        BPM = currentSong[0];
        channelNum = currentSong[1];
    }
}
