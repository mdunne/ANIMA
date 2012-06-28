
#include <p32xxxx.h>
#include <serial.h>
#include "stdio.h"
#include <I2C_Driver.h>

#include "st_compass.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00011000
#define RATE_MASK  0b11110000
#define MODE_MASK  0b00000111

typedef enum {
    WHO_AM_I = 0x0F,
    CTRL_REG1_A = 0x20,
    CTRL_REG2_A,
    CTRL_REG3_A,
    CTRL_REG4_A,
    CTRL_REG5_A,
    CTRL_REG6_A,
    REFERENCE_A,
    STATUS_REG_A,
    OUT_X_L_A,
    OUT_X_H_A,
    OUT_Y_L_A,
    OUT_Y_H_A,
    OUT_Z_L_A,
    OUT_Z_H_A,
    FIFO_CTRL_REG_A,
    FIFO_SRC_REG_A,
    INT1_CFG_A,
    INT1_SOURCE_A,
    INT1_THS_A,
    INT1_DURATION_A,
    INT2_CFG_A,
    INT2_SOURCE_A,
    INT2_THS_A,
    INT2_DURATION_A,
    CLICK_CFG_A,
    CLICK_SRC_A,
    CLICK_THIS_A,
    TIME_LIMIT_A,
    TIME_LATENCY_A,
    TIME_WINDOW_A,
    CRA_REG_M = 0x0,
    CRB_REG_M,
    MR_REG_M,
    OUT_X_L_M,
    OUT_X_H_M,
    OUT_Z_L_M,
    OUT_Z_H_M,
    OUT_Y_L_M,
    OUT_Y_H_M,
    SR_REG_MG,
    IRA_REG_M,
    IRB_REG_M,
    TEMP_OUT_H_M = 0x31,
    TEMP_OUT_L_M

} registers;





union swapU {
    struct field
    {
        unsigned char top;
        unsigned char bottom;
    }f;
    short w;
} swapU;


//bit fields in the struct start at the lsb
union Reg_Access {
    struct
    {
        unsigned : 5;
        unsigned int Gain : 3;

    }ConReg_B;
    struct
    {
        unsigned Mode : 2;
        unsigned :6;
    }Mode_Reg;
    struct
    {

        unsigned : 2;
        unsigned Rate : 3;
        unsigned : 2;
        unsigned Temp_Enable : 1;
    }ConReg_A;
    struct
    {
        unsigned SIM : 1;
        unsigned : 2;
        unsigned Scale : 2;
        unsigned Endedness : 1;
        unsigned Block_Update : 1;
    }CTRL_REG4_A;
    struct
    {
        unsigned XEnable : 1;
        unsigned YEnable : 1;
        unsigned ZEnable : 1;
        unsigned LowPower : 1;
        unsigned Rate : 4;
    }CTRL_REG1_A;
    unsigned char full_register;
} Reg_Access;


#define ACCEL_I2C_ADDRESS 0x19
#define MAG_I2C_ADDRESS 0x1E
#define swap(x,y) x^=y; y^=x; x^=y

short switch_endedness(short format_num);

void st_compass_init(void) {
    //char response = 0;
    I2C_Init(100000);

    //while(1);
    printf("Awakening Device\r\n");
    //I2C_WriteReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A,0b00010000);
    //st_ChangeMode(STMICRO_ACTIVEMODE);
    //printf("Control reg: %X",I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A));
    short testval=0xDEAD;
    //printf("The value: %X and its switched counterpart %X",(short)testval,(short)switch_endedness(testval));
    //I2C_WriteReg(MAG_I2C_ADDRESS,CRA_REG_M,0b00011100);
    //I2C_WriteReg(MAG_I2C_ADDRESS,MR_REG_M,0);
    st_mag_ChangeMode(ST_MAG_CONTINUOUS_MODE);
    printf("Device Awakened\r\n");
    return;


}

