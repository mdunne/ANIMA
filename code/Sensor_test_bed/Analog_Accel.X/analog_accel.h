#ifndef analog_ACCEL_H
#define analog_ACCEL_H


void analog_accel_init (void);
int analog_GetXData(void);
int analog_GetYData(void);
int analog_GetZData(void);


unsigned char analog_GetScale();
unsigned char analog_SetScale(char scale);
void analog_ChangeMode(char Mode);
unsigned char analog_SetRate(char Rate);
unsigned char analog_GetRate();


typedef enum{
    analog_1GSCALE=0,
            analog_1_5GSCALE,
            analog_2GSCALE,
            analog_3GSCALE,
        analog_4GSCALE,
	analog_8GSCALE,
        analog_16GSCALE,
	analog_STANDBYMODE,
	analog_ACTIVEMODE,
	analog_10HERTZ=0,
	analog_20HERTZ,
	analog_40HERTZ,
	analog_75HERTZ,
	analog_150HERTZ,
	analog_300HERTZ,
	analog_600HERTZ,
	analog_1200HERTZ,
		
}COMMANDS;
#endif