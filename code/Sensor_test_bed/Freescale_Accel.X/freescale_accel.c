#include <p32xxxx.h>
#include <serial.h>
#include "stdio.h"


#include "freescale_accel.h"
#include <I2C_Driver.h>

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
    F_SETUP = 0x09,
    TRIG_CFG,
    SYSMOD,
    INT_SOURCE,
    WHO_AM_I,
    XYZ_DATA_CFG,
    HP_FILTER_CUTOFF,
    PL_STATUS,
    PL_CFG,
    PL_COUNT,
    PL_BF_ZCOMP,
    P_L_THS_REG,
    FF_MT_CFG,
    FF_MT_SRC,
    FF_MT_THS,
    FF_MT_COUNT,
    TRANSIENT_CFG = 0x1D,
    TRANSIENT_SRC,
    TRANSIENT_THS,
    TRANSIENT_COUNT,
    PULSE_CFG,
    PULSE_SRC,
    PULSE_THSX,
    PULSE_THSY,
    PULSE_THSZ,
    PULSE_TMLT,
    PULSE_LTCY,
    PULSE_WIND,
    ASLP_COUNT,
    CTRL_REG1,
    CTRL_REG2,
    CTRL_REG3,
    CTRL_REG4,
    CTRL_REG5,
    OFF_X,
    OFF_Y,
    OFF_Z
} REGISTERS;

union Data_Access {

    struct {
        unsigned : 2;
        signed AccelData : 14;
    };
    struct {
        unsigned char msb;
        unsigned char lsb;
    };
    short full_data;
} Data_Access;

union Reg_Access{
    
    unsigned char full_register;
}Reg_Access;

#define I2C_ADDRESS 0x1C

void free_accel_init(void) {
    //char response=0;
    I2C_Init(100000);
    //printf("Awakening Device\r\n");
    free_ChangeMode(FREE_ACTIVEMODE);

    //printf("Device Awakened\r\n");
    return;
}

int free_GetXData(void) {
    int XData;
    XData = I2C_ReadInt(I2C_ADDRESS, OUT_X_MSB);
    return XData;

}

int free_GetYData(void) {
    int YData;
    YData = I2C_ReadInt(I2C_ADDRESS, OUT_Y_MSB);
    return YData;

}

int free_GetZData(void) {
    int ZData;
    ZData = I2C_ReadInt(I2C_ADDRESS, OUT_Z_MSB);
    return ZData;

}


//TODO: triplet is acting funny, as the read setting for this are tricky
void free_GetTriplet(short *AxisData) {
    unsigned char RegContents[6];

    char iterate;
    I2C_ReadMultiple(I2C_ADDRESS, OUT_X_MSB, RegContents, 6);
    Data_Access.full_data = 0;
    //Data_Access.msb = 0xDE;
    //Data_Access.lsb = 0xAD;
    //printf("acceleration: %X\r\n", Data_Access.accelation_data.acceleration);
    //printf("full short: %X\r\n", Data_Access.full_data);

    //for Big-Endian lsb should be iterate and msb iterate+1
    for (iterate = 0; iterate < 6; iterate += 2) {
        Data_Access.lsb = RegContents[iterate];
        Data_Access.msb = RegContents[iterate + 1];
        AxisData[iterate >> 1] = Data_Access.AccelData;
    }
}

unsigned char free_GetScale() {
    unsigned char Scale, regist;
    Scale = 255;
    regist = I2C_ReadInt(I2C_ADDRESS, XYZ_DATA_CFG);
    regist &= SCALE_MASK;
    //printf("regist: %X\r\n",regist);
    if (regist == 0)
        Scale = FREE_2GSCALE;
    if (regist == 1)
        Scale = FREE_4GSCALE;
    if (regist == 2)
        Scale = FREE_8GSCALE;

    return Scale;
}

unsigned char free_SetScale(char scale) {

    char regist, fun = XYZ_DATA_CFG;
    free_ChangeMode(FREE_STANDBYMODE);
    regist = I2C_ReadReg(I2C_ADDRESS, XYZ_DATA_CFG);

    if (scale == FREE_2GSCALE)
        regist = (regist & (~SCALE_MASK)) + 0;
    if (scale == FREE_4GSCALE)
        regist = (regist & (~SCALE_MASK)) + 1;
    if (scale == FREE_8GSCALE)
        regist = (regist & (~SCALE_MASK)) + 2;
    //printf("regist: %X\r\n",regist);
    I2C_WriteReg(I2C_ADDRESS, XYZ_DATA_CFG, regist);
    free_ChangeMode(FREE_ACTIVEMODE);
    return 0;

}

//

void free_ChangeMode(char Mode) {
    char Cur_Mode = 0;
    Cur_Mode = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    //printf("reading reg");
    Cur_Mode &= (~MODE_MASK); //remove current mode
    if (Mode == FREE_STANDBYMODE) {
        I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Cur_Mode);
    }
    if (Mode == FREE_ACTIVEMODE) {
        Cur_Mode |= MODE_MASK;
        I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Cur_Mode);
    }
}
//

unsigned char free_SetRate(char Rate) {
    char regist;
    free_ChangeMode(FREE_STANDBYMODE);
    regist = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    regist &= (~RATE_MASK);
    regist = regist + (Rate << 2);
    /*
    if (scale==FREE_2GSCALE)
            regist=(regist&(~SCALE_MASK))+0;
    if (scale==FREE_4GSCALE)
            regist=(regist&(~SCALE_MASK))+1;
    if (scale==FREE_8GSCALE)
            regist=(regist&(~SCALE_MASK))+2;
     */
    I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, regist);
    free_ChangeMode(FREE_ACTIVEMODE);
    return 0;

}
//

unsigned char free_GetRate() {
    unsigned char Rate, regist;
    Rate = 255;
    regist = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    regist &= RATE_MASK;
    Rate = regist >> 2;
    //printf("regist: %X\r\n",regist);
    /*if (regist==0)
            Scale=FREE_2GSCALE;
    if (regist==1)
            Scale=FREE_4GSCALE;
    if (regist==2)
            Scale=FREE_8GSCALE;
     */
    return Rate;
}