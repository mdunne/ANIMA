


#include <Data_Logging.h>
#include "FSIO.h"
#include <xc.h>
#include <stdio.h>
#include "SD-SPI.h"
#include "timers.h"
#include "serial.h"
//#include "LED.h"
#include <inttypes.h>


MEDIA_INFORMATION *mediaInformation;



#define DEBUG_MESSAGE
#define DEBUG_VERBOSE

#define SECTORS_USED_FOR_DIRECTORY 5

#define BYTES_USED_FOR_DIRECTORY (SECTORS_USED_FOR_DIRECTORY*MEDIA_SECTOR_SIZE)

#define ADDRESS_SIZE_IN_BYTES 3
#define ADDRESS_SIZE_IN_BITS ((ADDRESS_SIZE_IN_BYTES)*8)/2
//so need to divide by two for some reason
#define HEADER_SIZE_IN_BYTES 8
#define ENTRY_SIZE_IN_BYTES 8
//this is currently hardcoded to be 1 less as header is that size
#define ENTRIES_IN_DIRECTORY (((BYTES_USED_FOR_DIRECTORY)/(ENTRY_SIZE_IN_BYTES))-1)
#define MAX_ENTRY (ENTRIES_IN_DIRECTORY-1)
#define CARD_IDENTITY 0xDEAD
#define CHUNK_IN_SECTORS 1024
//#define DATA_SIZE (MEDIA_SECTOR_SIZE - 2)

typedef union {
    unsigned char Sector_Access[MEDIA_SECTOR_SIZE];

    struct {
        unsigned short ID;
        unsigned char Data[DATA_SIZE];
    };
} t_Sector;


static int CurSectorCount;
static int CurSector;
static int SectorforCurrentEntry;
static int CurDirectorySize;
static short curFileID;
static short IsWriteActive;

static FSFILE * FilePointer;

#define FILEPATTERN "*.bin"

//private function prototypes
char DataLogging_ReadDirectory(void);
char DataLogging_WriteDirectory(void);
void WipeCard(void);
char DataLogging_UpdateEntryAddress(void);

char DataLogging_Init() {
    //while (!MDD_MediaDetect());
    //while (!FSInit());
    //printf("Dir_Entry: %d\r\n ", sizeof (Dir_Entry));
    int ByteCount, SectorCount;
    SearchRec rec;
    unsigned char filenum = 1;
    char filename[7];
    unsigned char filecount = 0;
    unsigned char led_state = 0;
    char toggle = TRUE;
    SectorCount = 0;

    //    Directory.Card_Identifier = 0xDEAD;
    //    Directory.Last_Entry_Used = 0xFEFEED;
    //    Directory.Entries[10].ID = 0xFED;
    //    for (ByteCount = 0; ByteCount < ENTRIES_IN_DIRECTORY; ByteCount++) {
    //        Directory.Entries[ByteCount].ID = ByteCount+(ByteCount<<9);
    //        Directory.Entries[ByteCount].Start_Address=0;
    //        Directory.Entries[ByteCount].Stop_Address=0;
    //    }
    //    //Directory.Entries[ENTRIES_IN_DIRECTORY-1].Stop_Address=0xDEA;
    //    for (SectorCount = 0; SectorCount < SECTORS_USED_FOR_DIRECTORY; SectorCount++) {
    //        for (ByteCount = 0; ByteCount < MEDIA_SECTOR_SIZE; ByteCount++) {
    //            printf("%d\t", Directory.Sector_Access[SectorCount][ByteCount]);
    //            while (!IsTransmitEmpty());
    //        }
    //    }

    //printf("total entries: %d",ENTRIES_IN_DIRECTORY);
    //printf("sizeof(Dir_Entry):%d",sizeof(char));
    //printf("in function above pin declares\r\n");
    TRISAbits.TRISA1 = 0;
    //    PORTSetPinsDigitalOut(IOPORT_A, BIT_1);
    PPSInput(3, SDI2, RPC6);
    PPSOutput(2, RPC8, SDO2);
    TRISCbits.TRISC8 = 0;
    LATAbits.LATA1 = 0;
    PORTSetPinsDigitalIn(IOPORT_B, BIT_4);

    //printf("socsen: %X\r\n", OSCCONbits.SOSCEN);
    //InitTimer(0,500);
    //while(1);
    //LED_SetBank(LED_BANK1, ~3);
    //    printf("in function above below\r\n");
    //    InitTimer(0, 2000);
    //    while (IsTimerActive(0));
    //while (1);
    //    while (1) {
    //        if (IsTransmitEmpty()) {
    //            printf("%d\r\n", MDD_MediaDetect());
    //
    //        }
    //        if (IsTimerExpired(0)) {
    //            if (toggle) {
    //                LED_SetBank(LED_BANK1, ~0);
    //                toggle = FALSE;
    //            } else {
    //                LED_SetBank(LED_BANK1, ~(MDD_MediaDetect()+1));
    //                toggle = TRUE;
    //            }
    //            InitTimer(0, 500);
    //        }
    //    }
    while (!MDD_MediaDetect());
    //    while (1);
    MDD_SDSPI_InitIO();
    int count = 0;
    mediaInformation = MDD_MediaInitialize();
    if (mediaInformation->errorCode != 0) {
        printf("Media not initialized with error code: %d\r\n", mediaInformation->errorCode);
        while (1);
    }
    if (!FSInit()) {
        printf("File System Initializaion Failed");
        while (1);
    }
    //We now need to find the new file name
    char Searchresult;
    //search for the first file matching filepattern
    Searchresult = FindFirst(FILEPATTERN, ATTR_MASK, &rec);
#ifdef DEBUG_MESSAGE
    printf("%d\r\n", Searchresult);
#endif
    if (Searchresult == -1) {
        //we have no logs created so we can create the first one
#ifdef DEBUG_MESSAGE
        printf("No Logs Found, First Created\r\n");
#endif
        filecount = 0;

        //FSfwrite("aaa",1,3,FilePointer);
        //FSfclose(FilePointer);
    } else {
        //we find the largest log and increment by one
#ifdef DEBUG_VERBOSE
        printf("Logs Found iterating to largest\r\n");

#endif
        while (Searchresult != -1) {
            filenum = atoi(rec.filename);
            if (filenum >= filecount) {
                filecount = filenum + 1;
            }
#ifdef DEBUG_MESSAGE
            printf("%d\t%s\r\n", filenum, rec.filename);
#endif
            Searchresult = FindNext(&rec);
        }
    }
    curFileID = filecount;
#ifdef DEBUG_MESSAGE
    sprintf(filename, "%03d.bin", filecount);
#endif
    FilePointer = FSfopen(filename, "w");
    //we extract the first sector of the file
    CurSectorCount = Cluster2Sector(FilePointer->dsk, FilePointer->cluster) + FilePointer->sec;
#ifdef DEBUG_VERBOSE
    printf("First Sector of File is: %d\r\n", CurSector);
    while (!IsTransmitEmpty());
#endif
    //while(1);
    int curtime = GetTime();
    FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
#ifdef DEBUG_VERBOSE

    printf("Time to allocate %d was %d milliseconds\r\n", CHUNK_IN_SECTORS, GetTime() - curtime);
#endif
    //while (1);

}

