
#include <p32xxxx.h>
#include "serial.h"
#include "I2C_Driver.h"
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
    CTRL_REG0 = 0xD,
    CTRL_REG1,
    CTRL_REG2,
    BW_TCS = 0x20,
    CTRL_REG3,
    CTRL_REG4,
    TCO_Z = 0x30,
    OFFSET_LSB1 = 0x35,
} REGISTERS;


#define I2C_ADDRESS 0x40

#define INT_PIN_TRIS TRISDbits.TRISD5
#define INT_PIN PORTDbits.RD5

//bit fields in the struct start at the lsb

union Reg_Access {

    struct {
        unsigned lat_int : 1;
        unsigned new_data_int : 1;
        unsigned adv_int : 1;
        unsigned tapsens_int : 1;
        unsigned low_int : 1;
        unsigned high_int : 1;
        unsigned slope_int : 1;
        unsigned slope_alert : 1;

    } CtrlReg_3;
    unsigned char full_register;
} Reg_Access;

union Data_Access {

    struct {
        unsigned new_data : 1;
        unsigned : 1;
        signed acceleration : 14;

    } accelation_data;

    struct {
        unsigned char lsb;
        unsigned char msb;
    };
    short full_data;
} Data_Access;

void bosch_accel_init(void) {
    char response = 0;
    //    TRISBbits.TRISB9 = 0;
    //    TRISBbits.TRISB8 = 0;
    //    I2C1CONbits.I2CEN = 0;
    //    I2C1CONbits.A10M = 0;
    //    I2C1CONbits.SCLREL = 1;
    //    I2C1CONbits.ACKDT = 0;
    //    I2C1CONbits.DISSLW = 1;
    //    I2C1BRG = 511;
    //    I2C1RCV = 0x0000;
    //    I2C1TRN = 0;
    //    I2C1CONbits.I2CEN = 1;
    I2C_Init(100000);
    //printf("Awakening Device\r\n");
    //bosch_ChangeMode(BOSCH_ACTIVEMODE);
    //printf("Device Awakened\r\n");
    response = I2C_ReadReg(I2C_ADDRESS, CTRL_REG0);
    //printf("CTRL_REG0: %X\r\n", response);
    response |= 0x10;
    I2C_WriteReg(I2C_ADDRESS, CTRL_REG0, response);
    //printf("Control Reg 0: %X",CTRL_REG0);
    return;


}

int bosch_GetXData(void) {
    int XData;
    Data_Access.full_data = I2C_ReadInt(I2C_ADDRESS, ACC_X_LSB);
    XData = Data_Access.accelation_data.acceleration;

    return XData;

}

int bosch_GetYData(void) {
    int YData;
    Data_Access.full_data = I2C_ReadInt(I2C_ADDRESS, ACC_Y_LSB);
    YData = Data_Access.accelation_data.acceleration;
    return YData;

}

int bosch_GetZData(void) {
    int ZData;
    Data_Access.full_data = I2C_ReadInt(I2C_ADDRESS, ACC_Z_LSB);
    ZData = Data_Access.accelation_data.acceleration;
    return ZData;
}

void bosch_GetTriplet(short *AxisData) {
    unsigned char RegContents[6];

    char iterate;
    I2C_ReadMultiple(I2C_ADDRESS, ACC_X_LSB, RegContents, 6);
    Data_Access.full_data = 0;
    Data_Access.msb = 0xDE;
    Data_Access.lsb = 0xAD;
    //printf("acceleration: %X\r\n", Data_Access.accelation_data.acceleration);
    //printf("full short: %X\r\n", Data_Access.full_data);

    for (iterate = 0; iterate < 6; iterate += 2) {
        Data_Access.lsb = RegContents[iterate];
        Data_Access.msb = RegContents[iterate + 1];
        AxisData[iterate >> 1] = Data_Access.accelation_data.acceleration;
    }
}

//



//

void bosch_ChangeMode(char Mode) {
    unsigned char Cur_Mode = 0;
    Cur_Mode = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == BOSCH_STANDBYMODE) {
        I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Cur_Mode);
    }
    if (Mode == BOSCH_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Cur_Mode);
    }
}
//

unsigned char bosch_GetScale() {
    unsigned char Scale, regist;
    Scale = 255;
    regist = I2C_ReadReg(I2C_ADDRESS, OFFSET_LSB1);
    regist &= SCALE_MASK;
    Scale = regist >> 1;
    //printf("regist: %X\r\n",regist);
    return Scale;
}

unsigned char bosch_SetScale(char scale) {
    unsigned char regist = 0;
    //bosch_ChangeMode(BOSCH_STANDBYMODE);
    regist = I2C_ReadReg(I2C_ADDRESS, OFFSET_LSB1);
    //printf("\r\nRegist is %u\r\n",regist);
    regist = (regist & (~SCALE_MASK)) + (scale << 1);
    //printf("\r\nRegist is now %u\r\n",regist);
    I2C_WriteReg(I2C_ADDRESS, OFFSET_LSB1, regist);
    //bosch_ChangeMode(BOSCH_ACTIVEMODE);
    return 0;

}

//

unsigned char bosch_GetRate() {
    unsigned char Rate, regist;
    Rate = 255;
    regist = I2C_ReadReg(I2C_ADDRESS, BW_TCS);
    regist &= RATE_MASK;
    Rate = regist >> 4;
    //printf("regist: %X\r\n",regist);
    return Rate;
}
//

unsigned char bosch_SetRate(char Rate) {
    unsigned char regist;
    //bosch_ChangeMode(BOSCH_STANDBYMODE);
    regist = I2C_ReadReg(I2C_ADDRESS, BW_TCS);
    regist &= (~RATE_MASK);
    regist = regist + (Rate << 4);
    I2C_WriteReg(I2C_ADDRESS, BW_TCS, regist);
    //bosch_ChangeMode(BOSCH_ACTIVEMODE);
    return 0;

}
/*//


 */

// sets up the pin and modifies the settings in the accelerometer

void bosch_SetInterrupt(char IntType) {
    INT_PIN_TRIS = 1;

    switch (IntType) {
        case BOSCH_NEW_DATA_INTERRUPT:
            Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CTRL_REG3);
            //printf("CtrlReg3 before: %X\r\n", Reg_Access.full_register);
            Reg_Access.CtrlReg_3.new_data_int = 1;
            //printf("CtrlReg3 after: %X\r\n", Reg_Access.full_register);
            I2C_WriteReg(I2C_ADDRESS, CTRL_REG3, Reg_Access.full_register);
            break;
    }
}

unsigned char Bosch_IsNewDataReady(void) {
    return INT_PIN;
}