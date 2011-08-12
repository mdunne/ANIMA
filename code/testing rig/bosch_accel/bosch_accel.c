#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "bosch_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00001110
#define RATE_MASK  0b11110000
#define MODE_MASK  0b00000010

typedef enum {
    CHIP_ID = 0,
    VERSION,
    ACC_X_LSB,
    ACC_X_MSB,
    ACC_Y_LSB,
    ACC_Y_MSB,
    ACC_Z_LSB,
    ACC_Z_MSB,
    STATUS_REG1 = 0x09,
    STATUS_REG2,
    STATUS_REG3,
    STATUS_REG4,
    CTRL_REG0,
    CTRL_REG1,
    CTRL_REG2,
    BW_TCS = 0x20,
    CTRL_REG3,
    CTRL_REG4,
    TCO_Z = 0x30,
    OFFSET_LSB1 = 0x35,
} REGISTERS;


#define I2C_ADDRESS 0x40

void bosch_accel_init(void) {
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
    //bosch_ChangeMode(BOSCH_ACTIVEMODE);
    printf("Device Awakened\r\n");
    return;


}

int bosch_GetXData(void) {
    int XData;
    XData = bosch_ReadInt(ACC_X_LSB);
    return XData;

}

int bosch_GetYData(void) {
    int YData;
    YData = bosch_ReadInt(ACC_Y_LSB);
    return YData;

}

int bosch_GetZData(void) {
    int ZData;
    ZData = bosch_ReadInt(ACC_Z_LSB);
    return ZData;
}

int bosch_ReadInt(char address) {
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

unsigned char bosch_WriteReg(unsigned char address, unsigned char data) {
    int hmm=0;
    hmm=data;
    data&=0x00FF;
    printf("Data to write is %X\r\n",(data));
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

unsigned char bosch_ReadReg(unsigned char address) {
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

void bosch_ChangeMode(char Mode) {
    return;
    unsigned char Cur_Mode = 0;
    Cur_Mode = bosch_ReadReg(CTRL_REG1);
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == BOSCH_STANDBYMODE) {
        bosch_WriteReg(CTRL_REG1, Cur_Mode);
    }
    if (Mode == BOSCH_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        bosch_WriteReg(CTRL_REG1, Cur_Mode);
    }
}
//

unsigned char bosch_GetScale() {
    unsigned char Scale, regist;
    Scale = 255;
    regist = bosch_ReadReg(OFFSET_LSB1);
    regist &= SCALE_MASK;
    Scale = regist >> 1;
    //printf("regist: %X\r\n",regist);
    return Scale;
}

unsigned char bosch_SetScale(char scale) {
    unsigned char regist = 0;
    //bosch_ChangeMode(BOSCH_STANDBYMODE);
    regist = bosch_ReadReg(OFFSET_LSB1);
    //printf("\r\nRegist is %u\r\n",regist);
    regist = (regist & (~SCALE_MASK)) + (scale<<1);
    //printf("\r\nRegist is now %u\r\n",regist);
    bosch_WriteReg(OFFSET_LSB1, regist);
    //bosch_ChangeMode(BOSCH_ACTIVEMODE);
    return 0;

}

//


 unsigned char bosch_GetRate(){
        unsigned char Rate,regist;
        Rate=255;
        regist=bosch_ReadReg(CTRL_REG1);
        regist&=RATE_MASK;
        Rate=regist>>4;
        //printf("regist: %X\r\n",regist);
        return Rate;
}
 //
unsigned char bosch_SetRate(char Rate){
        unsigned char regist;
        //bosch_ChangeMode(BOSCH_STANDBYMODE);
        regist=bosch_ReadReg(BW_TCS);
        regist&=(~RATE_MASK);
        regist=regist+(Rate<<4);
        bosch_WriteReg(BW_TCS,regist);
        //bosch_ChangeMode(BOSCH_ACTIVEMODE);
        return 0;
	
}
/*//


 */