char DataLogging_LoadSector(unsigned char *AddresstoWrite) {
    static unsigned int ChunkCount = 0;
    unsigned char SPI_Status = FALSE;

    //due to the polling nature the chunking is handled before the write setup
    //    ChunkCount++;
    //    if (ChunkCount >= CHUNK_IN_SECTORS) {
    //#ifdef DEBUG_VERBOSE
    //        printf("Card allocated more sectors\r\n");
    //#endif
    //        //int curtime = GetTime();
    //        FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
    //#ifdef DEBUG_VERBOSE
    //        printf("Time to allocate %d was %d milliseconds\r\n", CHUNK_IN_SECTORS, GetTime() - curtime);
    //#endif
    //
    //        ChunkCount = 0;
    //    }

    if(IsWriteActive)
    {
        printf("Error: Next sector Write occured before last one was complete\r\n");
    }
    //set up the write
    SPI_Status = MDD_SDSPI_SectorSetupWrite(CurSectorCount, AddresstoWrite, TRUE);
    IsWriteActive = TRUE;

    //call the first sector write to start the process
    //SPI_Status = MDD_SDSPI_SectorWritePoll();
    //    if (SPI_Status == FALSE) {
    //#ifdef DEBUG_MESSAGE
    //        printf("Card failed to write at one point\r\n");
    //#endif
    //        while (MDD_SDSPI_MediaInitialize() != MEDIA_NO_ERROR);
    //    }


}
//we assume that this is 512 in size
//intermediary state where it uses the pointer instead of copying the array over
//eventually this function will lose its arguments and simply communicate with the sd card as need

char DataLogging_Log() {
    static unsigned int ChunkCount = 0;
    //uint8_t inSector[DATA_SIZE];
    if (IsWriteActive) {
        unsigned char SPI_Status = FALSE;
        //DataLogging_LoadSector(AddressToWrite);
        int ByteCount = 0;
        //    while (MDD_SDSPI_GetTransactionStatus() != ASYNC_WRITE_COMPLETE) {
        //printf("/");
        SPI_Status = MDD_SDSPI_SectorWritePoll();
        if (SPI_Status == FALSE) {
#ifdef DEBUG_MESSAGE
            printf("Card failed to write at one point\r\n");
#endif
            while (MDD_SDSPI_MediaInitialize() != MEDIA_NO_ERROR);
        }
        //    }
        if (MDD_SDSPI_GetTransactionStatus() == ASYNC_WRITE_COMPLETE) {
            CurSectorCount++;
            ChunkCount++;
            //printf("%d\r\n", ChunkCount);

            if (ChunkCount >= CHUNK_IN_SECTORS) {
#ifdef DEBUG_VERBOSE
                printf("Card allocated more sectors,card is currently at %d sectors and according to file system %d\r\n",CurSectorCount,FilePointer->size);
#endif
                int curtime = GetTime();
                FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
#ifdef DEBUG_VERBOSE
               // printf("Time to allocate %d was %d milliseconds\r\n", CHUNK_IN_SECTORS, GetTime() - curtime);
#endif
                //            printf("%d\t%d\r\n",ChunkCount,CurSectorCount);
                //        InitTimer(0,1000);
                //        while(IsTimerActive(0));
                ChunkCount = 0;
            }
            //printf("ChunkCount: %d\tCurSectorCount: %d\r\n",ChunkCount,CurSectorCount);
            IsWriteActive = FALSE;
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return TRUE;
    }
}

char DataLogging_CloseLog(void) {
    FSfclose(FilePointer);
}







//utility function to retrieve the file object point
//not used in normal usage

FSFILE * DataLogging_GetFilePointer(void) {
    return FilePointer;
}


//utility function to retrieve the current sector address
//not used in normal usage

DWORD DataLogging_GetSectorAddress(void) {
    return CurSectorCount;
}