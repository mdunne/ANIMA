#ifndef honeywell_mag_H
#define honeywell_mag_H


void honey_mag_init(void);
int honey_mag_GetXData(void);
int honey_mag_GetYData(void);
int honey_mag_GetZData(void);


unsigned char honey_mag_WriteReg(char address, char data);
unsigned char honey_mag_ReadReg(char address);
unsigned char honey_mag_GetGain();
unsigned char honey_mag_SetGain(char inGain);
void honey_mag_ChangeMode(char Mode);
unsigned char honey_mag_SetRate(char Rate);
unsigned char honey_mag_GetRate();

typedef enum {
    HONEY_GAIN_1370 = 0,
    HONEY_GAIN_1090,
    HONEY_GAIN_820,
    HONEY_GAIN_660,
    HONEY_GAIN_440,
    HONEY_GAIN_390,
    HONEY_GAIN_330,
    HONEY_GAIN_230,
    HONEY_RATE_0P75HERTZ = 0,
    HONEY_RATE_1P5HERTZ,
    HONEY_RATE_3HERTZ,
    HONEY_RATE_7P5HERTZ,
    HONEY_RATE_15HERTZ,
    HONEY_RATE_30HERTZ,
    HONEY_RATE_75HERTZ,
    HONEY_CONTINUOUS_MODE,
    HONEY_SINGLE_MEASUREMENT_MODE,
    HONEY_IDLE_MODE,

} COMMANDS;
#endif