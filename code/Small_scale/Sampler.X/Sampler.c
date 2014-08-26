#include <xc.h>

#include "serial.h"
#include "Sampler.h"
#include "timers.h"
#include "DataEncoding.h"
#ifndef USE_FAKE_DATA
#include "freescale_accel.h"
#include "freescale_mag.h"
#include "gps.h"
#include <AD.h>
#endif
#include <peripheral/timer.h>
#include <inttypes.h>

/*******************************************************************************
 * PRIVATE VARIABLE TYPES
 ******************************************************************************/
typedef struct SensorSampleSettings_t {
    uint16_t TicksBetweenSamples;
    uint16_t NextSampleTime;
} SensorSampleSettings_t;


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

//timer defines--------------------------------------
#define ACCELMAG_TIMER 0
#define SECOND_TIMER 1
#define POSSIBLE_PRESCALERS 8
#define MAX_TIMER_VALUE 1<<16

#define F_PB (BOARD_GetPBClock()>>1)

//use of these defines or same multiplier will result in desired 10:1 sample ratio
#define DEFAULT_ACCEL_TICK_COUNT 1 
#define DEFAULT_MAG_TICK_COUNT 10


/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static unsigned int AccelTickCount = 0;

static unsigned short SecondTickCount = 0;
static unsigned short SecondTickSoftwareScaler = 0; //required variable as at high processor speeds you need a greater scaler  than hardware allows
//
static float AccelFrequency = 0;

static const unsigned short PossiblePreScalers[] = {1, 2, 4, 8, 16, 32, 64, 256};
static const unsigned int ScalerValues[] = {T4_PS_1_1, T4_PS_1_2, T4_PS_1_4, T4_PS_1_8, T4_PS_1_16, T4_PS_1_32, T4_PS_1_64, T4_PS_1_256};

static MagAccelSet_t CurMagAccelData;
static UnionizedSet_t UnionSetTest;
static GPSSet_t CurGPSData;
static TempSet_t CurTempData;

struct SensorRates {
    SensorSampleSettings_t Accel;
    SensorSampleSettings_t Mag;
    SensorSampleSettings_t GPS;
    SensorSampleSettings_t Temp;
} SensorRates;

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/

/**
 * @Function Timer_Setup
 * @param Timer, One of the #defined TIMERS
 * @param TimerRate, a valid timer Rate
 * @return SUCCESS or ERROR
 * @brief  sets up the timer for the first time including setting up the interrupt
 * @note  wrapper function to the timer library to compartmentalize the timer access functions
 * @author Max Dunne */
unsigned char Timer_Setup(unsigned char Timer, float TimerRate);


/**
 * @Function Timer_SetSampleRate
 * @param Timer, One of the #defined TIMERS
 * @param TimerRate, a valid timer Rate
 * @return SUCCESS or ERROR
 * @brief  changes the sample rate for given timer and clears the interrupts for it
 * @note  wrapper function to the timer library to compartmentalize the timer access functions
 * @author Max Dunne */
unsigned char Timer_SetSampleRate(unsigned char Timer, float TimerRate);

/**
 * @Function Timer_DeterminePrescaler
 * @param TimerRate, a valid timer Rate
 * @return Prescaler appropriate for sample rate
 * @brief  determines a proper prescaler from const array to allow for accurate 
 * @note  wrapper function to the timer library to compartmentalize the timer access functions
 * @author Max Dunne */
