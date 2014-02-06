



#include <xc.h>
#include "stdio.h"
#include <serial.h>
#include "freescale_mag.h"
#include "BOARD.h"
#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000
#include <LED.h>
#include <timers.h>

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF

int main(void) {

    //unsigned char size = 0, i;



    BOARD_Init();
    TIMERS_Init();
    printf("Uno32 FreeScale Magnetometer test\r\n");
    printf("Size of short:%d\r\n", sizeof (short));
    printf("Size of char:%d\r\n", sizeof (char));
    printf("Size of int:%d\r\n", sizeof (int));
    //while(1);
    free_mag_init();
    //printf("Scale is set to %d \r\n",free_mag_GetScale());
    //free_mag_SetScale(free_mag_4GSCALE);
    //printf("Scale is set to %d and should be %d\r\n",free_mag_GetScale(),free_mag_4GSCALE);
    //free_mag_SetScale(free_mag_2GSCALE);
    //printf("Scale is set to %d and should be %d\r\n",free_mag_GetScale(),free_mag_2GSCALE);
    printf("Rate is set to %d \r\n", free_mag_GetRate());
    //free_mag_SetRate(FREE_MAG_10HERTZ_16_OVERRATIO);
    printf("Rate is set to %d and should be %d\r\n", free_mag_GetRate(), FREE_MAG_0P08HERTZ_128_OVERRATIO);
    //InitTimer(0, 1000);
    //while (!IsTimerExpired(0));

    //free_mag_SetRate(FREE_MAG_40HERTZ_32_OVERRATIO);
    printf("Rate is set to %d and should be %d\r\n", free_mag_GetRate(), FREE_MAG_40HERTZ_32_OVERRATIO);
    //while (1);
    char humanread = 1;
    int i, j, data;
    //for (i = 0; i != 1600; i++)
    //for (j = 0; j != 100; j++)
    //Nop();
    DELAY();
    short AxisData[3];
    while (1) {
        //if (UART2HalfEmpty()){
        //printf("%d",IsTransmitEmpty());
        //DELAY();
        if (humanread == 1) {
            if (IsTransmitEmpty()) {
                //                printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n", free_mag_GetXData(), free_mag_GetYData(), free_mag_GetZData());
                free_mag_GetTriplet(AxisData);
                printf("Mag Cur X: %d \tCur Y: %d \tCur Z: %d\tTotal: %d\r\n", AxisData[0], AxisData[1], AxisData[2], AxisData[0] * AxisData[0] + AxisData[1] * AxisData[1] + AxisData[2] * AxisData[2]);
            }
        } else {
            //data=free_mag_GetXData();
            //UART2PutChar('$');
            //UART2PutChar('#');
            //UART2PutChar(data >> 8);
            //UART2PutChar(data & 0x00FF);
            //UART2PutChar('\r');
            //UART2PutChar('\n');

        }
    }

}








