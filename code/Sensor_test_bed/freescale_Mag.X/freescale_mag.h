#ifndef freescale_mag_H
#define freescale_mag_H


void free_mag_init (void);
int free_mag_GetXData(void);
int free_mag_GetYData(void);
int free_mag_GetZData(void);


unsigned char free_mag_WriteReg(char address,char data);
unsigned char free_mag_ReadReg(char address);
unsigned char free_mag_GetScale();
unsigned char free_mag_SetScale(char scale);
void free_mag_ChangeMode(char Mode);
unsigned char free_mag_SetRate(char Rate);
unsigned char free_mag_GetRate();
void free_mag_GetTriplet(short *AxisData);

typedef enum{
	FREE_MAG_2GSCALE,
	FREE_MAG_4GSCALE,
	FREE_MAG_8GSCALE,
	FREE_MAG_STANDBYMODE=0,
	FREE_MAG_ACTIVEMODE,
	FREE_MAG_800HERTZ=0,
	FREE_MAG_400HERTZ,
	FREE_MAG_200HERTZ,
	FREE_MAG_100HERTZ,
	FREE_MAG_50HERTZ,
	FREE_MAG_12P5HERTZ,
	FREE_MAG_6P25HERTZ,
	FREE_MAG_1P56HERTZ,
		
}COMMANDS;
#endif