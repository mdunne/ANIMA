#include <xc.h>

#include "serial.h"
#include "DataEncoding.h"
#include "Data_Logging.h"
#include <peripheral/dma.h>

#include <inttypes.h>

//#define DEBUG_MESSAGE
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

//this should really reference a different define from logging
#define SECTORSIZE 512
#define DATASIZE (SECTORSIZE-8)

#define HEADERVALUE 0xFB3B
#define FOOTERVALUE 0x5F86

#define CRCPOLYNOMIAL 0x8005
#define CRCWIDTH 16
#define CRCSEED 0xffff

#define USEDDMACHANNEL DMA_CHANNEL2

#define NUMENTRIES 2

/*******************************************************************************
 * PRIVATE VARIABLE TYPES
 ******************************************************************************/
typedef struct DataEntry_t {
    uint16_t Header;
    uint16_t TimeStamp;
    uint8_t Data[DATASIZE];
    uint16_t Checksum;
    uint16_t Footer;
} DataEntry_t;

typedef union Sector_t {
    DataEntry_t DataAccess;
    unsigned char SectorAccess[SECTORSIZE];
} Sector_t;


/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

static Sector_t DataEntries[NUMENTRIES];
static uint8_t CurEntry = 0;
static uint16_t CurByte = 0;

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/

uint16_t CalcCRC(uint8_t Array[]);
void IncrementEntry();
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function Sampler_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  sets up the timers to their default rates and handles any onetime initialization of sensors
 * @note  None.
 * @author Max Dunne */
unsigned char DataEncoding_Init(void) {
    uint16_t iterator = 0;

    //we set the defaults for all of the entries
    for (iterator = 0; iterator < NUMENTRIES; iterator++) {
        DataEntries[iterator].DataAccess.Header = HEADERVALUE;
        DataEntries[iterator].DataAccess.Footer = FOOTERVALUE;
    }
    //    printf("size: %d",sizeof(DataEntry_t));
    //    while(1);

    CurEntry = 0;
    CurByte = 0;
#ifndef DATAENCODING_TEST
    DataEntries[CurEntry].DataAccess.TimeStamp = Sampler_GetSecondCount(); //this needs to be set from the sampler timer for now will be sector count
#else
    DataEntries[CurEntry].DataAccess.TimeStamp = 0;
#endif
    return SUCCESS;
}

//we assume that the data is valid
//we then determine if we pass a sector boundary with the new data
//if not we can simply perform a memcpy and be done
//if so we need to perform to memory copies and then perform further processing on the now completed sector

unsigned char DataEncoding_SubmitDataHelper(void *DataPointer, unsigned int IncomingDataSize) {
    unsigned int iterator = 0;
    uint16_t curDataSize = 0;
    //unsigned char *CharCastPointer = DataPointer;
#ifdef DEBUG_MESSAGE
    printf("Incoming data is %d bytes in size and currently at %d\r\n", IncomingDataSize, CurByte);
    for (iterator = 0; iterator < IncomingDataSize; iterator++) {
        printf("%02X\t", *((char *) (DataPointer + iterator)));
    }
    printf("\r\n");
    while (!IsTransmitEmpty());
#endif
    if ((CurByte + IncomingDataSize) <= DATASIZE) {
        memcpy(&DataEntries[CurEntry].DataAccess.Data[CurByte], DataPointer, IncomingDataSize);
        CurByte += IncomingDataSize;
    } else {
        //need to split the transfer into two parts
        //first half will fill the rest of the sector
        //after that crc is calculated and can be sent to the data logger
        curDataSize = DATASIZE - CurByte;
        memcpy(&DataEntries[CurEntry].DataAccess.Data[CurByte], DataPointer, curDataSize);
#ifdef DEBUG_MESSAGE
        printf("First part is %d in size and second is %d\r\n", curDataSize, IncomingDataSize - curDataSize);
        while (!IsTransmitEmpty());
#endif
        DataEntries[CurEntry].DataAccess.Checksum = CalcCRC(DataEntries[CurEntry].DataAccess.Data);
#ifdef DEBUG_MESSAGE
        printf("Checksum calculated is: %X\r\n", DataEntries[CurEntry].DataAccess.Checksum);
        while (!IsTransmitEmpty());


        printf("Current entry is %d and new one is ", CurEntry);
        while (!IsTransmitEmpty());
#endif
        //we then pass the array index along to logging at this point
//        printf("First Sector written\r\n");
//        for (iterator = 0; iterator < IncomingDataSize; iterator++) {
//            printf("%02X ", *((char *) (DataEntries[CurEntry].SectorAccess + iterator)));
//            while(!IsTransmitEmpty());
//        }
        //while(1);
        DataLogging_LoadSector(DataEntries[CurEntry].SectorAccess);

        IncrementEntry();
#ifdef DEBUG_MESSAGE
        printf("%d\r\n", CurEntry);
        while (!IsTransmitEmpty());
#endif
        // curDataSize=IncomingDataSize-curDataSize;  //calculate the chunk of memory left to copy
        //printf("%d ")
        memcpy(&DataEntries[CurEntry].DataAccess.Data[0], DataPointer + curDataSize, IncomingDataSize - curDataSize); //copy the second portion over
        CurByte = IncomingDataSize - curDataSize;
#ifdef DEBUG_MESSAGE
        printf("Processing Finished for second half\r\n");

        while (!IsTransmitEmpty());
#endif
#ifndef DATAENCODING_TEST
        DataEntries[CurEntry].DataAccess.TimeStamp = Sampler_GetSecondCount();
#else
        DataEntries[CurEntry].DataAccess.TimeStamp = 0;
#endif
    }

    //    for (iterator = 0; iterator < DATASIZE; iterator++) {
    //        printf("Data Value using CurByte: %d\r\n", DataEntries[CurEntry-1].DataAccess.Data[iterator]);
    //        while (!IsTransmitEmpty());
    //        //CharCastPointer++;
    //    }
    //    for (iterator = 0; iterator < (IncomingDataSize - curDataSize); iterator++) {
    //        printf("Data Value using CurByte: %d\r\n", DataEntries[CurEntry].DataAccess.Data[iterator]);
    //        //while (!IsTransmitEmpty());
    //    }

}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


//simply takes current entry and increments it to the next one
//however that is required

void IncrementEntry() {
    CurEntry++;
    if (CurEntry >= NUMENTRIES) {

        CurEntry = 0;
    }
}


//calculates the crc of the given array

uint16_t CalcCRC(uint8_t inArray[]) {
    uint16_t CRC;
    DmaTxferRes res;
    DmaChnConfigure(USEDDMACHANNEL, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
    DmaSfmConfigure(DMA_CHKSUM_CRC, DMA_BITO_MSb, DMA_REORDER_NOT);
    DmaSfmCrcConfigure(CRCPOLYNOMIAL, CRCWIDTH, CRCSEED);

    res = DmaChnMemCrc(&CRC, inArray, DATASIZE, USEDDMACHANNEL, DMA_CHN_PRI3);
    return CRC;
}