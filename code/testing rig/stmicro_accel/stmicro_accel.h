#ifndef STMICRO_ACCEL_H
#define STMICRO_ACCEL_H


void stmicro_accel_init (void);
int stmicro_GetXData(void);
int stmicro_GetYData(void);
int stmicro_GetZData(void);

int stmicro_ReadInt(char address);
unsigned char stmicro_WriteReg(char address,char data);
unsigned char stmicro_ReadReg(char address);
unsigned char stmicro_GetScale();
unsigned char stmicro_SetScale(char scale);
void stmicro_ChangeMode(char Mode);
unsigned char stmicro_SetRate(char Rate);
unsigned char stmicro_GetRate();


typedef enum{
	STMICRO_2GSCALE,
	STMICRO_4GSCALE,
	STMICRO_8GSCALE,
	STMICRO_STANDBYMODE,
	STMICRO_ACTIVEMODE,
	STMICRO_50HERTZ=0,
	STMICRO_100HERTZ,
	STMICRO_400HERTZ,
	STMICRO_1000HERTZ,	
}COMMANDS;
#endif