



#include <xc.h>
#include "stdio.h"
#include "serial.h"
#include "freescale_accel.h"
#include "BOARD.h"
#include "timers.h"
#include "LED.h"

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF
//#pragma config ICESEL = ICS_PGx3

int main(void) {

    //unsigned char size = 0, i;

    BOARD_Init();

    printf("Anima Small Scale FreeScale Accelerometer test\r\n");
    TIMERS_Init();
    LED_Init(LED_BANK1);
    int count=0;
//    while (1) {
//        if (!IsTimerActive(0)) {
//            // LATCbits.LATC5 ^= 1;
//            //LATBbits.LATB9 ^= 1;
//            InitTimer(0, 500);
//            printf("TOP: %X\r\n", count);
//            LED_SetBank(LED_BANK1, count);
//            count++;
//
//        }
//    }
//
//    while (1);
    free_accel_init();
    printf("Scale is set to %d \r\n", free_GetScale());
    free_SetScale(FREE_8GSCALE);
    printf("Scale is set to %d and should be %d\r\n", free_GetScale(), FREE_4GSCALE);
    free_SetScale(FREE_2GSCALE);
    printf("Scale is set to %d and should be %d\r\n", free_GetScale(), FREE_2GSCALE);
    printf("Rate is set to %d \r\n", free_GetRate());
    free_SetRate(FREE_200HERTZ);
    printf("Rate is set to %d and should be %d\r\n", free_GetRate(), FREE_200HERTZ);
    free_SetRate(FREE_800HERTZ);
    printf("Rate is set to %d and should be %d\r\n", free_GetRate(), FREE_800HERTZ);
    //free_SetRate(FREE_1P56HERTZ);
    //while(1);
    char humanread = 1;
    short dataArray[3];
    int i, j, data;
    for (i = 0; i != 1000; i++)
        for (j = 0; j != 500; j++)
            Nop();

    while (1) {
        //if (UART2HalfEmpty()){
        if (humanread == 1) {
            if (IsTransmitEmpty()) {
                free_GetTriplet(dataArray);
                printf("Accel: Cur X: %d \tCur Y: %d \tCur Z: %d\r\n", dataArray[0], dataArray[1], dataArray[2]);
            }
        } else {
            data = free_GetXData();
            //UART2PutChar('$');
            //UART2PutChar('#');
            // UART2PutChar(data >> 8);
            // UART2PutChar(data & 0x00FF);

            //UART2PutChar('\r');
            //UART2PutChar('\n');

        }
        //for (i = 0; i != -1; i++)
        //  Nop();
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }

}








