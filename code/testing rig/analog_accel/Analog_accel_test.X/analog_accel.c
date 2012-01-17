#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "analog_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00001110
#define RATE_MASK  0b11110000
#define MODE_MASK  0b00000010


//only the

typedef enum {
    DEVID = 0,
    THRESH_TAP = 0x1D,
    OFSX,
    OFSY,
    OFSZ,
    DUR,
    Latent,
    Window,
    THRESH_ACT,
    THRESH_INACT,
    TIME_INACT,
    ACT_INACT_CTL,
    THRESH_FF,
    TIME_FF,
    TAP_AXES,
    ACT_TAP_STATUS,
    BW_RATE,
    POWER_CTL,
    INT_ENABLE,
    INT_MAP,
    INT_SOURCE,
    DATA_FORMAT,
    DATAX0,
    DATAX1,
    DATAY0,
    DATAY1,
    DATAZ0,
    DATAZ1,
    FIFO_CTL,
    FIFO_STATUS
} REGISTERS;


#define I2C_ADDRESS 0x1D

void analog_accel_init(void) {
    char response = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    I2C1CONbits.I2CEN = 0;
    I2C1CONbits.A10M = 0;
    I2C1CONbits.SCLREL = 1;
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.DISSLW = 1;
    I2C1BRG = 511;
    I2C1RCV = 0x0000;
    I2C1TRN = 0;
    I2C1CONbits.I2CEN = 1;

    printf("Awakening Device\r\n");
    analog_WriteReg(POWER_CTL, 1 << 3);
    //set the bandwidth to 400Hz
    analog_WriteReg(BW_RATE, 0xC);
    //set the output to full range
    analog_WriteReg(DATA_FORMAT, 1 << 2);
    //analog_WriteReg(DATA_FORMAT,);
    //analog_ChangeMode(analog_ACTIVEMODE);
    printf("Device Awakened\r\n");
    //response = analog_ReadReg(CTRL_REG0);
    response |= 0x10;
    //analog_WriteReg(CTRL_REG0, response);
    //printf("Control Reg 0: %X",CTRL_REG0);
    return;


}

int analog_GetXData(void) {
    int XData;
    XData = analog_ReadInt(DATAX0);
    return XData;

}

int analog_GetYData(void) {
    int YData;
    YData = analog_ReadInt(DATAY0);
    return YData;

}

int analog_GetZData(void) {
    int ZData;
    ZData = analog_ReadInt(DATAZ0);
    return ZData;
}

int analog_ReadInt(char address) {
    int Data = 0, msB = 0, lsB = 0;

    //Send Start condition and wait
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);


    //Send out address shifted for write
    I2C1TRN = I2C_ADDRESS << 1;

    //wait for device to respond
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        //During debugging failure dies spectacularily
        while (1);
    }
    //printf("Accel Ackowledged\r\n");


    //Send out address to read and wait for ack
    I2C1TRN = address;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }

    //initiate repeated send condition
    I2C1CONbits.RSEN = 1;
    while (I2C1CONbits.RSEN == 1);

    //send out device address, this time for read
    I2C1TRN = (I2C_ADDRESS << 1) + 1;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }


    //recieve byte
    I2C1CONbits.RCEN = 1;
    while (I2C1STATbits.RBF != 1);
    lsB = I2C1RCV;

    //acknowledge byte
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN == 1);

    //receive next byte
    I2C1CONbits.RCEN = 1;
    while (I2C1STATbits.RBF != 1);
    msB = I2C1RCV;

    //set system to send nack
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;

    //send nack
    while (I2C1CONbits.ACKEN == 1);

    //reset system back to ack
    I2C1CONbits.ACKDT = 0;

    //send stop condition
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN == 1);

    Data = (lsB)+(msB << 8);
    Data = Data >> 2;
    return Data;


}


//

unsigned char analog_WriteReg(unsigned char address, unsigned char data) {
    int hmm = 0;
    hmm = data;
    data &= 0x00FF;
    printf("Data to write is %X\r\n", (data));
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    I2C1TRN = (I2C_ADDRESS << 1);
    while (I2C1STATbits.TRSTAT != 0);
    //if (I2C1STATbits.ACKSTAT == 1) {
    //    printf("Device Responded with NACK upon addressing");
    //    while (1);
    //}

    I2C1TRN = address;
    while (I2C1STATbits.TRSTAT != 0);
    //if (I2C1STATbits.ACKSTAT == 1) {
    //    printf("Device Responded with NACK upon address to write");
    //    while (1);
    //}
    I2C1TRN = data;
    while (I2C1STATbits.TRSTAT != 0);
    //if (I2C1STATbits.ACKSTAT == 1) {
    //    printf("Device Responded with NACK upon data");
    //    while (1);
    //}
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN == 1);

    return 1;
}

//

unsigned char analog_ReadReg(unsigned char address) {
    unsigned char data = 0;
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);

    I2C1TRN = I2C_ADDRESS << 1;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }

    I2C1TRN = address;

    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    I2C1CONbits.RSEN = 1;

    while (I2C1CONbits.RSEN == 1);
    I2C1TRN = (I2C_ADDRESS << 1) + 1;

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

void analog_ChangeMode(char Mode) {
    /*
    return;
    unsigned char Cur_Mode = 0;
    Cur_Mode = analog_ReadReg(CTRL_REG1);
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == analog_STANDBYMODE) {
        analog_WriteReg(CTRL_REG1, Cur_Mode);
    }
    if (Mode == analog_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        analog_WriteReg(CTRL_REG1, Cur_Mode);
    }
     */
}
//

unsigned char analog_GetScale() {
    /*
    unsigned char Scale, regist;
    Scale = 255;
    regist = analog_ReadReg(OFFSET_LSB1);
    regist &= SCALE_MASK;
    Scale = regist >> 1;
    //printf("regist: %X\r\n",regist);
    return Scale;
     * */
}

unsigned char analog_SetScale(char scale) {
    /*
    unsigned char regist = 0;
    //analog_ChangeMode(analog_STANDBYMODE);
    regist = analog_ReadReg(OFFSET_LSB1);
    //printf("\r\nRegist is %u\r\n",regist);
    regist = (regist & (~SCALE_MASK)) + (scale << 1);
    //printf("\r\nRegist is now %u\r\n",regist);
    analog_WriteReg(OFFSET_LSB1, regist);
    //analog_ChangeMode(analog_ACTIVEMODE);
    return 0;
     */
}

//

unsigned char analog_GetRate() {/*
    unsigned char Rate, regist;
    Rate = 255;
    regist = analog_ReadReg(CTRL_REG1);
    regist &= RATE_MASK;
    Rate = regist >> 4;
    //printf("regist: %X\r\n",regist);
    return Rate;*/
}

unsigned char analog_SetRate(char Rate) {/*
    unsigned char regist;
    //analog_ChangeMode(analog_STANDBYMODE);
    regist = analog_ReadReg(BW_TCS);
    regist &= (~RATE_MASK);
    regist = regist + (Rate << 4);
    analog_WriteReg(BW_TCS, regist);
    //analog_ChangeMode(analog_ACTIVEMODE);
    return 0;
*/
}
