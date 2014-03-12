
#include <xc.h>
#include "FSIO.h"
#include <serial.h>
#include "Data_Logging.h"
#include "timers.h"
#include "BOARD.h"
#include "LED.h"
#include <peripheral/dma.h>

char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN = OFF
#pragma config OSCIOFNC = OFF

#ifdef __32MX320F128H__
#warning hi all
#endif

union d_test {

    struct {
        unsigned short entry_one;
        unsigned short entry_two;
        unsigned short entry_three;
    };
    unsigned char multi_d [2][3];
} d_test;

//#define SECTORS_TO_WRITE

int main(void) {
#if defined(SUPPORT_LFN)
    char count = 80;
#endif
    char * pointer2;
    SearchRec rec;
    unsigned char attributes;
    unsigned char size = 0, i;
    int count, curtime, totaltimes;
    BOARD_Init();
    // Turn on the interrupts
    //INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    printf("Starting the Data Logging Test compiled at %s on %s\r\n", __TIME__, __DATE__);
    //printf("DMA max Size: %d\r\n",DmaGetMaxTxferSize());
    //while(1);
    TIMERS_Init();
    LED_Init(LED_BANK1);
    //LED_SetBank(LED_BANK1,0);
    InitTimer(0, 2000);

    while (IsTimerActive(0));

    //while(1);


    //while (!MDD_MediaDetect());
    //printf("Media Detected\r\n");
    //    FSInit();
    //    printf("File system Initialized\r\n");
    //    //while(1);
    //        char teststring[]="hello world";
    //        //pointer = FSfopen ("hmm.txt", "w");
    //        printf("File Opened\r\n");
    //    //FSfwrite(teststring,1,11,pointer);
    //    printf("File Written to\r\n");
    //    //FSfclose(pointer);
    //    printf("file_closed\r\n");
    //    attributes = ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;
    //    FindFirst("*.txt",attributes,&rec);
    //    printf("FileName is %s\r\n",rec.filename);
    //    while(1);

    //printf("%X\t%X\t%X\r\n",d_test.entry_one,d_test.entry_two,d_test.entry_three);
    //while(1);
    //SYSTEMConfigPerformance(GetSystemClock());
    //mOSCSetPBDIV(OSC_PB_DIV_2);
    //Initialize the RTCC
    //RtccInit();
    //while(RtccGetClkStat()!=RTCC_CLK_ON);// wait for the SOSC to be actually running and RTCC to have its clock source
    // could wait here at most 32ms
    //RtccOpen(0x10073000, 0x07011602, 0);
    //printf("supposedly I'm running this code now")

    // Create a file

    DataLogging_Init();
    count = GetTime();
    printf("Data logging inited\r\n");
    //while(1);
    //DataLogging_PrintDirectory();
    //printf("Total Entries: %d\r\n",DataLogging_NumEntries());
    //printf("Size of entry %d is: %d\r\n",DataLogging_NumEntries()/2,DataLogging_GetEntrySize(DataLogging_NumEntries()/2));

    //while(1);
    unsigned char test_array[510];
    unsigned char test_char;
    for (count = 0; count < 510; count++) {
        test_char = count/2;
        test_array[count] = test_char;
    }
    test_array[0] = 30;
    printf("Starting to write a lot of data\r\n");
    for (count = 0; count < 30000; count++) {
        printf(".");
        DataLogging_Log(test_array);

    }
    printf("Test Complete\r\n");
    while (1);
    //DataLogging_PrintDirectory();

    // char teststring[]="hello world";

    //FSfwrite(teststring,1,11,pointer);
    //printf("Write 21 1-byte objects from sendBuffer into the file: FAILED\r\n");
    //while (1);
    //printf("File being closed\r\n");
    //DataLogging_CloseLog();
    //DataLogging_DumpInterface();
    //printf("It took %d milliseconds to perform operations",GetTime()-count);
}