
#include <p32xxxx.h>
#include "I2C_Driver.h"
#include <GenericTypeDefs.h>
#include "stdio.h"
#include <plib.h>
#include <peripheral/i2c.h>
#include <LED.h>

#define BIG_ENDIAN



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define F_CPU 80000000L
#define F_PB F_CPU/2
#define USED_I2C I2C1

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static char I2C_Inited = FALSE;

int I2C_Init(unsigned int Rate) {
    unsigned int Real_Rate = 0;
    if (I2C_Inited != TRUE) {
        I2C1CONbits.ON=0;
        //I2CConfigure(USED_I2C, 0);
        //printf("device was inited");
        //Real_Rate = I2CSetFrequency(USED_I2C, F_PB, Rate);


        I2C1BRG = (F_PB / (2 * Rate)) - 2;
        //printf("I2C1BRG: %d\r\n",I2C1BRG);
        Real_Rate = (F_PB) / ((I2C1BRG + 2)*2);
        //printf("I2C baud rate: %X\r\n",I2C1BRG);
        //I2CEnable(USED_I2C, TRUE);
        I2C1CONbits.ON = 1;
        I2C_Inited=TRUE;
        //printf("Configuration Register: %X\r\n",I2C1CON);
    }
    return Real_Rate;
}

short I2C_ReadInt(char I2Caddress, char DeviceRegister) {

    int Data = 0;
    I2C1CONbits.SEN = 1;
    //printf("Sending start condition\r\n");
    while (I2C1CONbits.SEN == 1);
    //char debugchar='0';
    //printf("Start condition sent\r\n");
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
    //printf("did not nack\r\n");
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
    Data = I2C1RCV;
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
    Data |= I2C1RCV;
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

void I2C_ReadMultiple(char I2Caddress, char DeviceRegister, char *OutArray, char NumBytes) {
    int Data = 0;
    I2C1CONbits.SEN = 1;
    //printf("Sending start condition\r\n");
    while (I2C1CONbits.SEN == 1);
    //char debugchar='0';
    //printf("Start condition sent\r\n");
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
    //printf("did not nack\r\n");
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

    //receive the first byte of the multiple read
    I2C1CONbits.RCEN = 1;
    while (I2C1STATbits.RBF != 1);
    OutArray[0] = I2C1RCV;

    //iterate through the rest
    //we ack at the beginning as the last byte requires a different ack
    char bytecount = 0;
    for (bytecount = 1; bytecount < (NumBytes); bytecount++) {
        I2C1CONbits.ACKEN = 1;
        while (I2C1CONbits.ACKEN == 1);
        I2C1CONbits.RCEN = 1;
        while (I2C1STATbits.RBF != 1);
        OutArray[bytecount] = I2C1RCV;
    }

    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN == 1);
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN == 1);

}

unsigned char I2C_WriteReg(char I2Caddress, char DeviceRegister, char data) {
    //I2C_RESULT Command_Result;
    //    printf("WriteReg beginning\r\n");
    //    Command_Result = I2CStart(USED_I2C);
    //    if (Command_Result != I2C_SUCCESS) {
    //        printf("Start was not successfully sent\r\n");
    //        while (1);
    //    }
    //    printf("Start supposedly sent\r\n");
    //    if (I2CTransmitterIsReady(USED_I2C)) {
    //        //printf("About to send address\r\n");
    //        Command_Result = I2CSendByte(USED_I2C, (I2Caddress << 1) | I2C_WRITE);
    //    }
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

unsigned char I2C_ReadReg(char I2Caddress, char DeviceRegister) {
    //I2C_RESULT Command_Result;
    char bool_result = 0;
    unsigned char data = 0;
    //    printf("ReadReg beginning\r\n");
    //    Command_Result = I2CStart(USED_I2C);
    //    if (Command_Result != I2C_SUCCESS) {
    //        printf("Start was not successfully sent\r\n");
    //        while (1);
    //    }
    //    printf("Start supposedly sent\r\n");
    //    if (I2CTransmitterIsReady(USED_I2C)) {
    //        printf("About to send address\r\n");
    //        Command_Result = I2CSendByte(USED_I2C, (I2Caddress << 1) | I2C_READ);
    //        while(!I2CTransmissionHasCompleted(USED_I2C));
    //        if (Command_Result!=I2C_SUCCESS)
    //        {
    //            printf("Error sending address\r\n");
    //            while(1);
    //        }
    //    }
    //
    //    if(!I2CByteWasAcknowledged(USED_I2C))
    //    {
    //        printf("Packet was not acknowledged for address\r\n");
    //        while(1);
    //    }
    //    if (I2CTransmitterIsReady(USED_I2C)) {
    //        printf("About to send register\r\n");
    //        Command_Result = I2CSendByte(USED_I2C, DeviceRegister);
    //        if (Command_Result!=I2C_SUCCESS)
    //        {
    //            printf("Error sending register\r\n");
    //            while(1);
    //        }
    //    }
    //    while(!I2CTransmissionHasCompleted(USED_I2C));
    //    if(!I2CByteWasAcknowledged(USED_I2C))
    //    {
    //        printf("Packet was not acknowledged for register\r\n");
    //        while(1);
    //    }
    //    Command_Result = I2CRepeatStart(USED_I2C);
    //    if (Command_Result!= I2C_SUCCESS)
    //    {
    //        printf("Repeated start was not successful");
    //        while(1);
    //    }
    //    if (I2CTransmitterIsReady(USED_I2C)) {
    //        printf("About to send address for receive\r\n");
    //        Command_Result = I2CSendByte(USED_I2C, (I2Caddress << 1) | I2C_READ);
    //        if (Command_Result!=I2C_SUCCESS)
    //        {
    //            printf("Error sending address for receive\r\n");
    //            while(1);
    //        }
    //    }
    //    while(!I2CTransmissionHasCompleted(USED_I2C));
    //    if(!I2CByteWasAcknowledged(USED_I2C))
    //    {
    //        printf("Packet was not acknowledged for address\r\n");
    //        while(1);
    //    }
    //    Command_Result=I2CReceiverEnable(USED_I2C,TRUE);
    I2C1CONbits.SEN = 1;

    while (I2C1CONbits.SEN == 1);
    //printf("start condition sent\r\n");
    I2C1TRN = I2Caddress << 1;
    while (I2C1STATbits.TRSTAT != 0);

    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK1");
        while (1);
    }

    I2C1TRN = DeviceRegister;

    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK2");
        while (1);
    }
    I2C1CONbits.RSEN = 1;

    while (I2C1CONbits.RSEN == 1);
    I2C1TRN = (I2Caddress << 1) + 1;

    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK3");
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