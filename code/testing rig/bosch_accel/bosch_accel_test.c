



#include "p33FJ64MC802.h"
#include "stdio.h"
#include "uart2.h"
#include "bosch_accel.h"


_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);

int main(void) {

    //unsigned char size = 0, i;

    PLLFBD = 150;
    CLKDIVbits.PLLPOST = 0;
    CLKDIVbits.PLLPRE = 5;
    __builtin_write_OSCCONH(0b001);
    __builtin_write_OSCCONL(0b01);
    while (OSCCONbits.COSC != 0b001); // Wait for Clock switch to occur
    while (OSCCONbits.LOCK != 1) {
    };


    UART2Init();
    LATBbits.LATB15 = 1; // set latch levels
    TRISBbits.TRISB15 = 0; // set IO as outputs
    //UART2PutChar('a');

    printf("Microstick Bosch Accelerometer test\r\nAfter confirming settings reading will be taken\r\n");
    bosch_accel_init();
    //printf("mode Register: %X\r\n",bosch_ReadReg(0x35));


    //while(1);

    //printf("Scale is set to %d \r\n",bosch_GetScale());
    bosch_SetScale(BOSCH_3GSCALE);
    //while(1);

    printf("Scale is set to %d and should be %d\r\n", bosch_GetScale(), BOSCH_3GSCALE);
    //bosch_SetScale(BOSCH_2GSCALE);
    printf("Scale is set to %d and should be %d\r\n", bosch_GetScale(), BOSCH_2GSCALE);


    printf("Rate is set to %d \r\n", bosch_GetRate());

    bosch_SetRate(BOSCH_300HERTZ);
    printf("Rate is set to %d and should be %d\r\n", bosch_GetRate(), BOSCH_300HERTZ);
    /*
    bosch_SetRate(BOSCH_800HERTZ);
    printf("Rate is set to %d and should be %d\r\n",bosch_GetRate(),BOSCH_800HERTZ);
     */
    char humanread = 1;
    int maxX = bosch_GetXData(), maxY = bosch_GetYData(), maxZ = bosch_GetZData();
    int minX = maxX, minY = maxY, minZ = maxZ;
    int curval=0;
    int i, j, data;
    /*for(i=0; i!=-1; i++)
            for(j=0; j!=100; j++)
                    Nop();
    printf("Scale is set to %d and should be %d\r\n",bosch_GetScale(),BOSCH_3GSCALE);*/
    for (i = 0; i != -1; i++)
        for (j = 0; j != 100; j++)
            Nop();

    while (1) {
        //if (UART2HalfEmpty()){
        if (humanread == 1) {
            printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n", bosch_GetXData(), bosch_GetYData(), bosch_GetZData());
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
        for (i = 0; i != -1; i++)
            Nop();
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }

}








