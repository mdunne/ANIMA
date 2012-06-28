/*
   File:   serial.h
   Author: mdunne

   Created on November 10, 2011, 8:43 AM
 */

#ifndef SERIAL_H
#define SERIAL_H


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
void SERIAL_Init(void);

/**
 * Function: PutChar
 * @param ch, the char to be sent
 * @return None
 * @remark adds character to circular buffer and starts the uart transmitting
 *          if not already
 * @author Max Dunne
 * @date 2011.11.10  */
void PutChar(char ch);

/**
 * Function: GetChar
 * @param None
 * @return character or 0
 * @remark retrieves first character from the receive buffer or 0
 * @author Max Dunne
 * @date 2011.11.10  */
char GetChar(void);

/**
 * Function: IsTransmitEmpty
 * @param None
 * @return TRUE or FALSE
 * @remark returns the state of the transmit buffer
 * @author Max Dunne
 * @date 2011.12.15  */
char IsTransmitEmpty(void);

/**
 * Function: IsReceiveEmpty
 * @param None
 * @return TRUE or FALSE
 * @remark returns the state of the receive buffer
 * @author Max Dunne
 * @date 2011.12.15  */
char IsReceiveEmpty(void);

#endif // serial_h
