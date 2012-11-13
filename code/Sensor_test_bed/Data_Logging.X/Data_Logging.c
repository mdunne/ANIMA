


#include <Data_Logging.h>
#include "FSIO.h"
#include <xc.h>
#include <stdio.h>
#include <SD-SPI.h>
#include "timers.h"
#include "serial.h"


MEDIA_INFORMATION *mediaInformation;



//#define DEBUG_MESSAGE

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
#define CHUNK_IN_SECTORS 500
//#define DATA_SIZE (MEDIA_SECTOR_SIZE - 2)

typedef struct {
    unsigned short ID;
    unsigned Start_Address : ADDRESS_SIZE_IN_BITS;
    unsigned Stop_Address : ADDRESS_SIZE_IN_BITS;
} Dir_Entry;

static union Directory {
    unsigned char Sector_Access[SECTORS_USED_FOR_DIRECTORY][MEDIA_SECTOR_SIZE];

    struct {
        unsigned short Card_Identifier;
        unsigned int Last_Entry_Used;
        Dir_Entry Entries[ENTRIES_IN_DIRECTORY];
    };
} Directory;

typedef union {
    unsigned char Sector_Access[MEDIA_SECTOR_SIZE];

    struct {
        unsigned short ID;
        unsigned char Data[DATA_SIZE];
    };
} t_Sector;


static int CurSectorCount;
static int SectorforCurrentEntry;
static int CurDirectorySize;
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

    t_Sector curSector;
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
    while (!MDD_MediaDetect());
    //while (1);
    MDD_SDSPI_InitIO();
    int count = 0;
    mediaInformation = MDD_MediaInitialize();
    if (mediaInformation->errorCode != 0) {
        printf("Media not initialized with error code: %d\r\n", mediaInformation->errorCode);
        while (1);
    }
    //DataLogging_ReadDirectory();
    MDD_SDSPI_SectorRead(0, curSector.Sector_Access);
    //check for ID
    if (curSector.ID != CARD_IDENTITY) {
#ifdef DEBUG_MESSAGE
        printf("Card not formatted\r\n");
#endif
        Directory.Card_Identifier = CARD_IDENTITY;
        Directory.Last_Entry_Used = 0;
        Directory.Entries[0].ID = 0;
        Directory.Entries[0].Start_Address = SECTORS_USED_FOR_DIRECTORY;
        Directory.Entries[0].Stop_Address = Directory.Entries[0].Start_Address + CHUNK_IN_SECTORS;

    } else {
        DataLogging_ReadDirectory();
        MDD_SDSPI_SectorRead(Directory.Entries[Directory.Last_Entry_Used].Start_Address, curSector.Sector_Access);
        if (curSector.ID == Directory.Last_Entry_Used) {
#ifdef DEBUG_MESSAGE
            printf("Card Formatted and data written, directory updated\r\n");
#endif
            //we have written to this directory at least once so we assume it has been used

            //so we increment the last_entry_used and add 1 to the stop address of the old entry
            //as we update the directory when we start to use the new chunk
            Directory.Last_Entry_Used++;
            Directory.Entries[Directory.Last_Entry_Used].ID = Directory.Last_Entry_Used;
            Directory.Entries[Directory.Last_Entry_Used].Start_Address = Directory.Entries[Directory.Last_Entry_Used - 1].Stop_Address + 1;
            Directory.Entries[Directory.Last_Entry_Used].Stop_Address = Directory.Entries[Directory.Last_Entry_Used].Start_Address + CHUNK_IN_SECTORS;
            CurDirectorySize = CHUNK_IN_SECTORS;
        } else {
            //we assume that data was never written to this directory so we can use it again
            //we merely enforce the size constraint and change nothing else
#ifdef DEBUG_MESSAGE
            printf("Card Formatted But No New Data Has Been Written\r\n No Changes made to the table\r\n");
#endif
            Directory.Entries[Directory.Last_Entry_Used].Stop_Address = Directory.Entries[Directory.Last_Entry_Used].Start_Address + CHUNK_IN_SECTORS;
        }
    }

    //we now set the CurSectorCount for writing to the log and write the directory back to the card
    CurSectorCount = Directory.Entries[Directory.Last_Entry_Used].Start_Address;
    curSector.ID = Directory.Last_Entry_Used;
    //MDD_SDSPI_SectorWrite(Directory.Entries[Directory.Last_Entry_Used].Start_Address,curSector.Sector_Access,TRUE);
    DataLogging_WriteDirectory();
    //need to determine what sector of the directory the current ID is held
    //we know the size of the entries and the header so we need to simply multiply and then divide by 512
    SectorforCurrentEntry = (HEADER_SIZE_IN_BYTES + (ADDRESS_SIZE_IN_BYTES + ADDRESS_SIZE_IN_BYTES + sizeof (short))*8) / 512;
    printf("Sector for Current: %d\r\n", SectorforCurrentEntry);
    //while (1);
#ifdef DEBUG_MESSAGE
    printf("Data logging Initialized\r\n");
    printf("Directory Structure\r\n");
    DataLogging_PrintDirectory();
#endif
    //DataLogging_PrintDirectory();
    return 0;
}


//we assume that this is 510 in size

