#include <xc.h>

#include "serial.h"
#include "Sampler.h"
#include "timers.h"
#include <peripheral/timer.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

//timer defines--------------------------------------
#define ACCELMAG_TIMER 0
#define SECOND_TIMER 1
#define POSSIBLE_PRESCALERS 8
#define MAX_TIMER_VALUE 1<<16

#define F_PB (BOARD_GetPBClock()>>1)


/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static unsigned int AccelTickCount = 0;

static unsigned short SecondTickCount = 0;
static unsigned short SecondTickSoftwareScaler = 0;  //required variable as at high processor speeds you need a greater scaler  than hardware allows
//
static float AccelFrequency = 0;

static const unsigned short PossiblePreScalers[] = {1, 2, 4, 8, 16, 32, 64, 256};
static const unsigned int ScalerValues[] = {T4_PS_1_1, T4_PS_1_2, T4_PS_1_4, T4_PS_1_8, T4_PS_1_16, T4_PS_1_32, T4_PS_1_64, T4_PS_1_256};

MagAccelSet CurMagAccelData;

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

    //set up both timers
    AccelFrequency = 12.5;
    Timer_Setup(ACCELMAG_TIMER, AccelFrequency);
    //Timer_Setup(SECOND_TIMER, 1);
}

unsigned int Sampler_GetAccelCount(void) {
    return AccelTickCount;
}

unsigned short Sampler_GetSecondCount(void) {
    return SecondTickCount;
}

float Sampler_GetAccelFrequency(void) {
    return AccelFrequency;
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
            printf("Timer Period: %f  Prescale: %d  Index: %d\r\n", TimerPeriod, PossiblePreScalers[PreScalerIndex], PreScalerIndex);
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
