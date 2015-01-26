#include <xc.h>
#include <inttypes.h>
#include <GenericTypeDefs.h>

#include <serial.h>
#include "CircBuffer.h"




/*******************************************************************************
 * PRIVATE VARIABLE TYPES
 ******************************************************************************/


// struct containing the requirements for each circular buffer

typedef struct circBuffEntry_t {
    uint8_t isBufferActive;
    uint16_t head;
    uint16_t tail;
    uint16_t bufferSize;
    uint16_t bufferEntrySize;
    void * arrayLocation;
} circBuffEntry_t;


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/


#define NUM_OF_AVAILABLE_BUFFERS 8



/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

static circBuffEntry_t circBuffers[NUM_OF_AVAILABLE_BUFFERS];

static uint8_t areBuffersActive;
static uint8_t numBuffersUsed;

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function CircBuffer_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  initializes buffer information to defaults, needs to be called before any buffers are made
 * @note  None.
 * @author Max Dunne
 * @date 2015.01.20 */
uint8_t CircBuffer_Init(void)
{
    if (areBuffersActive) {
        return ERROR;
    }
    uint16_t currentBuffer;

    //initialize all buffers to unused and zero
    for (currentBuffer = 0; currentBuffer < NUM_OF_AVAILABLE_BUFFERS; currentBuffer++) {
        circBuffers[currentBuffer].isBufferActive = FALSE;
        circBuffers[currentBuffer].head = 0;
        circBuffers[currentBuffer].tail = 0;
        circBuffers[currentBuffer].bufferSize = 0;
        circBuffers[currentBuffer].bufferEntrySize = 0;
        circBuffers[currentBuffer].arrayLocation = 0;
    }
    return SUCCESS;
}


/**
 * @Function CircBuffer_NewCircBufferExplicit(void)
 * @param bufferEntries, number of entries in buffer
 * @param sizePerEntry, size in bytes of each entruy
 * @param arrayAddress, void pointer used to connect to the array used for actual storage of the data
 * @return number of buffer used or ERROR
 * @brief  initializes new circular buffer
 * @note  This function should not be called by the user as the #define handles certain operations for it
 * @author Max Dunne
 * @date 2015.01.20 */
uint8_t CircBuffer_NewCircBufferExplicit(uint16_t bufferEntries,uint16_t sizePerEntry,void * arrayAddress)
{
    if((!areBuffersActive)||numBuffersUsed>=NUM_OF_AVAILABLE_BUFFERS)
    {
        return ERROR;
    }
    uint16_t newBufferIndex;
    numBuffersUsed++;
    circBuffers[newBufferIndex].isBufferActive=TRUE;
    circBuffers[newBufferIndex].bufferSize=bufferEntries;
    circBuffers[newBufferIndex].bufferEntrySize=sizePerEntry;
    circBuffers[newBufferIndex].arrayLocation=arrayAddress;

    return newBufferIndex;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/



#ifdef CIRCBUFFER_TEST



#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN = OFF
#pragma config OSCIOFNC = OFF

#include "serial.h"
#include <BOARD.h>
#include <GenericTypeDefs.h>
//#include <plib.h>

int main(void)
{

    BOARD_Init();
    uint8_t TestBufferOne[5];
    printf("\r\nANIMA  Circular Buffer Test Harness\r\nAfter this Message the terminal should mirror anything you type.\r\n");
    printf("Checking each function before initialization for failure");
    //and skipping these for now due to theory on how
    CircBuffer_Init();
    unsigned char ch = 0;
    while (1) {
        if (IsTransmitEmpty() == TRUE)
            if (IsReceiveEmpty() == FALSE)
                PutChar(GetChar());
    }

    return 0;
}

#endif