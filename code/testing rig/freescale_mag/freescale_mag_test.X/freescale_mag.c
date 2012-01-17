#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "freescale_mag.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00000011
#define RATE_MASK 0b00111000
#define MODE_MASK 0x01

typedef enum {
    STATUS = 0x00,
    OUT_X_MSB,
    OUT_X_LSB,
    OUT_Y_MSB,
    OUT_Y_LSB,
    OUT_Z_MSB,
    OUT_Z_LSB,
    WHO_AM_I,
    SYSMOD,
    OFF_X_MSB,
    OFF_X_LSB,
    OFF_Y_MSB,
    OFF_Y_LSB,
    OFF_Z_MSB,
    OFF_Z_LSB,
    DIE_TEMP,
    CTRL_REG1,
    CTRL_REG2
} REGISTERS;

#define I2C_ADDRESS 0xE

void free_mag_accel_init(void) {
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
    free_mag_WriteReg(CTRL_REG1,0x1);
    //free_mag_ChangeMode(free_mag_ACTIVEMODE);
    printf("Device Awakened\r\n");
    return;


}

int free_mag_GetXData(void) {
    int XData;
    XData = free_mag_ReadInt(OUT_X_MSB);
    return XData;

}

int free_mag_GetYData(void) {
    int YData;
    YData = free_mag_ReadInt(OUT_Y_MSB);
    return YData;

}

int free_mag_GetZData(void) {
    int ZData;
    ZData = free_mag_ReadInt(OUT_Z_MSB);
    return ZData;

}

int free_mag_ReadInt(char address) {
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
    //printf("Accel Ackowledged\r\n");
    I2C1TRN = address;
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
    I2C1TRN = (I2C_ADDRESS << 1) + 1;
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
    Data = I2C1RCV << 8;


    //	UART2PutChar(debugchar);//4
    //debugchar++;
    I2C1CONbits.ACKEN = 1;
    while (I2C1CONbits.ACKEN == 1);
    //UART2PutChar(debugchar);
    I2C1CONbits.RCEN = 1;

    //debugchar++;

    while (I2C1STATbits.RBF != 1);
    Data += I2C1RCV;
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
    Data = Data;
    return Data;


}


//

unsigned char free_mag_WriteReg(char address, char data) {

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

unsigned char free_mag_ReadReg(char address) {
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
//ALL FUNCTIONS BEYOND THIS POINT ARE UN-IMPLEMENTED
unsigned char free_mag_GetScale() {
    /*
    unsigned char Scale, regist;
    Scale = 255;
    regist = free_mag_ReadReg(XYZ_DATA_CFG);
    regist &= SCALE_MASK;
    //printf("regist: %X\r\n",regist);
    if (regist == 0)
        Scale = free_mag_2GSCALE;
    if (regist == 1)
        Scale = free_mag_4GSCALE;
    if (regist == 2)
        Scale = free_mag_8GSCALE;

    return Scale;*/
}

unsigned char free_mag_SetScale(char scale) {
/*
    char regist, fun = XYZ_DATA_CFG;
    free_mag_ChangeMode(free_mag_STANDBYMODE);
    regist = free_mag_ReadReg(XYZ_DATA_CFG);

    if (scale == free_mag_2GSCALE)
        regist = (regist & (~SCALE_MASK)) + 0;
    if (scale == free_mag_4GSCALE)
        regist = (regist & (~SCALE_MASK)) + 1;
    if (scale == free_mag_8GSCALE)
        regist = (regist & (~SCALE_MASK)) + 2;
    free_mag_WriteReg(XYZ_DATA_CFG, regist);
    free_mag_ChangeMode(free_mag_ACTIVEMODE);
    return 0;
*/
}

//

void free_mag_ChangeMode(char Mode) {
    /*
    char Cur_Mode = 0;
    Cur_Mode = free_mag_ReadReg(CTRL_REG1);
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == free_mag_STANDBYMODE) {
        free_mag_WriteReg(CTRL_REG1, Cur_Mode);
    }
    if (Mode == free_mag_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        free_mag_WriteReg(CTRL_REG1, Cur_Mode);
    }*/
}
//

unsigned char free_mag_SetRate(char Rate) {
    /*
    char regist;
    free_mag_ChangeMode(free_mag_STANDBYMODE);
    regist = free_mag_ReadReg(CTRL_REG1);
    regist &= (~RATE_MASK);
    regist = regist + (Rate << 2);
    /*
    if (scale==free_mag_2GSCALE)
            regist=(regist&(~SCALE_MASK))+0;
    if (scale==free_mag_4GSCALE)
            regist=(regist&(~SCALE_MASK))+1;
    if (scale==free_mag_8GSCALE)
            regist=(regist&(~SCALE_MASK))+2;
     
    free_mag_WriteReg(CTRL_REG1, regist);
    free_mag_ChangeMode(free_mag_ACTIVEMODE);
    return 0;
*/
}
//

unsigned char free_mag_GetRate() {
    unsigned char Rate, regist;
    Rate = 255;
    regist = free_mag_ReadReg(CTRL_REG1);
    regist &= RATE_MASK;
    Rate = regist >> 2;
    //printf("regist: %X\r\n",regist);
    /*if (regist==0)
            Scale=free_mag_2GSCALE;
    if (regist==1)
            Scale=free_mag_4GSCALE;
    if (regist==2)
            Scale=free_mag_8GSCALE;
     */
    return Rate;
}