char DataLogging_Log(unsigned char *Sector_block) {
    static unsigned char ChunkCount = 0;
    t_Sector inSector;
    unsigned char SPI_Status = FALSE;
    int ByteCount = 0;
    //inSector.Sector_Access=Sector_block;
    //this is copying the data currently as my head is blanking on the proper pointer math
    //fix this soon please
    for (ByteCount = 0; ByteCount < DATA_SIZE; ByteCount++) {
        inSector.Data[ByteCount] = Sector_block[ByteCount];
    }
    inSector.ID = Directory.Entries[Directory.Last_Entry_Used].ID;
    //printf("ID value: %d",inSector.ID);
    while (SPI_Status == FALSE) {
        SPI_Status = MDD_SDSPI_SectorWrite(CurSectorCount, inSector.Sector_Access, TRUE);
        if (SPI_Status == FALSE) {
#ifdef DEBUG_MESSAGE
            printf("Card failed to write at one point\r\n");
#endif
            while (MDD_SDSPI_MediaInitialize() != MEDIA_NO_ERROR);

        }
    }

    CurSectorCount++;
    ChunkCount++;
    if (ChunkCount >= CHUNK_IN_SECTORS) {

        Directory.Entries[Directory.Last_Entry_Used].Stop_Address += CHUNK_IN_SECTORS;
        CurDirectorySize = CurDirectorySize + CHUNK_IN_SECTORS;
        if (Directory.Entries[Directory.Last_Entry_Used].Stop_Address < Directory.Entries[Directory.Last_Entry_Used].Start_Address) {
            Directory.Entries[Directory.Last_Entry_Used].Stop_Address = CurDirectorySize;
        }
        //printf("%d\r\n",Directory.Entries[Directory.Last_Entry_Used].Stop_Address);
        //DataLogging_WriteDirectory();
        DataLogging_UpdateEntryAddress();
        ChunkCount = 0;
    }
    //printf("ChunkCount: %d\tCurSectorCount: %d\r\n",ChunkCount,CurSectorCount);
    while (!IsTransmitEmpty());
}

char DataLogging_CloseLog(void) {
    //FSfclose(pointer);
}

char DataLogging_ReadDirectory(void) {
    int SectorCount = 0;
    for (SectorCount = 0; SectorCount < SECTORS_USED_FOR_DIRECTORY; SectorCount++) {
        MDD_SDSPI_SectorRead(SectorCount, Directory.Sector_Access[SectorCount]);
    }
}

char DataLogging_WriteDirectory(void) {
    int SectorCount = 0;
    int write_result = 0;
    for (SectorCount = 0; SectorCount < SECTORS_USED_FOR_DIRECTORY; SectorCount++) {
        write_result = MDD_SDSPI_SectorWrite(SectorCount, Directory.Sector_Access[SectorCount], TRUE);
        if (write_result != TRUE) {
            printf("writeback of directory failed");
        }
    }
}


//only writes back the sector of the currently used entry

char DataLogging_UpdateEntryAddress(void) {
    int write_result = 0;
    write_result = MDD_SDSPI_SectorWrite(SectorforCurrentEntry, Directory.Sector_Access[SectorforCurrentEntry], TRUE);
    if (write_result != TRUE) {
        printf("writeback of directory failed");
    }

}

void DataLogging_PrintDirectory(void) {
    int EntryCount;
    //printf("Sector: ");
    printf("Directory ID: %d\t Last Entry: %d\r\n", Directory.Card_Identifier, Directory.Last_Entry_Used);
    for (EntryCount = 0; EntryCount < ENTRIES_IN_DIRECTORY; EntryCount++) {
        if (Directory.Entries[EntryCount].Start_Address != 0)
            printf("Block ID: %u\t Start: %u Stop: %u\t Size: %u\r\n", Directory.Entries[EntryCount].ID, Directory.Entries[EntryCount].Start_Address, Directory.Entries[EntryCount].Stop_Address, Directory.Entries[EntryCount].Stop_Address - Directory.Entries[EntryCount].Start_Address);
        while (!IsTransmitEmpty());


    }
}


//interface to dump file from sd card

void DataLogging_DumpInterface() {
    //on st
    WipeCard();
}

void WipeCard(void) {
    //we read in the current directory
    DataLogging_ReadDirectory();
    //setting card_identifier to 0 forces a reset
    Directory.Card_Identifier = 0;
    DataLogging_WriteDirectory();
    int EntryCount;
    int SectorCount;
    t_Sector blankSector;
    //set very high such that the chances of it every be used are non-existant
    blankSector.ID = -1;
    //we now want to make sure there is no old data
    for (EntryCount = 0; EntryCount <= Directory.Last_Entry_Used; EntryCount++) {
        if (Directory.Entries[EntryCount].Start_Address != 0) {
            for (SectorCount = Directory.Entries[EntryCount].Start_Address; SectorCount < Directory.Entries[EntryCount].Stop_Address; SectorCount += CHUNK_IN_SECTORS) {
                MDD_SDSPI_SectorWrite(SectorCount, blankSector.Sector_Access, TRUE);
            }
        }
    }
}

int DataLogging_NumEntries(void) {
    return Directory.Last_Entry_Used + 1;
}

int DataLogging_GetEntrySize(int Entry) {
    int size = 0;
    size = Directory.Entries[Entry].Stop_Address - Directory.Entries[Entry].Start_Address;
    return size;

}

int DataLogging_GetEntrySector(int Entry, int Sector, unsigned char *SectorArray) {
    t_Sector inSector;
    int ByteCount = 0;
    int Address = Directory.Entries[Entry].Start_Address + Sector;
    MDD_SDSPI_SectorRead(Address, inSector.Sector_Access);
    for (ByteCount = 0; ByteCount < DATA_SIZE; ByteCount++) {
        //printf("Byte: %d\r\n",inSector.Data[ByteCount]);
        //while(!IsTransmitEmpty());
        SectorArray[ByteCount] = inSector.Data[ByteCount];
    }
    return inSector.ID;
}