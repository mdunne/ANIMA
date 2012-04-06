#ifndef I2C_H
#define I2C_H



void I2C_Init(unsigned int Rate);
int I2C_ReadInt(char I2Caddress, char DeviceRegister);
unsigned char I2C_ReadReg(char I2Caddress, char DeviceRegister,char data);
unsigned char I2C_WriteReg(char I2Caddress,char DeviceRegister, char data);


#endif