
/*
 * File:   uart.c
 * Author: mdunne
 *
 * Created on November 10, 2011, 8:42 AM
 */

#include <xc.h>
#include "serial.h"
#include <peripheral/uart.h>

#include <peripheral/pps.h>
#include <plib.h>
#include <sys/attribs.h>
//#include <stdlib.h>




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
void newCircBuffer(CBRef cB);
void freeCircBuffer(CBRef* cB);
unsigned int getLength(CBRef cB);
int readHead(CBRef cB);
int readTail(CBRef cB);
unsigned char peak(CBRef cB);
unsigned char readFront(CBRef cB);
unsigned char writeBack(CBRef cB, unsigned char data);

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
struct CircBuffer outgoingUart;
CBRef transmitBuffer;
struct CircBuffer incomingUart;
CBRef receiveBuffer;


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

void SERIAL_Init(void) {
    transmitBuffer = (struct CircBuffer*) &outgoingUart; //set up buffer for receive
    newCircBuffer(transmitBuffer);

    receiveBuffer = (struct CircBuffer*) &incomingUart; //set up buffer for transmit
    newCircBuffer(receiveBuffer);

    UARTConfigure(UART1, 0x00);
    UARTSetDataRate(UART1, F_PB, 115200);
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_TX_BUFFER_EMPTY);

    INTSetVectorPriority(INT_UART_1_VECTOR, INT_PRIORITY_LEVEL_4); //set the interrupt priority

    //RPC5R = 1;
    PPSOutput(1, RPC5, U1TX);
    PORTSetPinsDigitalIn(IOPORT_C, BIT_3);
    //U1RXRbits.U1RXR = 0b111;
    PPSInput(3, U1RX, RPC3);

    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    INTEnable(INT_U1RX, INT_ENABLED);
    //INTSetFlag(INT_U1RX);
    //INTEnable(INT_U1TX, INT_ENABLED);
    //PutChar('z');
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



void PutChar(char ch) {
    if (getLength(transmitBuffer) != QUEUESIZE) {
        writeBack(transmitBuffer, ch);

        if (!INTGetEnable(INT_U1TX)) {
            INTEnable(INT_U1TX, INT_ENABLED);
            //INTSetFlag(INT_U1TX);
        }
        //        if (U1STAbits.TRMT) {
        //            INTEnable(INT_U1TX, INT_ENABLED);
        //            INTSetFlag(INT_U1TX);
        //        } else if (!INTGetEnable(INT_U1TX)) {
        //            INTEnable(INT_U1TX, INT_ENABLED);
        //            //INTSetFlag(INT_U1TX);
        //        }
    }
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
char GetChar(void) {
    char ch;
    if (getLength(receiveBuffer) == 0) {
        ch = 0;
    } else {
        ch = readFront(receiveBuffer);
    }
    return ch;
}

/****************************************************************************
 Function
     _mon_putc

 Parameters
    c - char to be sent

 Returns
    None.

 Description
    overwrites weakly define extern to use circular buffer instead of Microchip functions
 
 Notes
     

 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
void _mon_putc(char c) {
    PutChar(c);
}

/****************************************************************************
 Function
     _mon_puts

 Parameters
    s - pointer to the string to be sent

 Returns
    None.

 Description
    overwrites weakly defined extern to use circular buffer instead of Microchip functions

 Notes


 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
void _mon_puts(const char* s) {
    int i;
    for (i = 0; i<sizeof (s); i++)
        PutChar(s[i]);
}

/****************************************************************************
 Function
     _mon_getc

 Parameters
    canblock - unused variable but required to match Microchip form

 Returns
    None.

 Description
    overwrites weakly defined extern to use circular buffer instead of Microchip functions

 Notes


 Author
 Max Dunne, 2011.11.10
 ****************************************************************************/
int _mon_getc(int canblock) {
    if (getLength(receiveBuffer) == 0)
        return -1;
    return GetChar();
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
char IsReceiveEmpty(void) {
    if (getLength(receiveBuffer) == 0)
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
char IsTransmitEmpty(void) {
    if (getLength(transmitBuffer) == 0)
        return TRUE;
    return FALSE;
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
void __ISR(_UART1_VECTOR, IPL4AUTO) IntUart1Handler(void) {
    static int transmitcount = 0;
    static int clearcount = 0;
    static int stallcount = 0;
    if (INTGetFlag(INT_U1RX)) {
        LATBbits.LATB8 ^= 1;
        writeBack(receiveBuffer, (unsigned char) U1RXREG);
        INTClearFlag(INT_U1RX);
    }
    if (INTGetFlag(INT_U1TX)) {
        //INTClearFlag(INT_U1TX);
        //IFS1bits.U1TXIF=0;
        //INTSTATbits.

        //Nop();
        //LATBbits.LATB7=0;
        //LATBbits.LATB8=PORTCbits.RC3;
        //LATCbits.LATC3^=1;
        if (!(getLength(transmitBuffer) == 0)) {
            transmitcount++;
            U1TXREG = readFront(transmitBuffer);
            INTClearFlag(INT_U1TX);
            stallcount = 0;
        } else {
            clearcount++;
            //INTEnable(INT_U1TX, 0);
            stallcount++;
            Nop();
        }
        if (stallcount > 1) {
            INTEnable(INT_U1TX, INT_DISABLED);
            INTClearFlag(INT_U1TX);
        }
    }

}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

void newCircBuffer(CBRef cB) {

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

void freeCircBuffer(CBRef* cB) {
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

unsigned int getLength(CBRef cB) {
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

int readHead(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->head);
    } else {
        return 0;
    }

}

// returns the actual index of the tail

int readTail(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        return (cB->tail);
    } else {
        return 0;
    }

}

// returns the byte (actual value) that the head points to. this
// does not mark the byte as read, so succesive calls to peak will
// always return the same value

unsigned char peak(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        // if there are bytes in the buffer
        if (getLength(cB) > 0) {
            return cB->buffer[cB->head];
        }
    }
    return 0;
}


// Manipulation Procedures
// ======================
// returns the front of the circular buffer and marks the byte as read

unsigned char readFront(CBRef cB) {
    // if the circular buffer is not null
    if (cB != NULL) {
        char retVal;
        // if there are bytes in the buffer
        if (getLength(cB) > 0) {
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

unsigned char writeBack(CBRef cB, unsigned char data) {
    // if the circular buffer is not null
    if (cB != NULL) {
        if (getLength(cB) == (cB->size - 1)) {
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

void makeEmpty(CBRef cB) {
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

unsigned char getOverflow(CBRef cB) {
    if (cB != NULL) {
        return cB->overflowCount;
    }
    return 0;
}



//#define SERIAL_TEST
#ifdef SERIAL_TEST


#include <xc.h>
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