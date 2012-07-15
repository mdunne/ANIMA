#include <p32xxxx.h>
#include "stdio.h"
#include <I2C_Driver.h>

#include "analog_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00001110
#define RATE_MASK  0b11110000
#define MODE_MASK  0b00000010


//only the

typedef enum {
    DEVICEID = 0,
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
    I2C_Init(100000);

    printf("Awakening Device\r\n");
    I2C_WriteReg(I2C_ADDRESS,POWER_CTL, 1 << 3);
    //set the bandwidth to 400Hz
    I2C_WriteReg(I2C_ADDRESS,BW_RATE, 0xC);
    //set the output to full range
    I2C_WriteReg(I2C_ADDRESS,DATA_FORMAT, 1 << 2);
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
    XData = I2C_ReadInt(I2C_ADDRESS,DATAX0);
    return XData;

}

int analog_GetYData(void) {
    int YData;
    YData = I2C_ReadInt(I2C_ADDRESS,DATAY0);
    return YData;

}

int analog_GetZData(void) {
    int ZData;
    ZData = I2C_ReadInt(I2C_ADDRESS,DATAZ0);
    return ZData;
}
//


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
