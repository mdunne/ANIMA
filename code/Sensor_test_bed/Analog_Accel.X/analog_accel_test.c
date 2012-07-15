



#include <p32xxxx.h>
#include "stdio.h"
#include <serial.h>
#include "analog_accel.h"




int main(void) {

    //unsigned char size = 0, i;

    SERIAL_Init();
    INTEnableSystemMultiVectoredInt();

    
    //UART2PutChar('a');
    printf("sUno32 analog Accelerometer test\r\nAfter confirming settings reading will be taken\r\n");
    analog_accel_init();


    //while(1);

    //printf("Scale is set to %d \r\n",analog_GetScale());
    //analog_SetScale(analog_3GSCALE);
    //while(1);

    //printf("Scale is set to %d and should be %d\r\n", analog_GetScale(), analog_3GSCALE);
    //analog_SetScale(analog_2GSCALE);
    //printf("Scale is set to %d and should be %d\r\n", analog_GetScale(), analog_2GSCALE);


    printf("Rate is set to %d \r\n", analog_GetRate());

    //analog_SetRate(analog_300HERTZ);
    printf("Rate is set to %d and should be %d\r\n", analog_GetRate(), analog_300HERTZ);
    /*
    analog_SetRate(analog_800HERTZ);
    printf("Rate is set to %d and should be %d\r\n",analog_GetRate(),analog_800HERTZ);
     */
    char humanread = 1;
    int maxX = analog_GetXData(), maxY = analog_GetYData(), maxZ = analog_GetZData();
    int minX = maxX, minY = maxY, minZ = maxZ;
    int curval=0;
    int i, j, data;
    /*for(i=0; i!=-1; i++)
            for(j=0; j!=100; j++)
                    Nop();
    printf("Scale is set to %d and should be %d\r\n",analog_GetScale(),analog_3GSCALE);*/
    for (i = 0; i != 1000; i++)
        for (j = 0; j != 100; j++)
            Nop();

    while (1) {
        if (IsTransmitEmpty()){
        if (humanread == 1) {
            printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n", analog_GetXData(), analog_GetYData(), analog_GetZData());
            //printf("combined z: %D\t\t",analog_GetZData());
        } else {
            printf("max X: %d \tmax Y: %d \tmax Z: %d \tmin X: %d \tmin Y: %d min Z: %d\r\n", maxX, maxY, maxZ, minX, minY, minZ);
            curval = analog_GetXData();
            if (curval < minX) {
                minX = curval;
            }
            if (curval > maxX) {
                maxX = curval;
            }
            curval = analog_GetYData();
            if (curval < minY) {
                minY = curval;
            }
            if (curval > maxY) {
                maxY = curval;
            }
            curval = analog_GetZData();
            if (curval < minZ) {
                minZ = curval;
            }
            if (curval > maxZ) {
                maxZ = curval;
            }
        }
        }
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }

}








