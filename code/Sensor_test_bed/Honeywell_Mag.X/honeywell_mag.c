#include <p32xxxx.h>
#include <serial.h>
#include "stdio.h"


#include "honeywell_mag.h"
#include <I2C_Driver.h>

#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define GAIN_MASK 0b11100000
#define RATE_MASK 0b00111000
#define MODE_MASK 0x01

typedef enum {
    CONFIG_REG_A = 0x0,
    CONFIG_REG_B,
    MODE_REG,
    OUT_X_MSB,
    OUT_X_LSB,
    OUT_Z_MSB,
    OUT_Z_LSB,
    OUT_Y_MSB,
    OUT_Y_LSB,
    STATUS_REG,
    IDENT_REG_A,
    IDENT_REG_B,
    IDENT_REG_C
} REGISTERS;

#define I2C_ADDRESS 0x1E


//bit fields are reversed from what makes sense
union Reg_Access {
    struct
    {
        unsigned : 5;
        unsigned int Gain : 3;
        
    }Gain_Reg;
    struct
    {
        unsigned Mode : 2;
        unsigned :6;
    }Mode_Reg;
    struct
    {
        unsigned : 2;
        unsigned Rate : 3;
        unsigned : 3;
    }Rate_Reg;
    unsigned char full_register;
} Reg_Access;

void honey_mag_init(void) {
    char response = 0;
    //TRISBbits.TRISB9 = 0;
    //TRISBbits.TRISB8 = 0;

    I2C_Init(100000);
    //printf("Awakening Device\r\n");
    honey_mag_ChangeMode(HONEY_CONTINUOUS_MODE);
    //I2C_WriteReg(I2C_ADDRESS,MODE_REG,0);
    //response=I2C_ReadReg(I2C_ADDRESS,CTRL_REG1);
    //printf("Control Reg: %X\r\n",response);
    //while(1);
    //honey_mag_ChangeMode(honey_mag_ACTIVEMODE);
   // printf("Device Awakened\r\n");
    return;


}

int honey_mag_GetXData(void) {
    int XData;
    XData = I2C_ReadInt(I2C_ADDRESS, OUT_X_MSB);
    return XData;

}

int honey_mag_GetYData(void) {
    int YData;
    YData = I2C_ReadInt(I2C_ADDRESS, OUT_Y_MSB);
    return YData;

}

int honey_mag_GetZData(void) {
    int ZData;
    ZData = I2C_ReadInt(I2C_ADDRESS, OUT_Z_MSB);
    return ZData;

}




//



unsigned char honey_mag_GetGain() {
    
    unsigned char Gain;

/*    for (Scale=0; Scale<=7;Scale++)
    {
        Reg_Access.Gain_Reg.Gain=Scale;
        printf("Gain:%X \tReg:%X\r\n",Scale,Reg_Access.full_register);
    }*/
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS,CONFIG_REG_B);
    Gain=Reg_Access.Gain_Reg.Gain;
    //printf("regist: %X\r\n",regist);
    return Gain;
}

unsigned char honey_mag_SetGain(char newGain) {
    
        char regist, fun = CONFIG_REG_B;
        //honey_mag_ChangeMode(honey_mag_STANDBYMODE);
        Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS,CONFIG_REG_B);
        Reg_Access.Gain_Reg.Gain=newGain;
        I2C_WriteReg(I2C_ADDRESS,CONFIG_REG_B,Reg_Access.full_register);
        //honey_mag_ChangeMode(honey_mag_ACTIVEMODE);
        return 0;
     
}

//

void honey_mag_ChangeMode(char Mode) {
    
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS,MODE_REG);
    switch(Mode)
    {
        case HONEY_CONTINUOUS_MODE:
            Reg_Access.Mode_Reg.Mode=0;
            I2C_WriteReg(I2C_ADDRESS,MODE_REG,Reg_Access.full_register);
            break;
        case HONEY_SINGLE_MEASUREMENT_MODE:
            Reg_Access.Mode_Reg.Mode=1;
            I2C_WriteReg(I2C_ADDRESS,MODE_REG,Reg_Access.full_register);
            break;
        case HONEY_IDLE_MODE:
            Reg_Access.Mode_Reg.Mode=2;
            I2C_WriteReg(I2C_ADDRESS,MODE_REG,Reg_Access.full_register);
            break;         
    }
}
//

unsigned char honey_mag_SetRate(char Rate) {
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CONFIG_REG_A);
    Reg_Access.Rate_Reg.Rate=Rate;
    I2C_WriteReg(I2C_ADDRESS,CONFIG_REG_A,Reg_Access.full_register);
    /*
    char regist;
    honey_mag_ChangeMode(honey_mag_STANDBYMODE);
    regist = honey_mag_ReadReg(CTRL_REG1);
    regist &= (~RATE_MASK);
    regist = regist + (Rate << 2);
    /*
    if (scale==honey_mag_2GSCALE)
            regist=(regist&(~SCALE_MASK))+0;
    if (scale==honey_mag_4GSCALE)
            regist=(regist&(~SCALE_MASK))+1;
    if (scale==honey_mag_8GSCALE)
            regist=(regist&(~SCALE_MASK))+2;
     
    honey_mag_WriteReg(CTRL_REG1, regist);
    honey_mag_ChangeMode(honey_mag_ACTIVEMODE);
      */
    return 0;
     
}
//

unsigned char honey_mag_GetRate() {
    unsigned char Rate, regist;
    Rate = 255;
    Reg_Access.full_register=0;
    //    for (Rate=0; Rate<=7;Rate++)
    //{
      //  Reg_Access.Rate_Reg.Rate=Rate;
        //printf("Gain:%X \tReg:%X\r\n",Rate,Reg_Access.full_register);
    //}
    Reg_Access.full_register = I2C_ReadReg(I2C_ADDRESS, CONFIG_REG_A);
    Rate=Reg_Access.Rate_Reg.Rate;
    //regist &= RATE_MASK;
    //Rate = regist >> 2;
    //printf("regist: %X\r\n",regist);
    /*if (regist==0)
            Scale=honey_mag_2GSCALE;
    if (regist==1)
            Scale=honey_mag_4GSCALE;
    if (regist==2)
            Scale=honey_mag_8GSCALE;
     */
    return Rate;
}



//ALL FUNCTIONS BEYOND THIS POINT ARE UN-IMPLEMENTED