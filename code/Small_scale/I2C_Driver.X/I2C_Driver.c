
#include <xc.h>
#include "I2C_Driver.h"
#include <GenericTypeDefs.h>
#include "stdio.h"
#include <plib.h>
#include <peripheral/i2c.h>
#include <LED.h>
#include "BOARD.h"
#include "serial.h"

#define BIG_ENDIAN



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define NONSTALLMODE

#define F_CPU 80000000L
#define F_PB F_CPU/2
#define USED_I2C I2C2

#define ACCEL_TRIS TRISAbits.TRISA2
#define MAG_TRIS TRISAbits.TRISA3

#define ACCEL_LAT LATAbits.LATA2
#define MAG_LAT LATAbits.LATA3

#define ACCEL_PORT IOPORT_A,BIT_2
#define MAG_PORT IOPORT_A,BIT_3

#define I2CPOWER_TRIS TRISCbits.TRISC0
#define I2CPOWER_LAT LATCbits.LATC0
#define I2CPOWER_PORT IOPORT_C,BIT_0

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static char I2C_Inited = FALSE;

int I2C_Init(unsigned int Rate) {
    unsigned int Real_Rate = 0;
    if (I2C_Inited != TRUE) {
        I2C2CONbits.ON = 0;
        //I2CConfigure(USED_I2C, 0);
        //printf("device was inited");
        //Real_Rate = I2CSetFrequency(USED_I2C, F_PB, Rate);
        ACCEL_TRIS = 0;
        MAG_TRIS = 0;
        PORTSetPinsDigitalOut(ACCEL_PORT);
        PORTSetPinsDigitalOut(MAG_PORT);
        ANSELBbits.ANSB2 = 0;
        ANSELBbits.ANSB3 = 0;
        ACCEL_LAT = 1;
        MAG_LAT = 1;
        if ((MAG_LAT == 1) && (ACCEL_LAT == 1)) {
            printf("Power to the I2C lines was made\r\n");
            I2CPOWER_TRIS = 0;
            PORTSetPinsDigitalOut(I2CPOWER_PORT);
            I2CPOWER_LAT = 1;
        } else {
            printf("Sensors not powered, stalling here\r\n");
            while (1);
        }

        I2C2BRG = (F_PB / (2 * Rate)) - 2;
        //printf("I2C2BRG: %d\r\n",I2C2BRG);
        Real_Rate = (F_PB) / ((I2C2BRG + 2)*2);
        //printf("I2C baud rate: %X\r\n",I2C2BRG);
        //I2CEnable(USED_I2C, TRUE);
        I2C2CONbits.ON = 1;
        //while(1);
        I2C_Inited = TRUE;
        //printf("Configuration Register: %X\r\n",I2C2CON);
    }
    return Real_Rate;
}

short I2C_ReadInt(char I2Caddress, char DeviceRegister) {

    int Data = 0;
    I2C2CONbits.SEN = 1;
    //printf("Sending start condition\r\n");
    while (I2C2CONbits.SEN == 1);
    //char debugchar='0';
    //printf("Start condition sent\r\n");
    I2C2TRN = I2Caddress << 1;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //printf("Accel Ackowledged\r\n");
    I2C2TRN = DeviceRegister;
    //UART2PutChar(debugchar);  //0
    //debugchar++;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //printf("did not nack\r\n");
    I2C2CONbits.RSEN = 1;
    //UART2PutChar(debugchar); //1
    //debugchar++;
    while (I2C2CONbits.RSEN == 1);
    I2C2TRN = (I2Caddress << 1) + 1;
    //UART2PutChar(debugchar); //2
    //debugchar++;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //UART2PutChar(debugchar); //3
    //debugchar++;
    I2C2CONbits.RCEN = 1;
    //while(I2C2CONbits.RCEN==1);
    while (I2C2STATbits.RBF != 1);
#ifdef BIG_ENDIAN
    Data = I2C2RCV << 8;
#else
    Data = I2C2RCV;
#endif
    //	UART2PutChar(debugchar);//4
    //debugchar++;
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN == 1);
    //UART2PutChar(debugchar);
    I2C2CONbits.RCEN = 1;

    //debugchar++;

    while (I2C2STATbits.RBF != 1);
#ifdef BIG_ENDIAN
    Data |= I2C2RCV;