short switch_endedness(short format_num){
    swapU.w=format_num;
    swap(swapU.f.bottom,swapU.f.top);
    return swapU.w;

}

int st_Get_AccelXData(void) {
    int XData;
    XData = switch_endedness(I2C_ReadInt(ACCEL_I2C_ADDRESS,OUT_X_L_A));
    //XData = st_ReadInt(OUT_X_L_A);
    return XData;

}

int st_Get_AccelYData(void) {
    int YData;
    YData = switch_endedness(I2C_ReadInt(ACCEL_I2C_ADDRESS, OUT_Y_L_A));
    return YData;

}

int st_Get_AccelZData(void) {
    int ZData;
    ZData = switch_endedness(I2C_ReadInt(ACCEL_I2C_ADDRESS, OUT_Z_L_A));
    return ZData;

}

int st_Get_MagXData(void) {
    int XData;
    XData = I2C_ReadInt(MAG_I2C_ADDRESS, OUT_X_H_M);
    return XData;

}

int st_Get_MagYData(void) {
    int YData;
    YData = I2C_ReadInt(MAG_I2C_ADDRESS, OUT_Y_H_M);
    return YData;

}

int st_Get_MagZData(void) {
    int ZData;
    ZData = I2C_ReadInt(MAG_I2C_ADDRESS, OUT_Z_H_M);
    return ZData;

}



unsigned char st_mag_GetGain() {

    unsigned char Gain;

/*    for (Scale=0; Scale<=7;Scale++)
    {
        Reg_Access.Gain_Reg.Gain=Scale;
        printf("Gain:%X \tReg:%X\r\n",Scale,Reg_Access.full_register);
    }*/
    Reg_Access.full_register = I2C_ReadReg(MAG_I2C_ADDRESS,CRB_REG_M);
    Gain=Reg_Access.ConReg_B.Gain;
    //printf("regist: %X\r\n",regist);
    return Gain;
}

unsigned char st_mag_SetGain(char newGain) {

        char regist, fun = CRB_REG_M;
        //st_mag_ChangeMode(st_mag_STANDBYMODE);
        Reg_Access.full_register = I2C_ReadReg(MAG_I2C_ADDRESS,CRB_REG_M);
        Reg_Access.ConReg_B.Gain=newGain;
        I2C_WriteReg(MAG_I2C_ADDRESS,CRB_REG_M,Reg_Access.full_register);
        //st_mag_ChangeMode(st_mag_ACTIVEMODE);
        return 0;

}

//

void st_mag_ChangeMode(char Mode) {

    Reg_Access.full_register = I2C_ReadReg(MAG_I2C_ADDRESS,MR_REG_M);
    switch(Mode)
    {
        case ST_MAG_CONTINUOUS_MODE:
            Reg_Access.Mode_Reg.Mode=0;
            I2C_WriteReg(MAG_I2C_ADDRESS,MR_REG_M,Reg_Access.full_register);
            break;
        case ST_MAG_SINGLE_MEASUREMENT_MODE:
            Reg_Access.Mode_Reg.Mode=1;
            I2C_WriteReg(MAG_I2C_ADDRESS,MR_REG_M,Reg_Access.full_register);
            break;
        case ST_MAG_IDLE_MODE:
            Reg_Access.Mode_Reg.Mode=2;
            I2C_WriteReg(MAG_I2C_ADDRESS,MR_REG_M,Reg_Access.full_register);
            break;
    }
}
//

unsigned char st_mag_SetRate(char Rate) {
    Reg_Access.full_register = I2C_ReadReg(MAG_I2C_ADDRESS, CRA_REG_M);
    Reg_Access.ConReg_A.Rate=Rate;
    I2C_WriteReg(MAG_I2C_ADDRESS,CRA_REG_M,Reg_Access.full_register);

    return 0;

}
//

