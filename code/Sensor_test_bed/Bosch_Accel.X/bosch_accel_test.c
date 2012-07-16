



#include <p32xxxx.h>
#include "serial.h"
#include "bosch_accel.h"
#include <timers.h>
#include <math.h>



int main(void) {

    //unsigned char size = 0, i;



    SERIAL_Init();
    //TIMERS_Init();
    //INTEnableSystemMultiVectoredInt();
    INTEnableSystemMultiVectoredInt();
    TIMERS_Init();
    //UART2PutChar('a');
    printf("sUno32 Bosch Accelerometer test on Laptop\r\nAfter confirming settings reading will be taken\r\n");
    bosch_accel_init();
    short AxisData[3];
    //bosch_GetTriplet(AxisData);
    //while(1);
    //printf("mode Register: %X\r\n",bosch_ReadReg(0x35));


    //while(1);

    printf("Scale is set to %d \r\n", bosch_GetScale());
    InitTimer(0, 20);
    while (IsTimerExpired(0)) {
        //printf("%d\r\n",GetTime());
    }
    bosch_SetScale(BOSCH_3GSCALE);
    //while(1);
    InitTimer(0, 200);
    while (IsTimerExpired(0));
    printf("Scale is set to %d and should be %d\r\n", bosch_GetScale(), BOSCH_3GSCALE);
    bosch_SetScale(BOSCH_2GSCALE);
    printf("Scale is set to %d and should be %d\r\n", bosch_GetScale(), BOSCH_2GSCALE);


    printf("Rate is set to %d \r\n", bosch_GetRate());
    InitTimer(0, 200);
    while (IsTimerExpired(0));
    bosch_SetRate(BOSCH_300HERTZ);
    printf("Rate is set to %d and should be %d\r\n", bosch_GetRate(), BOSCH_300HERTZ);
    bosch_SetInterrupt(BOSCH_NEW_DATA_INTERRUPT);
    /*
    bosch_SetRate(BOSCH_800HERTZ);
    printf("Rate is set to %d and should be %d\r\n",bosch_GetRate(),BOSCH_800HERTZ);
     */
    bosch_SetRate(BOSCH_10HERTZ);
    char humanread = 1;
    int maxX = bosch_GetXData(), maxY = bosch_GetYData(), maxZ = bosch_GetZData();
    int minX = maxX, minY = maxY, minZ = maxZ;
    int curval = 0;
    int i, j, data;
    InitTimer(0, 5000);
    while (!IsTimerExpired(0));
    //while(1);
    /*for(i=0; i!=-1; i++)
            for(j=0; j!=100; j++)
                    Nop();
    printf("Scale is set to %d and should be %d\r\n",bosch_GetScale(),BOSCH_3GSCALE);*/
    //for (i = 0; i != 1000; i++)
    //for (j = 0; j != 100; j++)
    //Nop();

    while (1) {
        if (IsTransmitEmpty()) {
            if (Bosch_IsNewDataReady()) {
                if (humanread == 1) {
                    bosch_GetTriplet(AxisData);
                    printf("Cur X: %d \tCur Y: %d \tCur Z: %d\tTotal: %d\r\n",AxisData[0],AxisData[1],AxisData[2],AxisData[0]*AxisData[0]+AxisData[1]*AxisData[1]+AxisData[2]*AxisData[2]);
                    //printf("Cur X: %d \tCur Y: %d \tCur Z: %d\tTotal: %d\r\n", bosch_GetXData(), bosch_GetYData(), bosch_GetZData(),bosch_GetXData()*bosch_GetXData()+bosch_GetYData()*bosch_GetYData()+bosch_GetZData()*bosch_GetZData());
                    //printf("combined z: %D\t\t",bosch_GetZData());
                } else {
                    printf("max X: %d \tmax Y: %d \tmax Z: %d \tmin X: %d \tmin Y: %d min Z: %d\r\n", maxX, maxY, maxZ, minX, minY, minZ);
                    curval = bosch_GetXData();
                    if (curval < minX) {
                        minX = curval;
                    }
                    if (curval > maxX) {
                        maxX = curval;
                    }
                    curval = bosch_GetYData();
                    if (curval < minY) {
                        minY = curval;
                    }
                    if (curval > maxY) {
                        maxY = curval;
                    }
                    curval = bosch_GetZData();
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

}








