/* 
 * File:   
 * Author: mdunne
 *
 */

#ifndef DATAENCODING_H
#define	DATAENCODING_H



/*******************************************************************************
 * PUBLIC VARIABLE TYPES
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/




/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function DataEncoding_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  sets the array to their base configuration and initiailizes any needed values
 * @note  None.
 * @author Max Dunne */
unsigned char DataEncoding_Init(void);



/**
 * @Function DataEncoding_SubmitDataHelper(void)
 * @param DataPointer, a void pointer for accepting any datatype
 * @param DataSize, how large the data is
 * @return SUCCESS or ERROR
 * @brief  takes in incoming data and processes it
 * @note  Not normally called by the user
 * @author Max Dunne */
unsigned char DataEncoding_SubmitDataHelper(void *DataPointer,unsigned int DataSize);


/**
 * @Function DataEncoding_SubmitData(void)
 * @param DataPointer, a void pointer for accepting any datatype
 * @param DataSize, how large the data is
 * @return SUCCESS or ERROR
 * @brief  macro to wrap data size into the helper function
 * @note  
 * @author Max Dunne */
#define DataEncoding_SubmitData(x) DataEncoding_SubmitDataHelper(x,sizeof(x))


#endif	/* DATAENCODING_H */