unsigned char st_mag_GetRate() {
    unsigned char Rate, regist;
    Rate = 255;
    Reg_Access.full_register=0;
    //    for (Rate=0; Rate<=7;Rate++)
    //{
      //  Reg_Access.Rate_Reg.Rate=Rate;
        //printf("Gain:%X \tReg:%X\r\n",Rate,Reg_Access.full_register);
    //}
    Reg_Access.full_register = I2C_ReadReg(MAG_I2C_ADDRESS, CRA_REG_M);
    Rate=Reg_Access.ConReg_A.Rate;
    //regist &= RATE_MASK;
    //Rate = regist >> 2;
    //printf("regist: %X\r\n",regist);
    /*if (regist==0)
            Scale=st_mag_2GSCALE;
    if (regist==1)
            Scale=st_mag_4GSCALE;
    if (regist==2)
            Scale=st_mag_8GSCALE;
     */
    return Rate;
}


//


//

unsigned char st_accel_GetScale() {

    unsigned char Scale;
    Reg_Access.full_register=I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG4_A);
    Scale=Reg_Access.CTRL_REG4_A.Scale;
    return Scale;
}

/**
 *
 * @param scale
 * @return
 */
unsigned char st_accel_SetScale(char scale) {
    Reg_Access.full_register=I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG4_A);
    Reg_Access.CTRL_REG4_A.Scale=scale;
    Reg_Access.CTRL_REG4_A.Block_Update=1;
    I2C_WriteReg(ACCEL_I2C_ADDRESS,CTRL_REG4_A,Reg_Access.full_register);
//    char regToRead;
//    st_ChangeMode(STMICRO_STANDBYMODE);
//    regToRead = st_ReadReg(CTRL_REG4_A);
//    if (scale == STMICRO_2GSCALE)
//        regToRead = (regToRead & (~SCALE_MASK))+(0b00 << 4);
//    if (scale == STMICRO_4GSCALE)
//        regToRead = (regToRead & (~SCALE_MASK))+(0b01 << 4);
//    if (scale == STMICRO_8GSCALE)
//        regToRead = (regToRead & (~SCALE_MASK))+(0b11 << 4);
//    st_WriteReg(CTRL_REG4_A, regToRead);
//    st_ChangeMode(STMICRO_ACTIVEMODE);
    return 0;
}

//

/** 
 * changes the mode for the device
 * @param Mode
 * #define for mode type: Currently only Active and Standby
 */
void st_accel_ChangeMode(char Mode) {
//    char Cur_Mode = 0;
//    Cur_Mode = st_ReadReg(CTRL_REG1_A);
//    Cur_Mode &= (~MODE_MASK); //remove current mode
//    if (Mode == STMICRO_STANDBYMODE) {
//        st_WriteReg(CTRL_REG1_A, Cur_Mode);
//    }
//    if (Mode == STMICRO_ACTIVEMODE) {
//        Cur_Mode |= MODE_MASK;
//        st_WriteReg(CTRL_REG1_A, Cur_Mode);
//    }
}
//
//note that the rate is also how you turn it off or on
unsigned char st_accel_SetRate(char Rate) {
    char regist;
    Reg_Access.full_register=I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A);
    Reg_Access.CTRL_REG1_A.Rate=Rate;
    //printf("status of axis: %d%d%d\r\n",Reg_Access.CTRL_REG1_A.XEnable,Reg_Access.CTRL_REG1_A.YEnable,Reg_Access.CTRL_REG1_A.ZEnable);
    I2C_WriteReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A,Reg_Access.full_register);
    //regist=I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A);
    //printf("Regist: %X\r\n",regist);
    return 0;

}
//

unsigned char st_accel_GetRate() {
    unsigned char Rate;
    Reg_Access.full_register=I2C_ReadReg(ACCEL_I2C_ADDRESS,CTRL_REG1_A);
    Rate=Reg_Access.CTRL_REG1_A.Rate;
    return Rate;
}