


#include "LED.h"



#include <xc.h>
#include "stdio.h"
#include "gps.h"
#include "BOARD.h"
#include "timers.h"
#include <serial.h>


#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF


#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000

int main(void) {

    //unsigned char size = 0, i;
    BOARD_Init();
    printf("Sizeof GPS Data: %d\r\n",sizeof(gpsControlData));
    GPS_Init();
    LED_Init(LED_BANK1);
    TIMERS_Init();

    //UART2PutChar('a');
    printf("Uno32 GPS test\r\n\r\n");


    //char test_sentence[]="$GPGGA,191734.000,3700.0240,N,12203.8165,W,1,10,0.82,267.1,M,-26.6,M,,*5B\r\n";
    //parseGGA(test_sentence);
    //while(1);
    //while (1)
    char toggle=TRUE;
    InitTimer(0,500);
    while (1) {
        //if (UART2HalfEmpty()){
        if (gpsControlData.newDatatoParse == 1) {
            //printf("New Data to parse\r\n");
            processNewGpsData();
            if (gpsControlData.newData == 1) {
                printf("time: %02d:%02d:%02d.%03d", gpsControlData.hour, gpsControlData.min, gpsControlData.sec,gpsControlData.millisec);
                printf(" Lat: %.4f: Lon: %.4f", gpsControlData.lat, gpsControlData.lon);
                printf(" Height: %.4f hdop: %d fix: %d sats: %d", gpsControlData.height, gpsControlData.hdop, gpsControlData.fix, gpsControlData.sats);
                //printf("  milliseconds: %d",gpsControlData.millisec);
                LED_SetBank(LED_BANK1,~(gpsControlData.fix+1));
                printf("\r\n");
                gpsControlData.newData = 0;
            }
        }
        if(IsTimerExpired(0))
        {
            if(toggle)
            {
                LED_SetBank(LED_BANK1,~0);
            }
            else
            {
                LED_SetBank(LED_BANK1,~(gpsControlData.fix+1));
            }
            InitTimer(0,500);
        }
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }
}