unsigned int Timer_DeterminePrescaler(float TimerRate);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function Sampler_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief  sets up the timers to their default rates and handles any onetime initialization of sensors
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_Init(void) {
    //start by initializing the sensors for the first time
    //left blank as getting timers correct ranks higher for now
    //        printf("Size of bulk access: %d and size of internal data struct: %d\r\n",sizeof(CurMagAccelData.BulkAccess),sizeof(CurMagAccelData.DataAccess));
    //        while(1);

    CurMagAccelData.DataAccess.PacketId = 34;
    CurGPSData.DataAccess.PacketID = 42;
    CurTempData.DataAccess.PacketId = 62;


    //temp code to intialize the gps struct to something useful, will be moved to sample when real data is used
    //    CurGPSData.DataAccess.Location.Lat = 37.000370;
    //    CurGPSData.DataAccess.Location.Lon = -122.063309;
    //    CurGPSData.DataAccess.Location.Alt = 433.36;
    //    CurGPSData.DataAccess.Location.Fix = 3;
    //    CurGPSData.DataAccess.Location.NumOfSats = 7;
    //    CurGPSData.DataAccess.Location.HDOP = 3;
    //    CurGPSData.DataAccess.Time.Year = 14;
    //    CurGPSData.DataAccess.Time.Month = 8;
    //    CurGPSData.DataAccess.Time.Day = 20;
    //    CurGPSData.DataAccess.Time.Hour = 12;
    //    CurGPSData.DataAccess.Time.Min = 12;
    //    CurGPSData.DataAccess.Time.Sec = 32;




    //set up both timers
    AccelFrequency = 12.5;
    SensorRates.Accel.TicksBetweenSamples = DEFAULT_ACCEL_TICK_COUNT;
    SensorRates.Accel.NextSampleTime = Sampler_GetAccelCount() + SensorRates.Accel.TicksBetweenSamples;
    SensorRates.Mag.TicksBetweenSamples = DEFAULT_MAG_TICK_COUNT;
    SensorRates.Mag.NextSampleTime = Sampler_GetAccelCount() + SensorRates.Mag.TicksBetweenSamples;


    //these will slow down tremendously in short order but want a base point to start with
    SensorRates.GPS.TicksBetweenSamples = 60;
    SensorRates.GPS.NextSampleTime = Sampler_GetSecondCount() + SensorRates.GPS.TicksBetweenSamples;
    SensorRates.Temp.TicksBetweenSamples = 30;
    SensorRates.Temp.NextSampleTime = Sampler_GetSecondCount() + SensorRates.Temp.TicksBetweenSamples;

    Timer_Setup(ACCELMAG_TIMER, AccelFrequency);
    //Timer_Setup(SECOND_TIMER, 1);
}

uint16_t Sampler_GetAccelCount(void) {
    return AccelTickCount;
}

uint16_t Sampler_GetSecondCount(void) {
    return SecondTickCount;
}

float Sampler_GetAccelFrequency(void) {
    return AccelFrequency;
}

/**
 * @Function Sampler_Sample
 * @param None
 * @return SUCCESS or ERROR
 * @brief  handles the actual data collection, designed to be run in the main loop and called repetively
 * @note  None.
 * @author Max Dunne */
unsigned char Sampler_Sample(void) {
    static uint16_t CurrentTickCount = 0; //local variable to ensure that the calls occur on the same interrupt, only static to save heap thrashing
    static uint8_t AccelSampleCounter = 0; //local variable to keep track of the sample count for accel to enforce 10:1
    CurrentTickCount = Sampler_GetAccelCount();

    //sample the accel
    if (CurrentTickCount >= SensorRates.Accel.NextSampleTime) {
#ifndef USE_FAKE_DATA
        //        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].X = free_GetXData();
        //        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Y = free_GetYData();
        //        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Z = free_GetZData();
        free_GetTriplet(CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].TripletAccess);
        //                printf("%d\t%d\t%d\r\n",CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].X,CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Y,CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Z);
#else
        //we sample the data here, loading with timestamp instead for now
        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].X = CurrentTickCount;
        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Y = CurrentTickCount + 1;
        CurMagAccelData.DataAccess.AccelData[AccelSampleCounter].Z = CurrentTickCount*-1;
