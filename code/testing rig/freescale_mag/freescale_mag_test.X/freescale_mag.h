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


typedef enum{
	free_mag_2GSCALE,
	free_mag_4GSCALE,
	free_mag_8GSCALE,
	free_mag_STANDBYMODE,
	free_mag_ACTIVEMODE,
	free_mag_800HERTZ=0,
	free_mag_400HERTZ,
	free_mag_200HERTZ,
	free_mag_100HERTZ,
	free_mag_50HERTZ,
	free_mag_12P5HERTZ,
	free_mag_6P25HERTZ,
	free_mag_1P56HERTZ,
		
}COMMANDS;
#endif