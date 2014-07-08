
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

#define MODULE_TEST
//#define FILE_ALLOCATION_TEST

#ifdef MODULE_TEST

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
//    while(1);
    //DataLogging_PrintDirectory();
    //printf("Total Entries: %d\r\n",DataLogging_NumEntries());
    //printf("Size of entry %d is: %d\r\n",DataLogging_NumEntries()/2,DataLogging_GetEntrySize(DataLogging_NumEntries()/2));

    //while(1);
    unsigned char test_array[512];
    unsigned char test_char;
    for (count = 0; count < 512; count++) {
        test_char = count % 60;
        test_array[count] = test_char;
    }
    test_array[0] = 30;
    printf("Starting to write a lot of data\r\n");
    for (count = 0; count < 2048; count++) {
        printf(".");
        DataLogging_LoadSector(test_array);
        while(!DataLogging_Log(test_array));

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


#endif

#ifdef FILE_ALLOCATION_TEST


void Generate_Fibonacci_Array(unsigned char In_array[]);

#define LARGE_FILE_SIZE 3862016>>1
#define TEST_ARRAY_SIZE 512

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
    //    while(1);
    unsigned char test_array[TEST_ARRAY_SIZE];
    unsigned char test_char;
    unsigned char testString[] = " The Quick Brown Fox Jumped over the Lazy Dog.\r\n";
    unsigned char TestStringSize = sizeof (testString);
    for (count = 0; count < TEST_ARRAY_SIZE; count++) {
        test_array[count] = 1;
    }
    //    while (1) {
    //        Generate_Fibonacci_Array(test_array);
    //        // Generate_Fibonacci_Array(test_array);
    //        for (count = 0; count < 510; count++) {
    //            printf("%d\r\n", test_array[count]);
    //            InitTimer(0,100);
    //            while(IsTimerActive(0));
    //            while (!IsTransmitEmpty());
    //        }
    //
    //    }
    DataLogging_Init();
    count = GetTime();
    printf("%%Data logging File Allocation tests started\r\n");
    //while(1);
    //DataLogging_PrintDirectory();
    //printf("Total Entries: %d\r\n",DataLogging_NumEntries());
    //printf("Size of entry %d is: %d\r\n",DataLogging_NumEntries()/2,DataLogging_GetEntrySize(DataLogging_NumEntries()/2));

    //while(1);

    //test_array[0] = 30;
    FSFILE * FilePointer;
    int startTime = 0, endTime = 0;
    FilePointer = DataLogging_GetFilePointer();
    DWORD curSectorCount = DataLogging_GetSectorAddress();
    printf("cur sector count: %d\r\n", curSectorCount);
    //while(1);

    unsigned int SectorCount = LARGE_FILE_SIZE >> 0;
    unsigned int TotalFileSize = SectorCount * 512;
    unsigned int CurFileSize = 0;
    //    printf("the test string is %s with size %d", testString, TestStringSize);
    //    printf("%%Starting to write a file %dkilobytes in size\r\n", TotalFileSize >> 10);
    //while(1);
#define CHUNK_IN_SECTORS 1024
    startTime = GetTime();
    for (count = 0; count < SectorCount / CHUNK_IN_SECTORS; count++) {
        FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
    }
    endTime = GetTime();
    printf("Current File Size: %d\r\n", FilePointer->size >> 10);
    printf("With duration %d\r\n", endTime - startTime);
    //printf(".");
    //DataLogging_Log(test_array);

    //    printf("Starting to write a lot of data\r\n");
    //    for (count = 0; count < 300; count++) {
    //        printf(".");
    //        DataLogging_Log(test_array);
    //
    //    }
    //    }

    Generate_Fibonacci_Array(test_array);
    char Write_State = TRUE;
    printf("Starting to fill the file to verify allocation was successful\r\n");
    while (TotalFileSize > CurFileSize) {
        //printf("Writing\r\n");

        Write_State = MDD_SDSPI_SectorWrite(curSectorCount, test_array, TRUE);
        if (Write_State != TRUE) {
            printf("Sector failed to write at Sector %d\r\n", curSectorCount);
        }
        //DataLogging_Log(test_array);
        Generate_Fibonacci_Array(test_array);
        curSectorCount++;
        CurFileSize += 512;
        if (IsTransmitEmpty()) {
            printf("%04.4f%%\r", ((float) CurFileSize / (float) TotalFileSize)*100);
        }
    }
    //printf("Will update current filesize every megabyte\r\n");
    printf("\r\nTest Complete\r\n");
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

void Generate_Fibonacci_Array(unsigned char In_array[]) {
    static unsigned char counter = 43;
    int index;
    for (index = 0; index < TEST_ARRAY_SIZE; index++) {
        //        printf("%d   ",In_array[index]);
        if (index == 0) {
            In_array[index] = In_array[TEST_ARRAY_SIZE - 2] + In_array[TEST_ARRAY_SIZE - 1];
        } else if (index == 1) {
            In_array[index] = In_array[TEST_ARRAY_SIZE - 1] + In_array[index - 1];
        } else {
            In_array[index] = In_array[index - 1] + In_array[index - 2];
        }
        In_array[index] = counter;
        //printf("%d\r\n",In_array[index]);
        //while (!IsTransmitEmpty());
    }
    counter++;

}



#endif

