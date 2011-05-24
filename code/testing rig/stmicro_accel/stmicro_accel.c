
#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "stmicro_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00011000
#define RATE_MASK  0b00011000
#define MODE_MASK  0b00100000

typedef enum {
    WHO_AM_I = 0x0F,
    CTRL_REG1 = 0x20,
    CTRL_REG2,
    CTRL_REG3,
    CTRL_REG4,
    CTRL_REG5,
    HP_FILTER_RESET,
    REFERENCE,
    STATUS_REG,
    OUT_X_L,
    OUT_X_H,
    OUT_Y_L,
    OUT_Y_H,
    OUT_Z_L,
    OUT_Z_H,
    INT1_CFG = 0x30,
    INT1_SOURCE,
    INT1_THS,
    INT1_DURATION,
    INT2_CFG,
    INT2_SOURCE,
    INT2_THS,
    INT2_DURATION
} regToReadERS;

#define I2C_ADDRESS 0b0011000

void stmicro_accel_init(void) {
    //char response = 0;
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
    stmicro_ChangeMode(STMICRO_ACTIVEMODE);
    printf("Device Awakened\r\n");
    return;


}

int stmicro_GetXData(void) {
    int XData;
    XData = stmicro_ReadInt(OUT_X_L);
    return XData;

}

int stmicro_GetYData(void) {
    int YData;
    YData = stmicro_ReadInt(OUT_Y_L);
    return YData;

}

int stmicro_GetZData(void) {
    int ZData;
    ZData = stmicro_ReadInt(OUT_Z_L);
    return ZData;

}


// due to nature of ST chip this function assumes LSB bits are first

int stmicro_ReadInt(char address) {
    int Data = 0;
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    //char debugchar='0';

    I2C1TRN = I2C_ADDRESS << 1;
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK");
        while (1);
    }
    //add 1 to most significant bit to indicate multi-byte read
    I2C1TRN = address + 0x80;

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
    Data = I2C1RCV;


    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN == 1);
    //UART2PutChar(debugchar);
    I2C1CONbits.RCEN = 1;

    //debugchar++;

    while (I2C1STATbits.RBF != 1);
    Data += (I2C1RCV << 8);
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;



    while (I2C1CONbits.ACKEN == 1);
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.PEN = 1;



    while (I2C1CONbits.PEN == 1);
    Data = Data >> 2;
    return Data;


}


//

unsigned char stmicro_WriteReg(char address, char data) {
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    I2C1TRN = (I2C_ADDRESS << 1);
    while (I2C1STATbits.TRSTAT != 0);
    if (I2C1STATbits.ACKSTAT == 1) {
        printf("Device Responded with NACK upon addressing");
        while (1);
    }

    I2C1TRN = address;
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

unsigned char stmicro_ReadReg(char address) {
    unsigned char data = 0;
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN == 1);
    //printf("%X",I2C_ADDRESS);
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

//

unsigned char stmicro_GetScale() {
    unsigned char Scale, regToRead;
    Scale = 255;
    regToRead = stmicro_ReadReg(CTRL_REG4);
    regToRead &= SCALE_MASK;
    regToRead = regToRead >> 4;
    //printf("regToRead: %X\r\n", regToRead);
    if (regToRead == 0b00)
        Scale = STMICRO_2GSCALE;
    if (regToRead == 0b01)
        Scale = STMICRO_4GSCALE;
    if (regToRead == 0b11)
        Scale = STMICRO_8GSCALE;

    return Scale;
}

/**
 *
 * @param scale
 * @return
 */
unsigned char stmicro_SetScale(char scale) {
    char regToRead;
    stmicro_ChangeMode(STMICRO_STANDBYMODE);
    regToRead = stmicro_ReadReg(CTRL_REG4);
    if (scale == STMICRO_2GSCALE)
        regToRead = (regToRead & (~SCALE_MASK))+(0b00 << 4);
    if (scale == STMICRO_4GSCALE)
        regToRead = (regToRead & (~SCALE_MASK))+(0b01 << 4);
    if (scale == STMICRO_8GSCALE)
        regToRead = (regToRead & (~SCALE_MASK))+(0b11 << 4);
    stmicro_WriteReg(CTRL_REG4, regToRead);
    stmicro_ChangeMode(STMICRO_ACTIVEMODE);
    return 0;
}

//

/** 
 * changes the mode for the device
 * @param Mode
 * #define for mode type: Currently only Active and Standby
 */
void stmicro_ChangeMode(char Mode) {
    char Cur_Mode = 0;
    Cur_Mode = stmicro_ReadReg(CTRL_REG1);
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == STMICRO_STANDBYMODE) {
        stmicro_WriteReg(CTRL_REG1, Cur_Mode);
    }
    if (Mode == STMICRO_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        stmicro_WriteReg(CTRL_REG1, Cur_Mode);
    }
}
//

unsigned char stmicro_SetRate(char Rate) {
    char regToRead;
    stmicro_ChangeMode(STMICRO_STANDBYMODE);
    regToRead = stmicro_ReadReg(CTRL_REG1);
    regToRead &= (~RATE_MASK);
    regToRead = regToRead + (Rate << 3);
    
    if (Rate==STMICRO_2GSCALE)
            regToRead=(regToRead&(~SCALE_MASK))+(0<<3);
    if (Rate==STMICRO_4GSCALE)
            regToRead=(regToRead&(~SCALE_MASK))+(1<<3);
    if (Rate==STMICRO_8GSCALE)
            regToRead=(regToRead&(~SCALE_MASK))+(2<<3);
    stmicro_WriteReg(CTRL_REG1, regToRead);
    stmicro_ChangeMode(STMICRO_ACTIVEMODE);
    return 0;

}
//

unsigned char stmicro_GetRate() {
    unsigned char Rate, regToRead;
    Rate = 255;
    regToRead = stmicro_ReadReg(CTRL_REG1);
    regToRead &= RATE_MASK;
    Rate = regToRead >> 3;
    //printf("regToRead: %X\r\n",regToRead);
    /*if (regToRead==0)
            Scale=STMICRO_2GSCALE;
    if (regToRead==1)
            Scale=STMICRO_4GSCALE;
    if (regToRead==2)
            Scale=STMICRO_8GSCALE;
     */
    return Rate;
}