#endif
        //printf("ACCEL Sample Taken at %d of sample number %d\r\n", CurrentTickCount, AccelSampleCounter);
        SensorRates.Accel.NextSampleTime = CurrentTickCount + SensorRates.Accel.TicksBetweenSamples;
        AccelSampleCounter++;
    }
    //sample the mag
    if (CurrentTickCount >= SensorRates.Mag.NextSampleTime) {
#ifndef USE_FAKE_DATA
        //        CurMagAccelData.DataAccess.MagData.X = free_GetXData();
        //        CurMagAccelData.DataAccess.MagData.Y = free_GetYData();
        //        CurMagAccelData.DataAccess.MagData.Z = free_GetZData();
        free_mag_GetTriplet(CurMagAccelData.DataAccess.MagData.TripletAccess);
#else
        //we sample the data here, loading with timestamp instead for now
        CurMagAccelData.DataAccess.MagData.X = CurrentTickCount;
        CurMagAccelData.DataAccess.MagData.Y = CurrentTickCount;
        CurMagAccelData.DataAccess.MagData.Z = CurrentTickCount;
#endif
        printf("MAG Sample Taken at %d\r\n", CurrentTickCount);
        SensorRates.Mag.NextSampleTime = CurrentTickCount + SensorRates.Mag.TicksBetweenSamples;


        //as this is the mag datapoint we also submit data at this point for the mag/accel
        //as the encoder is not set up we will print the data for testing purposes
        DataEncoding_SubmitData(CurMagAccelData.BulkAccess);
        AccelSampleCounter = 0;
        uint8_t incrementor = 0;
        printf("ACCEL Data: ");
        for (incrementor = 0; incrementor < 66; incrementor++) {
            //            printf("%d   ", CurMagAccelData.DataAccess.AccelData[incrementor].X);
            //            printf("%d\t",CurMagAccelData.BulkAccess[incrementor]);
        }
        printf("   MAG: %d %d\r\n", CurMagAccelData.DataAccess.MagData.X, Sampler_GetSecondCount());

    }
    //with slow scale sensors we now record the tick count for the slow timer
    CurrentTickCount = Sampler_GetSecondCount();

    //sample the GPS
    if (CurrentTickCount >= SensorRates.GPS.NextSampleTime) {
#ifndef USE_FAKE_DATA
        CurGPSData.DataAccess.Location.Lat = gpsControlData.lat;
        CurGPSData.DataAccess.Location.Lon = gpsControlData.lon;
        CurGPSData.DataAccess.Location.Alt = gpsControlData.altitude;
        CurGPSData.DataAccess.Location.Fix = gpsControlData.fix;
        CurGPSData.DataAccess.Location.NumOfSats = gpsControlData.sats;
        CurGPSData.DataAccess.Location.HDOP = gpsControlData.hdop.usData;
        CurGPSData.DataAccess.Time.Year = gpsControlData.year;
        CurGPSData.DataAccess.Time.Month = gpsControlData.month;
        CurGPSData.DataAccess.Time.Day = gpsControlData.day;
        CurGPSData.DataAccess.Time.Hour = gpsControlData.hour;
        CurGPSData.DataAccess.Time.Min = gpsControlData.min;
        CurGPSData.DataAccess.Time.Sec = gpsControlData.sec;
#else
#endif
        printf("%f\t%f\t%f\r\n", CurGPSData.DataAccess.Location.Lat, CurGPSData.DataAccess.Location.Lon, CurGPSData.DataAccess.Location.Alt);
        DataEncoding_SubmitData(CurGPSData.BulkAccess);
        printf("GPS Sample Taken at %d\r\n", CurrentTickCount);
        SensorRates.GPS.NextSampleTime = CurrentTickCount + SensorRates.GPS.TicksBetweenSamples;
    }

    //sample the Temp
    if (CurrentTickCount >= SensorRates.Temp.NextSampleTime) {
        //we sample the data here, loading with timestamp instead for now
#ifndef USE_FAKE_DATA
        CurTempData.DataAccess.Temp=AD_TempRead();
#else
        CurTempData.DataAccess.Temp++;
#endif
        DataEncoding_SubmitData(CurTempData.BulkAccess);
        printf("TEMP Sample Taken at %d\r\n", CurrentTickCount);
        SensorRates.Temp.NextSampleTime = CurrentTickCount + SensorRates.Temp.TicksBetweenSamples;
    }

}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


