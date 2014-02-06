/*
 * File:   Data_Logging.h
 * Author: mdunne
 *
 * Created on July 8, 2012, 1:52 PM
 */

#ifndef DATA_LOGGING_H
#define DATA_LOGGING_H

#include "FSconfig.h"
#include "FSIO.h"

#define DATA_SIZE (MEDIA_SECTOR_SIZE - 2)
#define SD_SECTOR_SIZE MEDIA_SECTOR_SIZE


char DataLogging_Init();

char DataLogging_Log(unsigned char*);

char DataLogging_CloseLog(void);

void DataLogging_PrintDirectory(void);
void DataLogging_DumpInterface();

int DataLogging_NumEntries(void);
int DataLogging_GetEntrySector(int Entry, int Sector, unsigned char *SectorArray);



#endif
