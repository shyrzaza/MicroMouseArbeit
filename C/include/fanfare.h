#ifndef FANFARE_H
#define FANFARE_H

//Tracklist
#define FANFARE_STOP 0
#define FANFARE_ALLE_MEINE_ENTCHEN 1

//Note frequencies based on A4=440Hz
#define F_AS1 58.27
#define F_B1 61.74
#define F_C2 65.41
#define F_CS2 69.30
#define F_D2 73.42
#define F_DS2 77.78
#define F_E2 82.41
#define F_F2 87.31
#define F_FS2 92.50
#define F_G2 98.00
#define F_GS2 103.83
#define F_A2 110.00
#define F_AS2 116.54
#define F_B2 123.47
#define F_C3 130.81

#define N_AS1 0x1
#define N_B1 0x2
#define N_C2 0x4
#define N_CS2 0x8
#define N_D2 0x10
#define N_DS2 0x20
#define N_E2 0x40
#define N_F2 0x80
#define N_FS2 0x100
#define N_G2 0x200
#define N_GS2 0x400
#define N_A2 0x800
#define N_AS2 0x1000
#define N_B2 0x2000
#define N_C3 0x4000
#define N_PAUSE 0x8000
#define N_ENDOFSONG 0

//To be called every TIMER_INTERVAL seconds
void updateFanfare();

//Call to switch to a specific fanfare
void playFanfare(int fanfare);

#endif
