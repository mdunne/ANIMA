/* 
 * File:   
 * Author: mdunne
 *
 */

#ifndef CIRCBUFFER_H
#define	CIRCBUFFER_H

/*******************************************************************************
 * PUBLIC INCLUDES
 ******************************************************************************/
#include <inttypes.h>


/*******************************************************************************
 * PUBLIC VARIABLE TYPES
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/




/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

///**
// * @Function Sampler_Init(void)
// * @param None
// * @return SUCCESS or ERROR
// * @brief  sets up the timers to their default rates and handles any onetime initialization of sensors
// * @note  None.
// * @author Max Dunne */
//unsigned char Sampler_Init(void);


/**
 * @Function CircBuffer_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  initializes buffer information to defaults, needs to be called before any buffers are made
 * @note  None.
 * @author Max Dunne
 * @date 2015.01.20 */
uint8_t CircBuffer_Init(void);





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
uint8_t CircBuffer_NewCircBufferExplicit(uint16_t bufferEntries,uint16_t sizePerEntry,void * arrayAddress);


#define CircBuffer_NewCircBuffer(bufferEntries,dataType,arrayAddress) CircBuffer_NewCircBufferExplicit(bufferEntries,sizeof(dataType),arrayAddress)



/**
 * @Function CircBuffer_SizeArray(DesiredBufferLength,BufferEntry)
 * @param DesiredBufferLength, desired number of entries
 * @param BufferEntry, datatype to be stored in the buffer
 * @return number of buffer used or ERROR
 * @brief  initializes new circular buffer
 * @note  This function should not be called by the user as the #define handles certain operations for it
 * @author Max Dunne
 * @date 2015.01.20 */
#define CircBuffer_SizeArray(DesiredBufferLength,BufferEntry) (DesiredBufferLength*sizeof(BufferEntry))


#endif	/* CIRCBUFFER_H */

