



#include <p32xxxx.h>
#include "stdio.h"
#include <serial.h>
#include "st_compass.h"
#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000
int main(void) {

    //unsigned char size = 0, i;
    SERIAL_Init();
    INTEnableSystemMultiVectoredInt();
    //UART2PutChar('a');
    printf("Uno32 ST Micro Compass test\r\n\r\n");
    st_compass_init();
    //printf("Current Mode Settings: %X\r\n",st_ReadReg(0x10));
    //while(1);

    printf("Mag Scale is set to %d \r\n",st_mag_GetGain());
    st_mag_SetGain(ST_MAG_GAIN_450);
    printf("Mag Scale is set to %d and should be %d\r\n",st_mag_GetGain(),ST_MAG_GAIN_450);
    st_mag_SetGain(ST_MAG_GAIN_855);
    printf("Mag Scale is set to %d and should be %d\r\n",st_mag_GetGain(),ST_MAG_GAIN_855);
    printf("Mag Rate is set to %d \r\n",st_mag_GetRate());
    st_mag_SetRate(ST_MAG_RATE_3HERTZ);
    printf("Mag Rate is set to %d and should be %d\r\n",st_mag_GetRate(),ST_MAG_RATE_3HERTZ);
    st_mag_SetRate(ST_MAG_RATE_30HERTZ);
    printf("Mag Rate is set to %d and should be %d\r\n",st_mag_GetRate(),ST_MAG_RATE_30HERTZ);

    printf("Accel Scale is set to %d \r\n", st_accel_GetScale());

    st_accel_SetScale(ST_ACCEL_16GSCALE);
    printf("Accel Scale is set to %d and should be %d\r\n", st_accel_GetScale(), ST_ACCEL_16GSCALE);
    st_accel_SetScale(ST_ACCEL_2GSCALE);
    printf("Accel Scale is set to %d and should be %d\r\n", st_accel_GetScale(), ST_ACCEL_2GSCALE);
    
    printf("Accel Rate is set to %d \r\n", st_accel_GetRate());
    
    st_accel_SetRate(ST_ACCEL_400HERTZ);
    printf("Accel Rate is set to %d and should be %d\r\n", st_accel_GetRate(), ST_ACCEL_400HERTZ);
    st_accel_SetRate(ST_ACCEL_50HERTZ);
    printf("Accel Rate is set to %d and should be %d\r\n", st_accel_GetRate(), ST_ACCEL_50HERTZ);
    st_accel_SetRate(ST_ACCEL_10HERTZ);
    //while(1);
    //printf("Current Mode Settings: %X\r\n",st_ReadReg(0x10));
    char humanread = 1;
    int maxX = st_Get_AccelXData(), maxY = st_Get_AccelYData(), maxZ = st_Get_AccelZData();
    int minX = maxX, minY = maxY, minZ = maxZ;
    short AxisData[3];
    int curval = 0;
    int i, j, data;
    //while(1);
    while (1) {
        //if (UART2HalfEmpty()){
        if (humanread == 1) {
            if (IsTransmitEmpty())
                //printf("hmm\t");
                st_GetAccelTriplet(AxisData);
                printf("Accel ");
                printf("X: %05d \tY: %05d \tZ: %05d",st_Get_AccelXData(), st_Get_AccelYData(), st_Get_AccelZData());

                st_GetMagTriplet(AxisData);
                printf("\tMag ");
                //printf("X: %5d \tY: %5d \tZ: %5d\r\n", st_Get_MagXData()-AxisData[0],st_Get_MagYData()-AxisData[1] , st_Get_MagZData()-AxisData[2]);
                printf("X: %5d \tY: %5d \tZ: %5d\r\n",AxisData[0],AxisData[1] ,AxisData[2]);
            DELAY();
        } else {
            printf("max X: %d \tmax Y: %d \tmax Z: %d \tmin X: %d \tmin Y: %d min Z: %d\r\n", maxX, maxY, maxZ, minX, minY, minZ);
            curval = st_Get_AccelXData();
            if (curval < minX) {
                minX = curval;
            }
            if (curval > maxX) {
                maxX = curval;
            }
            curval = st_Get_AccelYData();
            if (curval < minY) {
                minY = curval;
            }
            if (curval > maxY) {
                maxY = curval;
            }
            curval = st_Get_AccelZData();
            if (curval < minZ) {
                minZ = curval;
            }
            if (curval > maxZ) {
                maxZ = curval;
            }
        }
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }

}








