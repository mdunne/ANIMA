



#include <p32xxxx.h>
#include "stdio.h"
#include "gps.h"
#include <serial.h>

#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000

int main(void) {

    //unsigned char size = 0, i;
    INTEnableSystemMultiVectoredInt();
    SERIAL_Init();
    printf("Sizeof GPS Data: %d",sizeof(gpsControlData));
    GPS_Init();

    //UART2PutChar('a');
    printf("Uno32 GPS test\r\n\r\n");
    
    //char test_sentence[]="$GPGGA,191734.000,3700.0240,N,12203.8165,W,1,10,0.82,267.1,M,-26.6,M,,*5B\r\n";
    //parseGGA(test_sentence);
    //while(1);
    //while (1)
    while (1) {
        //if (UART2HalfEmpty()){
        if (gpsControlData.newDatatoParse == 1) {
            //printf("New Data to parse\r\n");
            processNewGpsData();
            if (gpsControlData.newData == 1) {
                printf("time: %02d:%02d:%02d", gpsControlData.hour, gpsControlData.min, gpsControlData.sec);
                printf(" Lat: %.4f: Lon: %.4f", gpsControlData.lat, gpsControlData.lon);
                printf(" Height: %.4f hdop: %d fix: %d sats: %d", gpsControlData.height, gpsControlData.hdop, gpsControlData.fix, gpsControlData.sats);
                printf("  milliseconds: %d",gpsControlData.millisec);
                printf("\r\n");
                gpsControlData.newData = 0;
            }
        }
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }
}







