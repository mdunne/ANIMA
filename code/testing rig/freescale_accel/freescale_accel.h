#ifndef FREESCALE_ACCEL_H
#define FREESCALE_ACCEL_H


void free_accel_init (void);
int free_GetXData(void);
int free_GetYData(void);
int free_GetZData(void);

int free_ReadInt(char address);
unsigned char free_WriteReg(char address,char data);
unsigned char free_ReadReg(char address);
unsigned char free_GetScale();
unsigned char free_SetScale(char scale);
void free_ChangeMode(char Mode);
unsigned char free_SetRate(char Rate);
unsigned char free_GetRate();


typedef enum{
	FREE_2GSCALE,
	FREE_4GSCALE,
	FREE_8GSCALE,
	FREE_STANDBYMODE,
	FREE_ACTIVEMODE,
	FREE_800HERTZ=0,
	FREE_400HERTZ,
	FREE_200HERTZ,
	FREE_100HERTZ,
	FREE_50HERTZ,
	FREE_12P5HERTZ,
	FREE_6P25HERTZ,
	FREE_1P56HERTZ,
		
}COMMANDS;
#endif