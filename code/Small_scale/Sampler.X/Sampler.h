/* 
 * File:   Sampler.h
 * Author: mdunne
 *
 * Created on April 15, 2014, 7:52 AM
 */

#ifndef SAMPLER_H
#define	SAMPLER_H

/*******************************************************************************
 * PUBLIC VARIABLE TYPES
 ******************************************************************************/
typedef enum {
    RATE_12P5_HERTZ = 0,
    RATE_50_HERTZ,
    RATE_100_HERTZ,
    RATE_200_HERTZ,
    RATE_400_HERTZ,
    RATE_800_HERTZ
} Valid_AccelMagRates;

typedef struct XYZPoint {
    short X;
    short Y;
    short Z;
} XYZPoint;

typedef struct MagAccelSet {
    XYZPoint MagData;
    XYZPoint AccelData[10];
} MagAccelSet;


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/




/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function Sampler_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  sets up the timers to their default rates and handles any onetime initialization of sensors
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_Init(void);

/**
 * @Function Sampler_Sample(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  handles the actual data collection, designed to be run in the main loop and called repetively
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_Sample(void);


/**
 * @Function Sampler_Sample
 * @param None
 * @return SUCCESS or ERROR
 * @brief  handles the actual data collection, designed to be run in the main loop and called repetively
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_Sample(void);

/**
 * @Function Sampler_SubmitData
 * @param DataID, ID code from table to identify the type of data
 * @param DataPointer, void pointer pointing to data, other modules will need to lookup data size to correctly use
 * @return SUCCESS or ERROR
 * @brief  used to submit data to other modules.
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_SubmitData(unsigned char DataID, void *DataPointer);

/**
 * @Function Sampler_SetAccelMagSampleRate
 * @param NewSampleRate, a valid sensor rate
 * @return SUCCESS or ERROR
 * @brief  sets the sample rate of the accelerometer with which the magnetometer will be slaved to be 10x slower
 * @note  If sample rate needed is slower that one of the given rates it should not be handled by this system
 * @author Max Dunne */
unsigned char Sampler_SetAccelMagSampleRate(unsigned char NewSampleRate);


/**
 * @Function Sampler_SetSensorSampleRate
 * @param NewSampleRate, a valid sensor rate with fastest interval of one second
 * @return SUCCESS or ERROR
 * @brief  sets the ticks between samples for sensors other than mag/accel
 * @note  quite possibly this should handle mag/accel as well when in sleep mode
 * @author Max Dunne */
unsigned char Sampler_SetSensorSampleRate(unsigned char Sensor, unsigned char NewSampleRate);

/**
 * @Function Sampler_GetSecondCount(void)
 * @return current count in seconds
 * @brief  gets the count of the one second timer
 * @note  with current implementation overflow occurs every 18.2 hours
 * @author Max Dunne */
unsigned short Sampler_GetSecondCount(void);

/**
 * @Function Sampler_GetAccelCount(void)
 * @return current number of ticks on accel sample rate
 * @brief  gets the tick count of the high speed timer
 * @note  this timer varies greatly in speed,
 * @author Max Dunne */
unsigned int Sampler_GetAccelCount(void);

/**
 * @Function Sampler_GetAccelRate(void)
 * @return current hertz of accel
 * @brief  
 * @note  returns a float due to slow sample rates at times
 * @author Max Dunne */
float Sampler_GetAccelFrequency(void);

#endif	/* SAMPLER_H */