#else
    Data += I2C2RCV << 8;
#endif
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;

    //UART2PutChar(debugchar);
    //debugchar++;

    while (I2C2CONbits.ACKEN == 1);
    I2C2CONbits.ACKDT = 0;
    I2C2CONbits.PEN = 1;

    //UART2PutChar(debugchar);
    //debugchar++;

    while (I2C2CONbits.PEN == 1);
    return Data;


}

void I2C_ReadMultiple(char I2Caddress, char DeviceRegister, char *OutArray, char NumBytes) {
    int Data = 0;
    I2C2CONbits.SEN = 1;
    //printf("Sending start condition\r\n");
    while (I2C2CONbits.SEN == 1);
    //char debugchar='0';
    //printf("Start condition sent\r\n");
    I2C2TRN = I2Caddress << 1;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //printf("Accel Ackowledged\r\n");
    I2C2TRN = DeviceRegister;
    //UART2PutChar(debugchar);  //0
    //debugchar++;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //printf("did not nack\r\n");
    I2C2CONbits.RSEN = 1;
    //UART2PutChar(debugchar); //1
    //debugchar++;
    while (I2C2CONbits.RSEN == 1);
    I2C2TRN = (I2Caddress << 1) + 1;
    //UART2PutChar(debugchar); //2
    //debugchar++;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //UART2PutChar(debugchar); //3
    //debugchar++;

    //receive the first byte of the multiple read
    I2C2CONbits.RCEN = 1;
    while (I2C2STATbits.RBF != 1);
    OutArray[0] = I2C2RCV;

    //iterate through the rest
    //we ack at the beginning as the last byte requires a different ack
    char bytecount = 0;
    for (bytecount = 1; bytecount < (NumBytes); bytecount++) {
        I2C2CONbits.ACKEN = 1;
        while (I2C2CONbits.ACKEN == 1);
        I2C2CONbits.RCEN = 1;
        while (I2C2STATbits.RBF != 1);
        OutArray[bytecount] = I2C2RCV;
    }

    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN == 1);
    I2C2CONbits.ACKDT = 0;
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1);

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

    I2C2CONbits.SEN = 1;
    //printf("sending start condition\r\n");
    while (I2C2CONbits.SEN == 1);
    I2C2TRN = (I2Caddress << 1);
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device address %X Responded with NACK in %s in regards to Register %X\r\n", I2Caddress, __FUNCTION__, DeviceRegister);
#ifdef NONSTALLMODE
        while (!IsTransmitEmpty());
        return -1;
#endif
        while (1);
    }

    I2C2TRN = DeviceRegister;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon address to wake");
#ifdef NONSTALLMODE
        return -1;
#endif
        while (1);
    }
    I2C2TRN = data;
    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon changing to awake mode");
#ifdef NONSTALLMODE
        while (!IsTransmitEmpty());
        return -1;
#endif
        while (1);
    }
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1);

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
    //while(1);
    I2C2CONbits.SEN = 1;

    //printf("I2C address, %X\r\n", I2Caddress);
    // while(1);
    while (!IsTransmitEmpty());
    while (I2C2CONbits.SEN == 1);

    //printf("start condition sent\r\n");
    //while(1);
    //while(!IsTransmitEmpty());
    I2C2TRN = I2Caddress << 1;
    while (I2C2STATbits.TRSTAT != 0) {
        if (IsTransmitEmpty()) {
            //printf("I2C: %d\r\n", I2C2STATbits.TRSTAT);
            //I2C2TRN = I2Caddress << 1;
        }
    }
    //printf("Address transmitted\r\n");
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device address %X Responded with NACK at Read of Register %X\r\n", I2Caddress, DeviceRegister);
        return -1;
        while (1);
    }

    I2C2TRN = DeviceRegister;

    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK2");
        while (1);
    }
    I2C2CONbits.RSEN = 1;

    while (I2C2CONbits.RSEN == 1);
    I2C2TRN = (I2Caddress << 1) + 1;

    while (I2C2STATbits.TRSTAT != 0);
    if (I2C2STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK3");
        while (1);
    }
    I2C2CONbits.RCEN = 1;
    //while(I2C2CONbits.RCEN==1);
    while (I2C2STATbits.RBF != 1);
    data = I2C2RCV;
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN == 1);
    return data;
}