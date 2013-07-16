/*
 * File:   timers.c
 * Author: mdunne
 *
 * Created on November 15, 2011, 9:53 AM
 */

#include <p32xxxx.h>
#include <peripheral/timer.h>
#include "timers.h"
#include <GenericTypeDefs.h>
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define TIMERS_TEST

#define F_CPU 80000000L
#define F_PB F_CPU/2
#define TIMER_FREQUENCY 1000
/*******************************************************************************
 * VERY IMPORTANT INFORMATION REGARDING TIMESCALES
 * if timer frequency is set too high the processor can no longer respond fast enough
 * if needed timing at that scale enable the #define below
 * you will no longer have the other timers, only the free running timer which will
 * at once per 1.6microseconds and a max time of 1.9 hours
 *
 * ******************************************************************************/
//#define HIGH_SPEED_TIMING
#ifdef HIGH_SPEED_TIMING
#undef TIMER_FREQUENCY
#define TIMER_FREQUENCY (F_PB/64)
#endif
//Change to alter number of used timers with a max of 32
#define NUM_TIMERS 16

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static unsigned int Timer_Array[NUM_TIMERS];
static unsigned int TimerActiveFlags;
static unsigned int TimerEventFlags;
static unsigned int FreeRunningTimer;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
 Function
     TIMERS_Init

 Parameters
    none

 Returns
     None.

 Description
     Initializes the timer module
 Notes
     None.

 Author
     Max Dunne, 2011.11.15
 ****************************************************************************/
void TIMERS_Init(void) {
    TimerActiveFlags = 0;
    TimerEventFlags = 0;
    FreeRunningTimer = 0;
#ifdef HIGH_SPEED_TIMING

    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, 0xFFFF);
    //ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_3);
    INTSetVectorPriority(INT_TIMER_1_VECTOR,INT_PRIORITY_LEVEL_3);
#else
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_1, F_PB / TIMER_FREQUENCY);
    //ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_3);
    INTSetVectorPriority(INT_TIMER_1_VECTOR,INT_PRIORITY_LEVEL_3);
#endif

    INTEnable(INT_TIMER_1_VECTOR,INT_ENABLED);
    //mT1IntEnable(1);
}

/****************************************************************************
 Function
     SetTimer

 Parameters
     unsigned int Num, the number of the timer to set.
    unsigned int NewTime, the number of milliseconds to be counted

 Returns
     ERROR if requested timer does not exist
     SUCCESS  otherwise

 Description
     sets the time for a timer, but does not make it active.

 Notes
     None.

 Author
 Max Dunne  2011.11.15
 ****************************************************************************/

char SetTimer(unsigned char Num, unsigned int NewTime) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    Timer_Array[Num] = NewTime;
    return SUCCESS;
}

/****************************************************************************
 Function
     StartTimer

 Parameters
     unsigned char Num the number of the timer to start

 Returns
     ERROR if requested timer does not exist
     SUCCESS  otherwise

 Description
     simply sets the active flag in TMR_ActiveFlags to resart a
     stopped timer.

 Notes
     None.

 Author
    Max Dunne, 2011.11.15
 ****************************************************************************/

char StartTimer(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerActiveFlags |= (1 << Num);
    return SUCCESS;
}

/****************************************************************************
 Function
     StopTimer

 Parameters
     unsigned char Num the number of the timer to stop.

 Returns
     ERROR if requested timer does not exist
     SUCCESS  otherwise

 Description
     simply clears the bit in TimerActiveFlags associated with this
     timer. This will cause it to stop counting.

 Notes
     None.

 Author
    Max Dunne 2011.11.15
 ****************************************************************************/
char StopTimer(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerActiveFlags &= ~(1 << Num);
    return SUCCESS;
}

/****************************************************************************
 Function
       InitTimer

 Parameters
     unsigned char Num, the number of the timer to start
     unsigned int NewTime, the number of tick to be counted

 Returns
     ERROR if requested timer does not exist
     SUCCESS  otherwise

 Description
     sets the NewTime into the chosen timer and clears any previous
     event flag and sets the timer actice to begin counting.

 Notes

 Author
    Max Dunne 2011.11.15
 ****************************************************************************/
char InitTimer(unsigned char Num, unsigned int NewTime) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    Timer_Array[Num] = NewTime;
    TimerEventFlags &= ~(1 << Num);
    TimerActiveFlags |= (1 << Num);
    return SUCCESS;
}

/****************************************************************************
 Function
     IsTimerActive

 Parameters
     unsigned char Num the number of the timer to check

 Returns
     ERROR if requested timer is not valid
     TIMER_NOT_ACTIVE if timer is not active
     TIMER_ACTIVE if it is active

 Description
     used to determine if a timer is currently counting.

 Notes
     None.

 Author
    Max Dunne   2011.11.15
 ****************************************************************************/
char IsTimerActive(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    if ((TimerActiveFlags & (1 << Num)) != 0) {
        return TIMER_ACTIVE;
    } else {
        return TIMER_NOT_ACTIVE;
    }
}

/****************************************************************************
 Function
     IsTimerExpired

 Parameters
     unsigned char Num the number of the timer to check

 Returns
     ERROR if requested timer is not valid
     TIMER_NOT_EXPIRED if timer is not active
     TIMER_EXPIRED if it is active

 Description
     used to determine if a timer is currently expired.

 Notes
     None.

 Author
    Max Dunne   2011.11.15
 ****************************************************************************/
char IsTimerExpired(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    if ((TimerEventFlags & (1 << Num)) != 0) {
        return TIMER_EXPIRED;
    } else {
        return TIMER_NOT_EXPIRED;
    }
}

