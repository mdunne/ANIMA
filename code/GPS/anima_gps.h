#ifndef ANIMA_GPS_H
#define ANIMA_GPS_H

#ifndef UART1_H
#include "uart1.h"
#endif
#include <stdlib.h>
#include <string.h>

#define MEDIATEK

#ifdef MEDIATEK
	#define NMEA_SWITCH MEDIATEK_NMEA
	#define INITIAL_BAUD MEDIATEK_INITIAL_BAUD 
	#define FINAL_BAUD MEDIATEK_MAX_BAUD
	#define CHANGE_BAUD MEDIATEK_CHANGE_BAUD
	#define REFRESH_RATE MEDIATEK_REFRESH_RATE
#endif


//settings for mediatek 3329
#define MEDIATEK_NMEA "$PGCMD,16,1,0,0,0,1*6A\r\n"
#define MEDIATEK_INITIAL_BAUD BAUD_38400
#define MEDIATEK_MAX_BAUD BAUD_115200
#define MEDIATEK_CHANGE_BAUD "$PMTK251,115200*1F\r\n"
#define MEDIATEK_REFRESH_RATE "$PMTK220,1000*1F\r\n"

//setting for locosys

#define LOCOSYS_CHANGE_BAUD MEDIATEK_CHANGE_BAUD
#define LOCOSYS_SELECT_MESSAGE "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n"


//wrapper for functions, eventually will be able to select uart
#define GPS_PutChar UART1PutChar
#define GPS_PutMsg UART1PutMsg
#define GPS_UART_Init UART1Init
#define GPS_GetChar UART1GetChar
#define GPS_Get_Uart_Len UART1GetLength
#define GPS_Get_Uart_Send_Len UART1GetSendLength
#define GPS_Change_Baud UART1ChangeBaud


int init_gps();




typedef union{
	unsigned char    chData[2];
	unsigned short   usData;
} tUnsignedShortToChar; 

typedef union{
	unsigned char    chData[2];
	short   		 shData;
} tShortToChar; 

typedef union{
	unsigned char   chData[4];
	unsigned int   	uiData;
} tUnsignedIntToChar; 

typedef union{
	unsigned char   chData[4];
	int   			inData;
} tIntToChar; 

typedef union{
	unsigned char   chData[4];
	float   		flData;
	unsigned short	shData[2];
} tFloatToChar; 

typedef struct tGpsData{
	unsigned char	 		year;
	unsigned char			month;
	unsigned char			day;
	unsigned char			hour;
	unsigned char			min;
	unsigned char			sec;	 
	float					lat;
	float		 			lon;
	float		 			height;
	tUnsignedShortToChar	cog;
	tUnsignedShortToChar	sog;
	tUnsignedShortToChar	hdop;	
	unsigned char			fix;
	unsigned char 			sats;	
	unsigned char			newData; // Flag for whether this struct stores new data
	unsigned char 			newDatatoParse; //Flag to tell whether there is data to be parsed
}tGpsData;


extern tGpsData gpsControlData;

#define KTS2MPS 		0.514444444

// GPS Circular Buffers
// ====================
#define MSIZE			150
#define CSIZE			26 //[newBytes payload remainingBytes]  (comms buffer out of readGPS)

/**
 * Converts a hexadecimal digit into its ascii equivalent.
 */
char hex2char(char halfhex);

/**
 * Converts degree-minutes to degrees.
 */
float degMinToDeg(unsigned char degrees, float minutes);

/**
 * Compiles GPS sentences one-byte at a time. Because of this
 * it is stateful. Once complete sentences are built, attempts
 * to parse and store in a tGpsData struct
 */
void buildAndCheckSentence(unsigned char characterIn);

/**
 * Pull new bytes from the UART2 receive buffer and
 * calls buildAndCheckSentence on each of them.
 */
void processNewGpsData();

/**
 * Computes the checksum for a given GPS sentence.
 */
unsigned char getChecksum(char* sentence, unsigned char size);

/**
 * This is a Matlab helper function that returns the most recent 
 * GPS data in a large array that Matlab can handle.
 * @param data A pointer to a float array for storing the GPS data that was requested.
 */
void getGpsMainData(float* data);

/**
 * A simple tokenizer. Similar to strtok(), but supports
 * multiple tokens in a row.
 */
unsigned char myTokenizer(char* stringToTokenize, char token, char * returnToken);

/**
 * Parses NMEA0183 RMC sentences. Results are stored in the
 * globally-declared gpsControlData struct.
 */
void parseRMC(char* stream);

/**
 * Parses NMEA0183 GGA sentences. Results are stored in the
 * globally-declared gpsControlData struct.
 */
void parseGGA(char* stream);

       
#endif





