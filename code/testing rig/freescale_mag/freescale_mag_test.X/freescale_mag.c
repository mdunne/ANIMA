#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "freescale_mag.h"
#include <I2C.h>


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

void free_mag_init(void) {
    char response = 0;
    //TRISBbits.TRISB9 = 0;
    //TRISBbits.TRISB8 = 0;

    I2C_Init(511);
    printf("Awakening Device\r\n");
    I2C_WriteReg(I2C_ADDRESS,CTRL_REG1,0x1);
    //free_mag_ChangeMode(free_mag_ACTIVEMODE);
    printf("Device Awakened\r\n");
    return;


}

int free_mag_GetXData(void) {
    int XData;
    XData = I2C_ReadInt(I2C_ADDRESS,OUT_X_MSB);
    return XData;

}

int free_mag_GetYData(void) {
    int YData;
    YData = I2C_ReadInt(I2C_ADDRESS,OUT_Y_MSB);
    return YData;

}

int free_mag_GetZData(void) {
    int ZData;
    ZData = I2C_ReadInt(I2C_ADDRESS,OUT_Z_MSB);
    return ZData;

}




//

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