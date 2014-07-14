#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "BOARD.h"
#include "timers.h"
#include "serial.h"
#include "DataEncoding.h"
#include "Data_Logging.h"
#include <peripheral/dma.h>

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN = OFF
#pragma config OSCIOFNC = OFF

//#define CRC_PROOF_OF_CONCEPT

void main(void) {
    BOARD_Init();


    printf("Welcome to the Data Encoding Test\r\n");
#ifdef CRC_PROOF_OF_CONCEPT

    TIMERS_Init();
    unsigned int iterator;
    unsigned int starttime, duration;
    unsigned int DataSize = 512;
    unsigned char Data[DataSize];
    unsigned int crc1 = 0, crc2;
    int DMAChannel = 2;
    DmaTxferRes res;

    for (iterator = 0; iterator < DataSize; iterator++) {
        Data[iterator] = iterator;
    }
    Data[511] = 46;
    //    printf("Hi Bob\r\n");
    //    while (1);
    DmaChnConfigure(DMAChannel, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
    DmaSfmConfigure(DMA_CHKSUM_CRC, DMA_BITO_MSb, DMA_REORDER_NOT);
    DmaSfmCrcConfigure(0x8005, 12, 0xffff);
    starttime = GetTime();
    res = DmaChnMemCrc(&crc1, Data, DataSize - 1, DMAChannel, DMA_CHN_PRI3);
    duration = GetTime() - starttime;
    printf("DMA Transfer Results: %d\r\n", res);
    printf("CRC calculated: %X\r\n", crc1);
    //printf("Time taken: %d\r\n",duration);
    //DmaChnSetTxfer(DMAChannel,Data,&crc1,DataSize);
    //DmaChnEnable(DMAChannel);

#endif
#define ENTRIESTOTEST 300
    DataEncoding_Init();
    DataLogging_Init();
    unsigned int DataSize = 113;
    unsigned char TestArray[DataSize];
    unsigned int TestEntry;
    unsigned int iterator = 0;

    for (TestEntry = 0; TestEntry < ENTRIESTOTEST; TestEntry++) {
        for (iterator = 0; iterator < DataSize; iterator++) {
            TestArray[iterator] = iterator + TestEntry;
        }
        DataEncoding_SubmitData(TestArray);
        while(!DataLogging_Log());
    }
    printf("test Complete\r\n");
    while (1);

    //------------------------------------------------------------------

}
