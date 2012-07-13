#ifndef BOSCH_ACCEL_H
#define BOSCH_ACCEL_H


void bosch_accel_init(void);
int bosch_GetXData(void);
int bosch_GetYData(void);
int bosch_GetZData(void);


unsigned char bosch_GetScale();
unsigned char bosch_SetScale(char scale);
void bosch_ChangeMode(char Mode);
unsigned char bosch_SetRate(char Rate);
unsigned char bosch_GetRate();
void bosch_SetInterrupt(char );
unsigned char Bosch_IsNewDataReady(void);
void bosch_GetTriplet(short *AxisData);

typedef enum {
    BOSCH_1GSCALE = 0,
    BOSCH_1_5GSCALE,
    BOSCH_2GSCALE,
    BOSCH_3GSCALE,
    BOSCH_4GSCALE,
    BOSCH_8GSCALE,
    BOSCH_16GSCALE,
    BOSCH_STANDBYMODE,
    BOSCH_ACTIVEMODE,
    BOSCH_10HERTZ = 0,
    BOSCH_20HERTZ,
    BOSCH_40HERTZ,
    BOSCH_75HERTZ,
    BOSCH_150HERTZ,
    BOSCH_300HERTZ,
    BOSCH_600HERTZ,
    BOSCH_1200HERTZ,
    BOSCH_NEW_DATA_INTERRUPT
} BOSCH_COMMANDS;
#endif