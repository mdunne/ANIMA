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



#endif	/* CIRCBUFFER_H */

