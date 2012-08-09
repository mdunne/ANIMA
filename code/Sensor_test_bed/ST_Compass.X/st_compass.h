#ifndef ST_COMPASS_H
#define ST_COMPASS_H


void st_compass_init(void);
short st_Get_AccelXData(void);
short st_Get_AccelYData(void);
short st_Get_AccelZData(void);

short st_Get_MagXData(void);
short st_Get_MagYData(void);
short st_Get_MagZData(void);

void st_GetAccelTriplet(short *AxisData);
void st_GetMagTriplet(short *AxisData);


void st_mag_ChangeMode(char Mode);
unsigned char st_mag_GetRate();
unsigned char st_mag_SetRate(char Rate);
unsigned char st_mag_SetGain(char newGain);
unsigned char st_mag_GetGain();

unsigned char st_accel_GetScale();
unsigned char st_accel_SetScale(char scale);
void st_accel_ChangeMode(char Mode);
unsigned char st_accel_SetRate(char Rate);
unsigned char st_accel_GetRate();

typedef enum {
    ST_ACCEL_2GSCALE = 0,
    ST_ACCEL_4GSCALE,
    ST_ACCEL_8GSCALE,
    ST_ACCEL_16GSCALE,
    ST_ACCEL_STANDBYMODE,
    ST_ACCEL_ACTIVEMODE,
    ST_ACCEL_OFF = 0,
    ST_ACCEL_1HERTZ = 1,
    ST_ACCEL_10HERTZ,
    ST_ACCEL_25HERTZ,
    ST_ACCEL_50HERTZ,
    ST_ACCEL_100HERTZ,
    ST_ACCEL_200HERTZ,
    ST_ACCEL_400HERTZ,
    ST_ACCEL_1620HERTZ_LOW,
    ST_ACCEL_1344HERTZ_NORM,
    ST_ACCEL_5376HERTZ_LOW = ST_ACCEL_1344HERTZ_NORM,
    ST_MAG_CONTINUOUS_MODE,
    ST_MAG_SINGLE_MEASUREMENT_MODE,
    ST_MAG_IDLE_MODE,
    ST_MAG_GAIN_1100 = 0,
    ST_MAG_GAIN_855,
    ST_MAG_GAIN_670,
    ST_MAG_GAIN_450,
    ST_MAG_GAIN_330,
    ST_MAG_GAIN_230,
    ST_MAG_RATE_0P75HERTZ = 0,
    ST_MAG_RATE_1P5HERTZ,
    ST_MAG_RATE_3HERTZ,
    ST_MAG_RATE_7P5HERTZ,
    ST_MAG_RATE_15HERTZ,
    ST_MAG_RATE_30HERTZ,
    ST_MAG_RATE_75HERTZ,
    ST_MAG_RATE_220HERTZ
} ST_COMPASS_COMMANDS;
#endif