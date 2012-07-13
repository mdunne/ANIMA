/*
   File:   serial.h
   Author: mdunne

   Created on November 10, 2011, 8:43 AM
 */

#ifndef GPS_H
#define GPS_H


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#ifndef SUCCESS
#define SUCCESS 0
#define ERROR -1
#endif


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/


/****************************************************************************
 Function
     

 Parameters
     none

 Returns
     None.

 Description
    
 Notes
     None.

 Author
 Max Dunne, 2011.11.10 0905
 ****************************************************************************/
/**
 * Function: SERIAL_Init
 * @param None
 * @return None
 * @remark Initializes the UART subsystem to 115200 and sets up the circular buffer
 * @author Max Dunne
 * @date 2011.11.10  */
void GPS_Init(void);

/**
 * Function: PutChar
 * @param ch, the char to be sent
 * @return None
 * @remark adds character to circular buffer and starts the uart transmitting
 *          if not already
 * @author Max Dunne
 * @date 2011.11.10  */
//void PutChar(char ch);

/**
 * Function: GetChar
 * @param None
 * @return character or 0
 * @remark retrieves first character from the receive buffer or 0
 * @author Max Dunne
 * @date 2011.11.10  */
char GPS_GetChar(void);

/**
 * Function: IsTransmitEmpty
 * @param None
 * @return TRUE or FALSE
 * @remark returns the state of the transmit buffer
 * @author Max Dunne
 * @date 2011.12.15  */
char GPS_IsTransmitEmpty(void);

/**
 * Function: IsReceiveEmpty
 * @param None
 * @return TRUE or FALSE
 * @remark returns the state of the receive buffer
 * @author Max Dunne
 * @date 2011.12.15  */
char GPS_IsReceiveEmpty(void);


void GPS_Configure(void);
void GPS_PutString(char *MEDIATEK_CHANGE_BAUD);
;

typedef union {
    unsigned char chData[2];
    unsigned short usData;
} tUnsignedShortToChar;

typedef union {
    unsigned char chData[2];
    short shData;
} tShortToChar;

typedef union {
    unsigned char chData[4];
    unsigned int uiData;
} tUnsignedIntToChar;

typedef union {
    unsigned char chData[4];
    int inData;
} tIntToChar;

typedef union {
    unsigned char chData[4];
    float flData;
    unsigned short shData[2];
} tFloatToChar;

typedef struct tGpsData {
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned short millisec;
    float lat;
    float lon;
    float height;
    tUnsignedShortToChar cog;
    tUnsignedShortToChar sog;
    tUnsignedShortToChar hdop;
    unsigned char fix;
    unsigned char sats;
    unsigned char newData; // Flag for whether this struct stores new data
    unsigned char newDatatoParse; //Flag to tell whether there is data to be parsed
} tGpsData;


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
float degMinToDeg(unsigned char degrees, double minutes);

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


#endif // serial_h
