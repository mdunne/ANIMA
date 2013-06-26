
#include <xc.h>
#include "FSIO.h"
#include <serial.h>
#include "Data_Logging.h"
#include "timers.h"


char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

#if defined (__PIC32MX__)
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_2         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = ON            // Background Debugger Enable
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
    SERIAL_Init();
    // Turn on the interrupts
    //INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    INTEnableSystemMultiVectoredInt();
    TIMERS_Init();
    printf("Starting the Data Logging Test compiled at %s on %s\r\n", __TIME__, __DATE__);
    int count,curtime,totaltimes;

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
    count = GetTime();
    DataLogging_Init();
    printf("Data logging inited\r\n");
    //while(1);
    //DataLogging_PrintDirectory();
    //printf("Total Entries: %d\r\n",DataLogging_NumEntries());
    //printf("Size of entry %d is: %d\r\n",DataLogging_NumEntries()/2,DataLogging_GetEntrySize(DataLogging_NumEntries()/2));

    //while(1);
    unsigned char test_array[510];
    unsigned char test_char;
    for (count = 0; count < 510; count++) {
        test_char = count;
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