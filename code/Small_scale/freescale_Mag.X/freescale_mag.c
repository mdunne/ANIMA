#include <xc.h>
#include <serial.h>
#include "stdio.h"


#include "freescale_mag.h"
#include <I2C_Driver.h>


#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000

#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00000011
#define RATE_MASK 0b11100000
#define MODE_MASK 0x01
#define OVER_MASK 0b00011000

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



//bit fields in the struct start at the lsb

union Reg_Access {

    struct {
        unsigned operating_mode : 1;
        unsigned trigger_measurement : 1;
        unsigned fast_read : 1;
        unsigned CombinedRate : 5;

    } CtrlReg_1;

    struct {
        unsigned : 4;
        unsigned Mag_RST : 1;
        unsigned Raw : 1;
        unsigned : 1;
        unsigned Auto_MRST_En : 1;
    } CtrlReg_2;
    unsigned char full_register;
} Reg_Access;

union Data_Access {

    struct {
        unsigned char lsb;
        unsigned char msb;
    };
    short full_data;
} Data_Access;

void free_mag_init(void) {
    char response = 0;
    //TRISBbits.TRISB9 = 0;
    //TRISBbits.TRISB8 = 0;

    I2C_Init(400000);
    // printf("Awakening Device\r\n");
    //I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, 0x1);
    //response=I2C_ReadReg(I2C_ADDRESS,CTRL_REG1);
    //printf("Control Reg: %X\r\n",response);
    //while(1);
    //Reg_Access.CtrlReg_1.oversample = 0b11;
    Reg_Access.CtrlReg_1.CombinedRate=0b11;

    while(I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Reg_Access.full_register)!=1);
    printf("somewhere\r\n");
    free_mag_ChangeMode(FREE_MAG_ACTIVEMODE);
    printf("Device Awakened\r\n");
    return;


}
//don't use until you've switched endedness

int free_mag_GetXData(void) {
    int XData;
    XData = I2C_ReadInt(I2C_ADDRESS, OUT_X_MSB);
    return XData;

}

int free_mag_GetYData(void) {
    int YData;
    YData = I2C_ReadInt(I2C_ADDRESS, OUT_Y_MSB);
    return YData;

}

int free_mag_GetZData(void) {
    int ZData;
    ZData = I2C_ReadInt(I2C_ADDRESS, OUT_Z_MSB);
    return ZData;

}

void free_mag_GetTriplet(short *AxisData) {
    unsigned char RegContents[6];

    char iterate;
    I2C_ReadMultiple(I2C_ADDRESS, OUT_X_MSB, RegContents, 6);
    Data_Access.full_data = 0;
    Data_Access.msb = 0xDE;
    Data_Access.lsb = 0xAD;
    //printf("acceleration: %X\r\n", Data_Access.accelation_data.acceleration);
    //printf("full short: %X\r\n", Data_Access.full_data);

    for (iterate = 0; iterate < 6; iterate += 2) {
        Data_Access.lsb = RegContents[iterate];
        Data_Access.msb = RegContents[iterate + 1];
        AxisData[iterate >> 1] = Data_Access.full_data;
    }
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




}

//

void free_mag_ChangeMode(char Mode) {

    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    Reg_Access.CtrlReg_1.operating_mode = Mode;
    I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Reg_Access.full_register);
    //printf("somewhere else\r\n");

}
//

unsigned char free_mag_SetRate(char Rate) {
    int i;
    free_mag_ChangeMode(FREE_MAG_STANDBYMODE);
    DELAY();
    DELAY();
    DELAY();
    DELAY();
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);
    //Reg_Access.CtrlReg_1.Rate = (scale & RATE_MASK);
    //Reg_Access.CtrlReg_1.oversample = (scale & OVER_MASK);
    Reg_Access.CtrlReg_1.CombinedRate = Rate;
    //printf("scale: %X\tFull Register: %X\r\n", Rate, Reg_Access.full_register);
    //while (1);
    I2C_WriteReg(I2C_ADDRESS, CTRL_REG1, Reg_Access.full_register);
    Reg_Access.full_register=I2C_ReadReg(I2C_ADDRESS,CTRL_REG1);
    //printf("scale: %X\tFull Register: %X\r\n", Rate, Reg_Access.full_register);
    free_mag_ChangeMode(FREE_MAG_ACTIVEMODE);
    return 0;
}
//

unsigned char free_mag_GetRate() {
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CTRL_REG1);

    return Reg_Access.CtrlReg_1.CombinedRate;
}