/****************************************************************************
 Function
     ClearTimerExpired

 Parameters
     unsigned char Num, the timer whose event flag should be cleared.

 Returns
     ERROR if requested timer does not exist
     SUCCESS otherwise

 Description
     simply clears the appropriate bit in Event Flags to show that
     the event has been serviced.

 Notes
     None.

 Author
     Max Dunne  211.11.15
 ****************************************************************************/

char ClearTimerExpired(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerEventFlags &= ~(1 << Num);
    return SUCCESS;
}

/****************************************************************************
 Function
     GetTime

 Parameters
     None.

 Returns
     the current value of the module variable FreeRunningTimer

 Description
     Provides the ability to grab a snapshot time as an alternative to using
      the library timers. Can be used to determine how long between 2 events.

 Notes


 Author
     Max Dunne, 2012.01.08
 ****************************************************************************/
unsigned int GetTime(void) {
#ifdef HIGH_SPEED_TIMING
    return TMR1 + FreeRunningTimer * 0xFFFF;
#else
    return FreeRunningTimer;
#endif
}

/****************************************************************************
 Function
    GetTicksPerSecond

 Parameters
     None.

 Returns
     the number of ticks for a second

 Description
    returns the number of ticks per second. Can be used to have the same timing
    regardless of the time base of the timers.
 Notes
    this assumes time base is kept in a possible range

 Author
     Max Dunne, 2013.06.25
 ****************************************************************************/
unsigned int GetTicksPerSecond(void) {
    return TIMER_FREQUENCY;
}

/****************************************************************************
 Function
     Timer1IntHandler

 Parameters
     None.

 Returns
     None.

 Description
     This is the interrupt handler to support the timer module.
     It will increment time, to maintain the functionality of the
     GetTime() timer and it will check through the active timers,
     decrementing each active timers count, if the count goes to 0, it
     will set the associated event flag and clear the active flag to
     prevent further counting.

 Notes
     None.

 Author
     Max Dunne 2011.11.15
 ****************************************************************************/

void __ISR(_TIMER_1_VECTOR, ipl3) Timer1IntHandler(void) {
    INTClearFlag(INT_TIMER_1_VECTOR);
    FreeRunningTimer++;
#ifndef HIGH_SPEED_TIMING
    char CurTimer = 0;
    if (TimerActiveFlags != 0) {
        for (CurTimer = 0; CurTimer < NUM_TIMERS; CurTimer++) {
            if ((TimerActiveFlags & (1 << CurTimer)) != 0) {
                if (--Timer_Array[CurTimer] == 0) {
                    TimerEventFlags |= (1 << CurTimer);
                    TimerActiveFlags &= ~(1 << CurTimer);
                }
            }
        }
    }
#endif
}




#ifdef TIMERS_TEST

#include <xc.h>
#include "serial.h"
#include "timers.h"
#include <GenericTypeDefs.h>
#define TIMERS_IN_TEST NUM_TIMERS
//#include <plib.h>

int main(void) {
    int i = 0;
    SERIAL_Init();
    TIMERS_Init();
    INTEnableSystemMultiVectoredInt();

    printf("\r\nUno Timers Test Harness\r\n");
    printf("Setting each timer for one second longer than the last and waiting for all to expire.  There are %d available timers with a time base of %g seconds\r\n", TIMERS_IN_TEST, 1 / (float) GetTicksPerSecond());
#ifdef HIGH_SPEED_TIMING
    printf("In high speed mode, will print out current time every second\r\n");
    while (1) {
        if ((GetTime() % GetTicksPerSecond()) == 0) {
            printf("%f\r\n", (float) GetTime() / (float) GetTicksPerSecond());
            while ((GetTime() % GetTicksPerSecond()) == 0);
        }
        //        printf("%u\r\n",GetTime());
        //        while(!IsTransmitEmpty());
    }
#endif
    for (i = 0; i <= TIMERS_IN_TEST; i++) {
        InitTimer(i, (i + 1) * GetTicksPerSecond()); //for second scale
    }
    while (IsTimerActive(TIMERS_IN_TEST - 1) == TIMER_ACTIVE) {
        for (i = 0; i <= TIMERS_IN_TEST; i++) {
            if (IsTimerExpired(i) == TIMER_EXPIRED) {
                printf("Timer %d has expired and the free running counter is at %d\r\n", i, GetTime());
                ClearTimerExpired(i);
            }
        }
    }
    printf("All timers have ended\r\n");
    printf("Setting and starting 1st timer to 2 seconds using alternative method. \r\n");
    SetTimer(0, 2 * GetTicksPerSecond());
    StartTimer(0);
    while (IsTimerExpired(0) != TIMER_EXPIRED);
    printf("2 seconds should have elapsed\r\n");
    printf("Starting 1st timer for 8 seconds but also starting 2nd timer for 4 second\r\n");
    InitTimer(0, 8 * GetTicksPerSecond());
    InitTimer(1, 4 * GetTicksPerSecond());
    while (IsTimerExpired(1) != TIMER_EXPIRED);
    printf("4 seconds have passed and now stopping 1st timer\r\n");
    StopTimer(0);
    printf("Waiting 6 seconds to verifiy that 1st timer has indeed stopped\r\n");
    InitTimer(1, 3 * GetTicksPerSecond());
    i = 0;
    while (IsTimerActive(1) == TIMER_ACTIVE) {
        if (IsTimerExpired(0) == TIMER_EXPIRED) {
            i++;
            ClearTimerExpired(0);
        }
    }
    if (i == 0) {
        printf("Timer did not expire, module working correctly\r\n");
    } else {
        printf("Timer did expire, module not working correctly\r\n");
    }

    return 0;
}

#endif