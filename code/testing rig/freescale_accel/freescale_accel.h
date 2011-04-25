#ifndef FREESCALE_ACCEL_H
#define FREESCALE_ACCEL_H


void free_accel_init (void);
int free_GetXData(void);
int free_GetYData(void);
int free_GetZData(void);

int free_ReadInt(char address);
unsigned char free_WriteReg(char address);
unsigned char free_ReadReg(char address);

#endif