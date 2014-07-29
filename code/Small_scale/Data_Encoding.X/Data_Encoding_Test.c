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
//#define CRC_CALC_VERIFICATION


#ifdef CRC_PROOF_OF_CONCEPT

void main(void) {
    BOARD_Init();


    printf("Welcome to the Data Encoding Test\r\n");
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

#elif  defined(CRC_CALC_VERIFICATION)
#define POLYNOMIAL 0xD8

uint8_t crcNaive(uint8_t message);

void main(void) {
    BOARD_Init();

    //    PutChar(27);
    //    PutChar(0x5b);
    //    PutChar('2');
    //    PutChar('J');
    printf("Welcome to the Data Encoding Test\r\n");
    unsigned char iterator;
    unsigned int starttime, duration;
    unsigned int DataSize = 20;
    unsigned char Data[DataSize + 2];
    unsigned int crc1 = 0, crc2;
    int DMAChannel = 2;
    DmaTxferRes res;
    printf("0x");
    Data[0] = 0xA3;
    Data[1] = 0xD2;
    Data[2] = 0x0;
    Data[3] = 0x0;
    for (iterator = 0; iterator < DataSize; iterator++) {
        Data[iterator] = 49 + iterator + 36;
        printf("%02X", Data[iterator]);
    }
    //    for (iterator; iterator < DataSize+2; iterator++) {
    //        Data[iterator] = 0;
    //        printf("%02X", Data[iterator]);
    //    }

    printf("\r\n");
    //    for (iterator = 0; iterator < DataSize; iterator++) {
    //
    //        printf("%c", Data[iterator]);
    //    }
    // Data[511] = 46;
    //    printf("Hi Bob\r\n");
    //    while (1);
    DmaChnConfigure(DMAChannel, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
    DmaSfmConfigure(DMA_CHKSUM_CRC, DMA_BITO_MSb, DMA_REORDER_NOT);
    DmaSfmCrcConfigure(0x8005, 16, 0xffff);
    starttime = GetTime();
    res = DmaChnMemCrc(&crc1, Data, DataSize, DMAChannel, DMA_CHN_PRI3);
    duration = GetTime() - starttime;
    printf("DMA Transfer Results: %d\r\n", res);
    printf("CRC calculated: %X\r\n", crc1);
    printf("CRC from naive is : %X\r\n", crcNaive(Data[0]));

    while (1);
    printf("starting to calculate them all in form DMA tab naive");
    for (iterator = 0; iterator < 255; iterator++) {

        DmaChnConfigure(DMAChannel, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
        DmaSfmConfigure(DMA_CHKSUM_CRC, DMA_BITO_MSb, DMA_REORDER_NOT);
        DmaSfmCrcConfigure(0x1101, 4, 0xEAA8);
        Data[0] = iterator;
        res = DmaChnMemCrc(&crc1, &iterator, 1, DMAChannel, DMA_CHN_PRI3);
        printf("%d\t", iterator);
        printf("%d\t", crc1);
        printf("%d", crcNaive(iterator));
        printf("\r\n");
        while (!IsTransmitEmpty());
    }
    //printf("Time taken: %d\r\n",duration);
    //DmaChnSetTxfer(DMAChannel,Data,&crc1,DataSize);
    //DmaChnEnable(DMAChannel);
}

uint8_t crcNaive(uint8_t message) {
    uint8_t remainder;
    uint8_t bit;

    /*
     * Initially, the dividend is the remainder.
     */
    remainder = message;

    /*
     * For each bit position in the message....
     */
    for (bit = 8; bit > 0; --bit) {
        /*
         * If the uppermost bit is a 1...
         */
        if (remainder & 0x80) {
            /*
             * XOR the previous remainder with the divisor.
             */
            remainder ^= POLYNOMIAL;

        }
        //printf("%X\r\n", remainder);
        /*
         * Shift the next bit of the message into the remainder.
         */
        remainder = (remainder << 1);
    }

    /*
     * Return only the relevant bits of the remainder as CRC.
     */
    return (remainder >> 4);

} /* crcNaive() */


#else
#define ENTRIESTOTEST 3000

void main(void) {
    BOARD_Init();
    printf("\r\nWelcome to Data Encoding Test\r\n");
    DataEncoding_Init();
    DataLogging_Init();
    //printf("%d",RAND_MAX);
    //while(1);
    unsigned int DataSize = 343;
    unsigned char TestArray[DataSize];
    srand(343);
    unsigned int TestEntry;
    unsigned int iterator = 0;
    
    for (TestEntry = 0; TestEntry < ENTRIESTOTEST; TestEntry++) {
        for (iterator = 0; iterator < DataSize; iterator++) {
            //printf("%d ",rand()>>24);
            TestArray[iterator] = rand();
        }
        DataEncoding_SubmitData(TestArray);
        while (!DataLogging_Log());
    }
    printf("test Complete\r\n");
    while (1);
}
#endif
    //------------------------------------------------------------------


