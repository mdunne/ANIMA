#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H


int I2C_Init(unsigned int Rate);
short I2C_ReadInt(char I2Caddress, char DeviceRegister);
unsigned char I2C_ReadReg(char I2Caddress, char DeviceRegister);
unsigned char I2C_WriteReg(char I2Caddress,char DeviceRegister, char data);
void I2C_ReadMultiple(char I2Caddress, char DeviceRegister, char *OutArray, char NumBytes);


#endif