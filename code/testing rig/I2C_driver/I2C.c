
#include "p33FJ64MC802.h"
#include <I2C.h>
#include "uart2.h"
#include <stdio.h>

#define BIG_ENDIAN

void I2C_Init(unsigned int Rate) {
    I2C1CONbits.I2CEN = 0;
    I2C1CONbits.A10M = 0;
    I2C1CONbits.SCLREL = 1;
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.DISSLW = 1;
    I2C1BRG = 511;
    I2C1RCV = 0x0000;
    I2C1TRN = 0;
    I2C1CONbits.I2CEN = 1;
}



int I2C_ReadInt(char I2Caddress, char DeviceRegister) {
    int Data = 0;
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    //char debugchar='0';

    I2C1TRN = I2Caddress << 1;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //printf("Accel Ackowledged\r\n");
    I2C1TRN = DeviceRegister;
    //UART2PutChar(debugchar);  //0
    //debugchar++;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    I2C1CONbits.RSEN = 1;
    //UART2PutChar(debugchar); //1
    //debugchar++;
    while (I2C1CONbits.RSEN == 1);
    I2C1TRN = (I2Caddress << 1) + 1;
    //UART2PutChar(debugchar); //2
    //debugchar++;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //UART2PutChar(debugchar); //3
    //debugchar++;
    I2C1CONbits.RCEN = 1;
    //while(I2C1CONbits.RCEN==1);
    while (I2C1STATbits.RBF != 1);
#ifdef BIG_ENDIAN
    Data = I2C1RCV << 8;
#else
    Data=I2C1RCV;
#endif

    //	UART2PutChar(debugchar);//4
    //debugchar++;
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN == 1);
    //UART2PutChar(debugchar);
    I2C1CONbits.RCEN = 1;

    //debugchar++;

    while (I2C1STATbits.RBF != 1);
#ifdef BIG_ENDIAN
    Data += I2C1RCV;
#else
    Data += I2C1RCV << 8;
#endif
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;

    //UART2PutChar(debugchar);
    //debugchar++;

    while (I2C1CONbits.ACKEN == 1);
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.PEN = 1;

    //UART2PutChar(debugchar);
    //debugchar++;

    while (I2C1CONbits.PEN == 1);
    return Data;


}

unsigned char I2C_WriteReg(char I2Caddress, char DeviceRegister, char data) {

    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    I2C1TRN = (I2Caddress << 1);
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon addressing");
        while (1);
    }

    I2C1TRN = DeviceRegister;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon address to wake");
        while (1);
    }
    I2C1TRN = data;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon changing to awake mode");
        while (1);
    }
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN == 1);

    return 1;
}

//

unsigned char I2C_ReadReg(char I2Caddress, char DeviceRegister, char data) {
    unsigned char data = 0;
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);

    I2C1TRN = I2Caddress << 1;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }

    I2C1TRN = DeviceRegister;

    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    I2C1CONbits.RSEN = 1;

    while (I2C1CONbits.RSEN == 1);
    I2C1TRN = (I2Caddress << 1) + 1;

    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    I2C1CONbits.RCEN = 1;
    //while(I2C1CONbits.RCEN==1);
    while (I2C1STATbits.RBF != 1);
    data = I2C1RCV;
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN == 1);
    return data;
}