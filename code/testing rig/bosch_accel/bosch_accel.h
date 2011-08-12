#ifndef BOSCH_ACCEL_H
#define BOSCH_ACCEL_H


void bosch_accel_init (void);
int bosch_GetXData(void);
int bosch_GetYData(void);
int bosch_GetZData(void);

int bosch_ReadInt(char address);
unsigned char bosch_WriteReg(unsigned char address,unsigned char data);
unsigned char bosch_ReadReg(unsigned char address);
unsigned char bosch_GetScale();
unsigned char bosch_SetScale(char scale);
void bosch_ChangeMode(char Mode);
unsigned char bosch_SetRate(char Rate);
unsigned char bosch_GetRate();


typedef enum{
    BOSCH_1GSCALE=0,
            BOSCH_1_5GSCALE,
            BOSCH_2GSCALE,
            BOSCH_3GSCALE,
        BOSCH_4GSCALE,
	BOSCH_8GSCALE,
        BOSCH_16GSCALE,
	BOSCH_STANDBYMODE,
	BOSCH_ACTIVEMODE,
	BOSCH_10HERTZ=0,
	BOSCH_20HERTZ,
	BOSCH_40HERTZ,
	BOSCH_75HERTZ,
	BOSCH_150HERTZ,
	BOSCH_300HERTZ,
	BOSCH_600HERTZ,
	BOSCH_1200HERTZ,
		
}COMMANDS;
#endif