unsigned char Timer_Setup(unsigned char Timer, float TimerRate) {
    switch (Timer) {
        case ACCELMAG_TIMER:
            AccelTickCount = 0;
            CloseTimer4();
            INTClearFlag(INT_T4);
            INTSetVectorPriority(INT_TIMER_4_VECTOR, 3);
            INTSetVectorSubPriority(INT_TIMER_4_VECTOR, 3);
            Timer_SetSampleRate(Timer, TimerRate);
            INTEnable(INT_T4, INT_ENABLED);
            return SUCCESS;
            break;
        case SECOND_TIMER:
            SecondTickCount = 0;
            CloseTimer2();
            INTClearFlag(INT_T2);
            INTSetVectorPriority(INT_TIMER_2_VECTOR, 3);
            INTSetVectorSubPriority(INT_TIMER_2_VECTOR, 3);
            Timer_SetSampleRate(Timer, TimerRate);
            INTEnable(INT_T2, INT_ENABLED);
            return SUCCESS;
            break;
        default:
            return ERROR;
    }
}

unsigned char Timer_SetSampleRate(unsigned char Timer, float TimerRate) {
    //     printf("Getting here for %d\r\n", Timer);
    unsigned int PreScalerIndex = 0;
    float TimerPeriod = 0;
    float ScaledTimerRate = TimerRate * 2;
    switch (Timer) {
        case ACCELMAG_TIMER:
            CloseTimer4();
            INTClearFlag(INT_T4);
            PreScalerIndex = Timer_DeterminePrescaler(ScaledTimerRate);
            TimerPeriod = (float) ((float) F_PB / (float) PossiblePreScalers[PreScalerIndex] / ScaledTimerRate);
            SecondTickSoftwareScaler = (int) ScaledTimerRate;
            //printf("Timer Period: %f  Prescale: %d  Index: %d\r\n", TimerPeriod, PossiblePreScalers[PreScalerIndex], PreScalerIndex);
            OpenTimer4(T4_ON | T4_SOURCE_INT | ScalerValues[PreScalerIndex], (unsigned int) TimerPeriod);
            return SUCCESS;
        default:
            return ERROR;
    }
}

unsigned int Timer_DeterminePrescaler(float TimerRate) {
    unsigned char curPrescalerIndex = 0;
    unsigned int ScalerIndex = 0;
    unsigned int curTimerPeriod = 0;
    for (curPrescalerIndex = 0; curPrescalerIndex < POSSIBLE_PRESCALERS; curPrescalerIndex++) {
        curTimerPeriod = F_PB / PossiblePreScalers[curPrescalerIndex] / TimerRate;
        ScalerIndex = curPrescalerIndex;
        //printf("Current Timer Period: %d index: %d\r\n",curTimerPeriod,curPrescalerIndex);
        if (curTimerPeriod < MAX_TIMER_VALUE)
            break;
    }
    //    printf("Current Timer Period: %d index: %d\r\n", curTimerPeriod, curPrescalerIndex);

    return ScalerIndex;
}

/**
 * @Function Timer4IntHandler(void)
 * @param None.
 * @return None.
 * @brief  This is the interrupt handler to support the timer module. It will increment
 * time, to maintain the functionality of the GetTime() timer and it will check
 * through the active timers, decrementing each active timers count, if the
 * count goes to 0, it will set the associated event flag and clear the active
 * flag to prevent further counting.
 * @author Max Dunne 2011.11.15 */
void __ISR(_TIMER_4_VECTOR, ipl3) Timer4IntHandler(void) {
    static unsigned short SecondTickSoftwareScalerCounter = 1;
    static unsigned char Toggler = 1;
    INTClearFlag(INT_T4);
    if (Toggler % 2 == 0) {
        AccelTickCount++;
    }
    Toggler++;
    if (SecondTickSoftwareScalerCounter < SecondTickSoftwareScaler) {
        SecondTickSoftwareScalerCounter++;
    } else {
        SecondTickCount++;
        SecondTickSoftwareScalerCounter = 1;
    }
}
