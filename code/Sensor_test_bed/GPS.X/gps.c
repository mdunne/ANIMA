
/*
 * File:   uart.c
 * Author: mdunne
 *
 * Created on November 10, 2011, 8:42 AM
 */

#include <p32xxxx.h>
#include "gps.h"
#include <peripheral/uart.h>
#include <serial.h>
#include <string.h>
//#include <plib.h>
#include <stdlib.h>



//settings for mediatek 3329
#define MEDIATEK_NMEA "$PGCMD,16,1,0,0,0,1*6A\r\n\r\n"
#define MEDIATEK_CHANGE_BAUD "$PMTK251,115200*1F\r\n\r\n"
#define MEDIATEK_REFRESH_RATE "$PMTK220,1000*1F\r\n\r\n"


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define F_CPU 80000000L
#define F_PB F_CPU/2
#define QUEUESIZE 512

/*******************************************************************************
 * PRIVATE DATATYPES                                                           *
 ******************************************************************************/
typedef struct CircBuffer {
    unsigned char buffer[QUEUESIZE];
    int head;
    int tail;
    unsigned int size;
    unsigned char overflowCount;
} CircBuffer;
typedef struct CircBuffer* CBRef;


/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/
void GPSnewCircBuffer(CBRef cB);
void GPSfreeCircBuffer(CBRef* cB);
unsigned int GPSgetLength(CBRef cB);
int GPSreadHead(CBRef cB);
int GPSreadTail(CBRef cB);
unsigned char GPSpeak(CBRef cB);
unsigned char GPSreadFront(CBRef cB);
unsigned char GPSwriteBack(CBRef cB, unsigned char data);

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
struct CircBuffer GoutgoingUart;
CBRef GtransmitBuffer;
struct CircBuffer GincomingUart;
CBRef GreceiveBuffer;







/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
 Function
     SERIAL_Init

 Parameters
     none

 Returns
     None.

 Description
    Initializes the UART subsystem to 115200 and sets up the circular buffer
 Notes
     None.

 Author
 Max Dunne, 2011.11.10 
 ****************************************************************************/

void GPS_Init(void) {
    GtransmitBuffer = (struct CircBuffer*) &GoutgoingUart; //set up buffer for receive
    GPSnewCircBuffer(GtransmitBuffer);

    GreceiveBuffer = (struct CircBuffer*) &GincomingUart; //set up buffer for transmit
    GPSnewCircBuffer(GreceiveBuffer);

    UARTConfigure(UART2, 0x00);
    UARTSetDataRate(UART2, F_PB, 38400);
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    mU2SetIntPriority(4); //set the interrupt priority

    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));

    mU2RXIntEnable(1);
    mU2TXIntEnable(1);
    GPS_Configure();
}

