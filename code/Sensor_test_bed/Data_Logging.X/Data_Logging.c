


#include <Data_Logging.h>
#include "FSIO.h"
#include <xc.h>
#include <stdio.h>
#include "SD-SPI.h"
#include "timers.h"
#include "serial.h"


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
static int CurSector;
static int SectorforCurrentEntry;
static int CurDirectorySize;
static short curFileID;

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
    t_Sector curSector;
    unsigned char filenum = 1;
    char filename[7];
    unsigned char filecount = 0;
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
    if (!FSInit()) {
        printf("File System Initializaion Failed");
        while (1);
    }
    //We now need to find the new file name
    char Searchresult;
    //search for the first file matching filepattern
    Searchresult = FindFirst(FILEPATTERN, ATTR_MASK, &rec);
    printf("%d\r\n", Searchresult);
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
            printf("%d\t%s\r\n", filenum, rec.filename);
            Searchresult = FindNext(&rec);
        }
    }
    curFileID = filecount;
    sprintf(filename, "%03d.bin", filecount);
    FilePointer = FSfopen(filename, "w");
    //we extract the first sector of the file
    CurSectorCount = Cluster2Sector(FilePointer->dsk, FilePointer->cluster) + FilePointer->sec;
#ifdef DEBUG_VERBOSE
    printf("First Sector of File is: %d\r\n", CurSector);
    while (!IsTransmitEmpty());
#endif
    //while(1);
    int curtime=GetTime();
    FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
#ifdef DEBUG_VERBOSE
    printf("Time to allocate %d was %d milliseconds\r\n",CHUNK_IN_SECTORS,GetTime()-curtime);
#endif
    //while (1);

}


//we assume that this is 510 in size

char DataLogging_Log(unsigned char *Sector_block) {
    static unsigned int ChunkCount = 0;
    t_Sector inSector;
    unsigned char SPI_Status = FALSE;
    int ByteCount = 0;
    //inSector.Sector_Access=Sector_block;
    //this is copying the data currently as my head is blanking on the proper pointer math
    //fix this soon please
    for (ByteCount = 0; ByteCount < DATA_SIZE; ByteCount++) {
        inSector.Data[ByteCount] = Sector_block[ByteCount];
    }
    inSector.ID = curFileID;
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
    //printf("%d\r\n",ChunkCount);
    if (ChunkCount >= CHUNK_IN_SECTORS) {
#ifdef DEBUG_VERBOSE
        printf("Card allocated more sectors\r\n");
#endif
        int curtime=GetTime();
        FILEallocate_multiple_clusters(FilePointer, CHUNK_IN_SECTORS);
        printf("Time to allocate %d was %d milliseconds\r\n",CHUNK_IN_SECTORS,GetTime()-curtime);
        ChunkCount = 0;
    }
    //printf("ChunkCount: %d\tCurSectorCount: %d\r\n",ChunkCount,CurSectorCount);

}

char DataLogging_CloseLog(void) {
    FSfclose(FilePointer);
}

char DataLogging_ReadDirectory(void) {

    int SectorCount = 0;
    for (SectorCount = 0; SectorCount < SECTORS_USED_FOR_DIRECTORY; SectorCount++) {
        MDD_SDSPI_SectorRead(SectorCount, Directory.Sector_Access[SectorCount]);
    }
}

char DataLogging_WriteDirectory(void) {
    return;
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

