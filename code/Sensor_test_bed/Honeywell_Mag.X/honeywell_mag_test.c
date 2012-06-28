



#include <p32xxxx.h>
#include "stdio.h"
#include <serial.h>
#include "honeywell_mag.h"
#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 150000
//#include <LED.h>
int main(void) {

    //unsigned char size = 0, i;



    SERIAL_Init();
    INTEnableSystemMultiVectoredInt();
    printf("Uno32 Honeywell Magnetometer test\r\nAll input should be mirrored back to you\r\n");
    //printf("Size of short:%d\r\n",sizeof(short));
    //printf("Size of char:%d\r\n",sizeof(char));
    //printf("Size of int:%d\r\n",sizeof(int));
    //while(1);
    honey_mag_init();
    printf("Scale is set to %d \r\n",honey_mag_GetGain());
    honey_mag_SetGain(HONEY_GAIN_440);
    printf("Scale is set to %d and should be %d\r\n",honey_mag_GetGain(),HONEY_GAIN_440);
    honey_mag_SetGain(HONEY_GAIN_820);
    printf("Scale is set to %d and should be %d\r\n",honey_mag_GetGain(),HONEY_GAIN_820);
    printf("Rate is set to %d \r\n",honey_mag_GetRate());
    honey_mag_SetRate(HONEY_RATE_3HERTZ);
    printf("Rate is set to %d and should be %d\r\n",honey_mag_GetRate(),HONEY_RATE_3HERTZ);
    honey_mag_SetRate(HONEY_RATE_30HERTZ);
    printf("Rate is set to %d and should be %d\r\n",honey_mag_GetRate(),HONEY_RATE_30HERTZ);
    //while(1);
    char humanread = 1;
    int i, j, data;
    //for (i = 0; i != 1600; i++)
      //for (j = 0; j != 100; j++)
        //Nop();
    DELAY();

    while (1) {
        //if (UART2HalfEmpty()){
        //printf("%d",IsTransmitEmpty());
        //DELAY();
        if (humanread == 1) {
            if (IsTransmitEmpty())
                //printf("In Here at Least\r\n");
                printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n", honey_mag_GetXData(), honey_mag_GetYData(), honey_mag_GetZData());
            DELAY();
            DELAY();
            DELAY();
            DELAY();
            DELAY();
        } else {
            //data=honey_mag_GetXData();
            //UART2PutChar('$');
            //UART2PutChar('#');
            //UART2PutChar(data >> 8);
            //UART2PutChar(data & 0x00FF);

            //UART2PutChar('\r');
            //UART2PutChar('\n');

        }
        //for (i = 0; i != -1; i++)
        //Nop();
        //}
        /*while(!UART2IsEmpty())
                UART2PutChar(UART2GetChar());*/
    }

}