void GPS_Configure(void) {
    //send the string to always change the baud
    //printf("about to change the baud");
    //char *NMEA_String="$PMTK251,115200*1F\r\n\0";
    GPS_PutString(MEDIATEK_CHANGE_BAUD);
    while (!GPS_IsTransmitEmpty());
    //disable the uart and change baud and then re-enable
    UARTEnable(UART2, UART_DISABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    UARTSetDataRate(UART2, F_PB, 115200);
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    //while(!GPS_IsReceiveEmpty());
    while (GPS_GetChar() != '$');
    GPS_PutString(MEDIATEK_NMEA);
    //while(!GPS_IsReceiveEmpty());
    while (GPS_GetChar() != '$');
    GPS_PutString(MEDIATEK_REFRESH_RATE);
    //printf("GPS Should be at 115200");

}

/****************************************************************************
 Function
     PutChar

 Parameters
    char ch, the char to be sent out the serial port

 Returns
     None.

 Description
    adds char to the end of the circular buffer and forces the interrupt flag high is nothing is currently transmitting
 Notes


 Author
    Max Dunne, 2011.11.10
 ****************************************************************************/



void GPS_PutChar(char ch) {
    if (GPSgetLength(GtransmitBuffer) != QUEUESIZE) {
        GPSwriteBack(GtransmitBuffer, ch);
        if (U2STAbits.TRMT) {
            IFS1bits.U2TXIF = 1;
        }
    }
}

void GPS_PutString(char *instring) {
    while (*instring != 0) {
        GPS_PutChar(*instring);
        //PutChar(*instring);
        instring++;
    }
    //why oh why do i need to do this right now, don't care right now though
    //GPS_PutChar('\r');
    //GPS_PutChar('\n');
}

/****************************************************************************
 Function
     GetChar

 Parameters
     None.

 Returns
    ch - char from the serial port

 Description
    reads first character from buffer or returns 0 if no chars available
 Notes
     

 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
char GPS_GetChar(void) {
    char ch;
    if (GPSgetLength(GreceiveBuffer) == 0) {
        ch = 0;
    } else {
        ch = GPSreadFront(GreceiveBuffer);
    }
    return ch;
}

/****************************************************************************
 Function
    IsReceiveEmpty

 Parameters
     None.

 Returns
    TRUE or FALSE

 Description
    returns the state of the receive buffer
 Notes
     

 Author
 Max Dunne, 2011.12.15
 ****************************************************************************/
char GPS_IsReceiveEmpty(void) {
    if (GPSgetLength(GreceiveBuffer) == 0)
        return TRUE;
    return FALSE;
}

/****************************************************************************
 Function
    IsTransmitEmpty

 Parameters
     None.

 Returns
    TRUE or FALSE

 Description
    returns the state of the transmit buffer
 Notes


 Author
 Max Dunne, 2011.12.15
 ****************************************************************************/
char GPS_IsTransmitEmpty(void) {
    if (GPSgetLength(GtransmitBuffer) == 0)
        return TRUE;
    return FALSE;
}

/****************************************************************************
 Function
    IsTransmitEmpty

 Parameters
     None.

 Returns
    TRUE or FALSE

 Description
    returns the state of the transmit buffer
 Notes


 Author
 Max Dunne, 2011.12.15
 ****************************************************************************/
char GPS_GetLength(void) {
    return GPSgetLength(GreceiveBuffer);

}

/****************************************************************************
 Function
    IntUart1Handler

 Parameters
    None.

 Returns
    None.

 Description
    Interrupt Handle for the uart. with the PIC32 architecture both send and receive are handled within the same interrupt

 Notes


 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
void __ISR(_UART2_VECTOR, ipl4) IntUart2Handler(void) {
    if (mU2RXGetIntFlag()) {
        mU2RXClearIntFlag();
        GPSwriteBack(GreceiveBuffer, (unsigned char) U2RXREG);
        gpsControlData.newDatatoParse = 1;
        //PutChar(U2RXREG);

    }
    if (mU2TXGetIntFlag()) {
        mU2TXClearIntFlag();
        if (!(GPSgetLength(GtransmitBuffer) == 0)) {
            U2TXREG = GPSreadFront(GtransmitBuffer);
        }
    }

}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

void GPSnewCircBuffer(CBRef cB) {

    // initialize to zero
    int i;
    for (i = 0; i < QUEUESIZE; i++) {
        cB->buffer[i] = 0;
    }

    // initialize the data members
    cB->head = 0;
    cB->tail = 0;
    cB->size = QUEUESIZE;
    cB->overflowCount = 0;

}

// this function frees the Circular Buffer CB Ref

void GPSfreeCircBuffer(CBRef* cB) {
    // if it is already null, nothing to free
    if (cB == NULL || *cB == NULL) {
        return;
    }

    // free and nil the pointer
    //free(*cB);
    *cB = NULL;
}




// Accesor Methods
// ===============

// returns the amount of unread bytes in the circular buffer

unsigned int GPSgetLength(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        if (cB->head <= cB->tail) {
            return (cB->tail - cB->head);
        } else {
            return (cB->size + cB->tail - cB->head);
        }
    } else {
        return 0;
    }


}

// returns the actual index of the head

int GPSreadHead(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->head);
    } else {
        return 0;
    }

}

// returns the actual index of the tail

int GPSreadTail(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->tail);
    } else {
        return 0;
    }

}

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to GPSpeak will
// always return the same value

unsigned char GPSpeak(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        // if there are bytes in the buffer
        if (GPSgetLength(cB) > 0) {
            return cB->buffer[cB->head];
        }
    }
    return 0;
}


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read

unsigned char GPSreadFront(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        char retVal;
        // if there are bytes in the buffer
        if (GPSgetLength(cB) > 0) {
            retVal = cB->buffer[cB->head];
            cB->head = cB->head < (cB->size - 1) ? cB->head + 1 : 0;
            return retVal;
        }
        return 128;
    }
    return 254;
}

// writes one byte at the end of the circular buffer,
// increments overflow count if overflow occurs

unsigned char GPSwriteBack(CBRef cB, unsigned char data) {
    // if the circular buffer is not null
    if (cB != NULL) {
        if (GPSgetLength(cB) == (cB->size - 1)) {
            cB->overflowCount++;
            //return 1;
        } else {
            cB->buffer[cB->tail] = data;
            cB->tail = cB->tail < (cB->size - 1) ? cB->tail + 1 : 0;
            //return 0;
        }
        //return 0;
    } else {
        return 1;
    }
    return 0;
}

// empties the circular buffer. It does not change the size. use with caution!!

void GPSmakeEmpty(CBRef cB) {
    if (cB != NULL) {
        int i;
        for (i = 0; i < cB->size; ++i) {
            cB->buffer[i] = 0;
        }
        cB->head = 0;
        cB->tail = 0;
        cB->overflowCount = 0;
    }
}

// returns the amount of times the CB has overflown;

unsigned char GPSgetOverflow(CBRef cB) {
    if (cB != NULL) {
        return cB->overflowCount;
    }
    return 0;
}


tGpsData gpsControlData;
char sentence[127];
unsigned char sentenceIndex;
unsigned char checksum;
unsigned char sentenceState;

/**
 * This function converts one hex ASCII character to numeric
 * hex. It's used for the checksum comparison.
 */
char hex2char(char halfhex) {
    if ((halfhex - 48) < 9) {
        return (halfhex - 48);
    }
    return (halfhex - 55);
}

float degMinToDeg(unsigned char degrees, double minutes) {
    //printf("minutes: %f",minutes);
    return ((float) degrees + (minutes / 60.0));
}

void buildAndCheckSentence(unsigned char characterIn) {
    // Full specification for NMEA0138 specifies a maximum sentence length
    // of 255 characters. We're going to ignore this for half the length as
    // we shouldn't get anything that big.
    // This contains the function's state of whether
    // it is currently building a sentence.
    // 0 - Awaiting start character ($)
    // 1 - Building sentence
    // 2 - Building first checksum character
    // 3 - Building second checksum character
    //printf("char: %c\r\n",characterIn);
    // We start recording a new sentence if we see a dollarsign.
    // The sentenceIndex is hard-set to 1 so that multiple dollar-signs
    // keep you at the beginning.
    if (characterIn == '$') {
        //printf("start character at least");
        sentence[0] = characterIn;
        sentenceIndex = 1;
        sentenceState = 1;
    } else if (sentenceState == 1) {
        // Record every character that comes in now that we're building a sentence.
        // Only stop if we run out of room or an asterisk is found.
        sentence[sentenceIndex++] = characterIn;
        if (characterIn == '*') {
            sentenceState = 2;
        } else if (sentenceIndex > 127) {
            // If we've filled up the buffer, ignore the entire message as we can't store it all
            sentenceState = 0;
            sentenceIndex = 0;
        }
    } else if (sentenceState == 2) {
        // Record the first ASCII-hex character of the checksum byte.
        checksum = hex2char(characterIn) << 4;
        sentenceState = 3;
    } else if (sentenceState == 3) {
        // Record the second ASCII-hex character of the checksum byte.
        checksum |= hex2char(characterIn);

        // Now that we've compiled a complete GPS sentence, let's check the checksum and parse it.
        // This code currently only supports RMC and GGA messages.
        if (checksum == getChecksum(sentence, sentenceIndex)) {
            if (sentence[3] == 'R' &&
                    sentence[4] == 'M' &&
                    sentence[5] == 'C') {
                parseRMC(sentence);
            } else if (sentence[3] == 'G' &&
                    sentence[4] == 'G' &&
                    sentence[5] == 'A') {
                parseGGA(sentence);
            }
        }

        // We clear all state variables here regardless of success.
        sentenceIndex = 0;
        sentenceState = 0;
    }
}

void processNewGpsData() {
    //printf("Buffer length: %d\r\n",GPS_GetLength());
    while (GPS_GetLength() > 0) {
        //printf("Buffer length: %d\r\n",GPS_GetLength());
        buildAndCheckSentence(GPS_GetChar());
        //printf("size: %d\r\n%c\r\n",GPS_Get_Uart_Len(),GPS_GetChar());
        //printf("size: %d\r\n%c\r\n",GPS_Get_Uart_Len(),GPS_GetChar());
    }
    gpsControlData.newDatatoParse = 0;
}

// GPS checksum code based on
// http://www.codeproject.com/KB/mobile/WritingGPSApplications2.aspx
// original code in C# written by Jon Person, author of "GPS.NET" (www.gpsdotnet.com)

unsigned char getChecksum(char* sentence, unsigned char size) {

    // Loop through all chars to get a checksum
    unsigned char checkSum = 0;
    unsigned char i;
    for (i = 0; i < size; i++) {
        if (sentence[i] == '$') {
            // Ignore the dollar sign
            continue;
        } else if (sentence[i] == '*') {
            // Stop processing before the asterisk
            break;
        } else {
            checkSum ^= sentence[i];
        }
    }
    // Return the checksum
    return checkSum;
}

/*void getGpsMainData(float* data) {
        data[0] = gpsControlData.lat.flData;
        data[1] = gpsControlData.lon.flData;
        data[2] = gpsControlData.height.flData;

        // Add date info
        tFloatToChar tmp;
        tmp.chData[0] = gpsControlData.day;
        tmp.chData[1] = gpsControlData.month;
        tmp.chData[2] = gpsControlData.year;
        tmp.chData[3] = 0;
        data[3] = tmp.flData;

        // Add time info
        tmp.chData[0] = gpsControlData.sec;
        tmp.chData[1] = gpsControlData.min;
        tmp.chData[2] = gpsControlData.hour;
        tmp.chData[3] = 0;
        data[4] = tmp.flData;

        data[5] = (float)gpsControlData.cog.usData;
        data[6] = (float)gpsControlData.sog.usData/100.0;

        // Mark this data as old now
        gpsControlData.newData = 0;
}*/

// a return value of 1 means the string is done. No more tokens
// This function is stateful, call it once with the String and then with NULL
// similar to strtok but this will support succesive tokens like
// "find,,,the,,commas"

unsigned char myTokenizer(char* stringToTokenize, char token, char * returnToken) {
    static char * pch;
    static char * prevPch;
    static char * lastByte;

    // Make sure the return token is "empty"
    // Tokens set to max-length of 15 bytes
    memset(returnToken, 0, 15);

    // get the pointer to next token if it exists
    // and the stringToTokenize is null
    // Bahavior similar to strtok
    if (stringToTokenize == NULL) {
        pch = strchr(prevPch, token);
    } else {
        pch = strchr(stringToTokenize, token);
        prevPch = stringToTokenize;
        lastByte = stringToTokenize + strlen(stringToTokenize);
    }

    if (pch != NULL) {
        memcpy(returnToken, prevPch, pch - prevPch);
        prevPch = pch + 1;
    } else {
        memcpy(returnToken, prevPch, lastByte - prevPch);
    }

    return pch == NULL;
}

void parseRMC(char* stream) {
    // declare the local vars
    char token[15]; // Tokens set to 15 characters in length
    char tmp [3] = {0, 0, '\0'}, tmp3[4] = {0, 0, 0, '\0'};
    unsigned char chTmp = 0;


    // initialize tokenizer, let go first token which holds the msg type
    // token = strtok(stream, ",");
    myTokenizer(stream, ',', token);

    // 1.- hhmmss.ssss
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 5) {
        tmp[0] = token[0];
        tmp[1] = token[1];
        gpsControlData.hour = (unsigned char) atoi(tmp);
        tmp[0] = token[2];
        tmp[1] = token[3];
        gpsControlData.min = (unsigned char) atoi(tmp);
        tmp[0] = token[4];
        tmp[1] = token[5];
        gpsControlData.sec = (unsigned char) atoi(tmp);
    }

    // 2.- Status of position Fix
    myTokenizer(NULL, ',', token);
    if (strlen(token) == 1) {
        if (token[0] == 'A' || token[0] == 'D') {
            gpsControlData.fix = 1;
        } else {
            gpsControlData.fix = 0;
        }
    }

    // 3.- Latitude
    // ddmm.mmmmmm
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        // get the first two values
        tmp[0] = token[0];
        tmp[1] = token[1];
        // get the degrees
        chTmp = (unsigned char) atoi(tmp);
        // make the degrees zero for minutes conversion
        token[0] = '0';
        token[1] = '0';
        // get the float
        gpsControlData.lat = degMinToDeg(chTmp, atof(token));

        // 4.- Latitude Sector
        myTokenizer(NULL, ',', token);
        if (strlen(token) == 1) {
            // set the sign of the float value
            if (token[0] == 'S' || token[0] == 'W') {
                gpsControlData.lat = -gpsControlData.lat;
            }
        }
    }

    // 5.- Longitude
    // dddmm.mmmmmm
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        // get the first two values
        tmp3[0] = token[0];
        tmp3[1] = token[1];
        tmp3[2] = token[2];
        // get the degrees
        chTmp = (unsigned char) atoi(tmp3);
        // make the degrees zero for minutes conversion
        token[0] = '0';
        token[1] = '0';
        token [2] = '0';
        // get the float
        gpsControlData.lon = degMinToDeg(chTmp, atof(token));

        // 6.- Longitude Sector
        myTokenizer(NULL, ',', token);
        if (strlen(token) == 1) {
            // set the sign of the float value
            if (token[0] == 'S' || token[0] == 'W') {
                gpsControlData.lon = -gpsControlData.lon;
            }
        }
    }

    // 7.- SOG in knots but gets stored in cm/s CAUTION
    // xx.xx
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        gpsControlData.sog.usData = (unsigned short) (atof(token) * KTS2MPS * 100.0);
    }

    // 8.- COG in degrees
    // xxx.xxx
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        gpsControlData.cog.usData = (unsigned short) atof(token);
    }

    // 9.- UTC Date
    // ddmmyy
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 5) {
        // get day
        tmp[0] = token[0];
        tmp[1] = token[1];
        gpsControlData.day = (unsigned char) atoi(tmp);
        // get month
        tmp[0] = token[2];
        tmp[1] = token[3];
        gpsControlData.month = (unsigned char) atoi(tmp);
        // get year
        tmp[0] = token[4];
        tmp[1] = token[5];
        gpsControlData.year = (unsigned char) atoi(tmp);
    }

    // turn the flag on of new data
    gpsControlData.newData = 1;
}

void parseGGA(char* stream) {
    // declare the local vars
    char token[15]; // Declare a token to be 15 characters in length
    char tmp [3] = {0, 0, '\0'}, tmp3[4] = {0, 0, 0, '\0'};
    unsigned char chTmp = 0;

    // initialize tokenizer, let go first token which holds the msg type
    myTokenizer(stream, ',', token);

    // 1.- hhmmss.ssss
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 5) {
        tmp[0] = token[0];
        tmp[1] = token[1];
        gpsControlData.hour = (unsigned char) atoi(tmp);
        tmp[0] = token[2];
        tmp[1] = token[3];
        gpsControlData.min = (unsigned char) atoi(tmp);
        tmp[0] = token[4];
        tmp[1] = token[5];
        gpsControlData.sec = (unsigned char) atoi(tmp);
    }
    // 2.- Latitude
    // ddmm.mmmmmm
    myTokenizer(NULL, ',', token);
    //printf("token %s", token);
    if (strlen(token) > 0) {
        // get the first two values
        tmp[0] = token[0];
        tmp[1] = token[1];
        // get the degrees
        chTmp = (unsigned char) atoi(tmp);
        printf("\r\ntmp: %s\r\nchtmp: %d\r\n", tmp, chTmp);
        // make the degrees zero for minutes conversion
        token[0] = '0';
        token[1] = '0';
        //printf("token: %s\r\n", token);
        //printf("atof(token): %f\r\n", atof(token));
        // get the float
        gpsControlData.lat = degMinToDeg(chTmp, atof(token));
        //printf("\r\nLatittude: %f", gpsControlData.lat);
        // 3.- Latitude Sector
        myTokenizer(NULL, ',', token);
        if (strlen(token) == 1) {
            // Set the sign of the float value.
            // South & west are negative, so we invert the sign in
            // those cases. North/East don't change the value so no
            // need to check those.
            if (token[0] == 'S' || token[1] == 'W') {
                gpsControlData.lat = -gpsControlData.lat;
            }
        }
    }
    //printf("\r\nLatittude: %f", gpsControlData.lat);
    // 4.- Longitude
    // ddmm.mmmmmm
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        // get the first two values
        tmp3[0] = token[0];
        tmp3[1] = token[1];
        tmp3[2] = token[2];
        // get the degrees
        chTmp = (unsigned char) atoi(tmp3);
        // make the degrees zero for minutes conversion
        token[0] = '0';
        token[1] = '0';
        token [2] = '0';
        // get the float
        gpsControlData.lon = degMinToDeg(chTmp, atof(token));

        // 5.- Longitude Sector
        myTokenizer(NULL, ',', token);

        if (strlen(token) > 0) {
            // set the sign of the float value
            if (token[0] == 'S' || token[0] == 'W') {
                gpsControlData.lon = -gpsControlData.lon;
            }
        }
    }

    // 6.- Quality Indicator
    myTokenizer(NULL, ',', token);
    if (strlen(token) == 1) {
        gpsControlData.fix = (char) atoi(token);
    }

    // 7.- Sats used in solution
    // xx
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        gpsControlData.sats = (unsigned char) atoi(token);
    }

    // 8.- Horizontal dilution of solution given from 0 to 99.99 but
    // stored from 0 - 990
    //in integers, i.e HDOP = HDOP_stored/100 CAUTION
    // xx.xx
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        gpsControlData.hdop.usData = (unsigned short) (atof(token)*10.0);
    }

    // 9.- Altitude above mean sea level given in meters
    // xxx.xxx
    myTokenizer(NULL, ',', token);
    if (strlen(token) > 0) {
        gpsControlData.height = atof(token);
    }

    // turn the flag on of new data
    gpsControlData.newData = 1;
}


//#define SERIAL_TEST
#ifdef SERIAL_TEST


    #include <p32xxxx.h>
    #include "serial.h"
    #include <GenericTypeDefs.h>
//#include <plib.h>

int main(void) {
    SERIAL_Init();
    INTEnableSystemMultiVectoredInt();
    printf("\r\nUno Serial Test Harness\r\nAfter this Message the terminal should mirror anything you type.\r\n");

    unsigned char ch = 0;
    while (1) {
        if (IsTransmitEmpty() == TRUE)
            if (IsReceiveEmpty() == FALSE)
                PutChar(GetChar());
    }

    return 0;
}

#endif