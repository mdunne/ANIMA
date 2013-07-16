/*
 * File:   RCServo.c
 * Author: Elkaim
 *
 * Created on December 7, 2011, 3:23 PM
 */
//#define RCSERVO_TEST

#include <p32xxxx.h>
#include <plib.h>
#include "RCServo.h"
#include "bits.h"
#include <stdio.h>
#include "serial.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

//#define DEBUG_VERBOSE
#ifdef DEBUG_VERBOSE
    #define dbprintf(...) printf(__VA_ARGS__)
#else
    #define dbprintf(...)
#endif

#define RCPINCOUNT 10
#define SERVOCENTER 1500
#define RCPERIODTIME 20000
#define FULLOVERFLOW 0xFFFF

#define RC_TRISX03 TRISFbits.TRISF5
#define RC_LATX03 LATFbits.LATF5
#define RC_TRISX04 TRISBbits.TRISB0
#define RC_LATX04 LATBbits.LATB0

#define RC_TRISY06 TRISDbits.TRISD10
#define RC_LATY06 LATDbits.LATD10
#define RC_TRISY07 TRISEbits.TRISE7
#define RC_LATY07 LATEbits.LATE7

#define RC_TRISZ08 TRISDbits.TRISD8
#define RC_LATZ08 LATDbits.LATD8
#define RC_TRISZ09 TRISEbits.TRISE1
#define RC_LATZ09 LATEbits.LATE1

#define RC_TRISV03 TRISBbits.TRISB2
#define RC_LATV03 LATBbits.LATB2
#define RC_TRISV04 TRISBbits.TRISB3
#define RC_LATV04 LATBbits.LATB3

#define RC_TRISW07 TRISBbits.TRISB15
#define RC_LATW07 LATBbits.LATB15
#define RC_TRISW08 TRISBbits.TRISB14
#define RC_LATW08 LATBbits.LATB14

/* Note that you need to set the prescalar and periferal clock appropriate to
 * the processor board that you are using. In order to calculate the minimal
 * prescalar: Prescalar = (2000*F_PB/(1000000*0xFFFF))+1, round down */
#ifndef F_CPU
#define F_CPU       80000000L
#define F_PB        (F_CPU/2)
#define F_PB_IN_KHZ (F_PB/1000)
#define PRESCALE    2
#define uSEC        (F_PB_IN_KHZ / (PRESCALE * 1000))
#endif

/* Code readability Macros, information hiding */
#define RC_SetPin(pin) *RC_LATSET[RCpinMap[pin]] = rcBitsMap[RCpinMap[pin]]
#define RC_ClearPin(pin) *RC_LATCLR[RCpinMap[pin]] = rcBitsMap[RCpinMap[pin]]
#define RC_SetPeriod(pin) WritePeriod4(ReadTimer4() + uSEC * RC_upTime[RCpinMap[pin]])
#define RC_GetTime(pin) RC_upTime[RCpinMap[pin]]

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static volatile unsigned int * const RC_TRISCLR[] = {&TRISFCLR, &TRISBCLR, &TRISDCLR,
    &TRISECLR, &TRISDCLR, &TRISECLR,
    &TRISBCLR, &TRISBCLR, &TRISBCLR,
    &TRISBCLR};

static volatile unsigned int * const RC_TRISSET[] = {&TRISFSET, &TRISBSET, &TRISDSET,
    &TRISESET, &TRISDSET, &TRISESET,
    &TRISBSET, &TRISBSET, &TRISBSET,
    &TRISBSET};

static volatile unsigned int * const RC_LATSET[] = {&LATFSET, &LATBSET, &LATDSET,
    &LATESET, &LATDSET, &LATESET,
    &LATBSET, &LATBSET, &LATBSET,
    &LATBSET};
static volatile unsigned int * const RC_LATCLR[] = {&LATFCLR, &LATBCLR, &LATDCLR,
    &LATECLR, &LATDCLR, &LATECLR,
    &LATBCLR, &LATBCLR, &LATBCLR,
    &LATBCLR};
static unsigned short int rcBitsMap[] = {BIT_5, BIT_0, BIT_10, BIT_7, BIT_8,
    BIT_1, BIT_2, BIT_3, BIT_15, BIT_14};

static enum {
    off, init, first, cycling, idling, first_shuttingdown, cycling_shuttingdown
} RCstate = off;

static short int RC_upTime[RCPINCOUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static char RCpinMap[RCPINCOUNT];
static char numRCPins = 0;
static int uSecondsLeftToGo = RCPERIODTIME;

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
 Function: RC_Init

 Parameters
     RCpins: an unsigned short with a 1 in each position to set the pin as an RC
             servo pin, should be a bitwise OR of the #define'd RC_PORTxxx pins.

 Returns
     char: SUCCESS or ERROR

 Description
    Initializes the RC_Servo subsystem, sets each pin as a digital output, and
    sets the uptime for each pin at 1.5msec, with a period of 20msec.

 Notes: Uses TIMER4 with a rollover.

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
char RC_Init(unsigned short int RCpins) {
    char i, curPin;
    unsigned short int CurrentTime;
    dbprintf("\nInitializing the RC Servo Module.");
    // Check if inputs are in range, and if already initialized
    if ((RCpins == 0x000) || (RCpins > 0x2FF) || (RCstate != off)) {
        return ERROR;
    }
    RCstate = init;
    // Go through input and set each RC pin direction and force to low
    for (i = 0; i < RCPINCOUNT; i++) {
        curPin = (1 << i);
        if (RCpins & curPin) {
            RCpinMap[numRCPins] = i;
            numRCPins++;
            RC_upTime[i] = SERVOCENTER;
            *RC_TRISCLR[i] = rcBitsMap[i]; // Sets pin direction to output
            *RC_LATCLR[i] = rcBitsMap[i]; // Forces pin to low state
            dbprintf("\nEnabling pin: 0x%X", curPin);
        }
    }
    // Release ADC pins to RC servo control
    //    if (RCpins & RC_PORTX04) AD1PCFGbits.PCFG0 = 1;
    //    if (RCpins & RC_PORTV03) AD1PCFGbits.PCFG2 = 1;
    //    if (RCpins & RC_PORTV04) AD1PCFGbits.PCFG3 = 1;
    //    if (RCpins & RC_PORTW07) AD1PCFGbits.PCFG15 = 1;
    //    if (RCpins & RC_PORTW08) AD1PCFGbits.PCFG14 = 1;
    // Set up Timer #4 to overflow at more than 2msec, enable and set interrupt
    OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_2 |
            T4_32BIT_MODE_OFF | T4_SOURCE_INT, SERVOCENTER * uSEC);
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_4 | T4_INT_SUB_PRIOR_0);
    mT4IntEnable(1);
    RCstate = first;
    return SUCCESS;
}

/****************************************************************************
 Function: RC_SetPulseTime

 Parameters
     RCpin: a single pin from the #define'd RC_PORTxxx pins to set the high time
     pulseTime: uptime for pulse in uSeconds (1000 to 2000)

 Returns
     char: SUCCESS or ERROR

 Description
    Sets the period for the RC servo pin in microseconds, from a minimum of 1000
    to a maximum of 2000. Pin must have been init'd previously or will return an
    ERROR.

 Notes: None.

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
char RC_SetPulseTime(unsigned short int RCpin, unsigned short int pulseTime) {
    char i = 0;
    dbprintf("\nSetting RC pin time for pin 0x%X", RCpin);
    if ((pulseTime < MINPULSE) || (pulseTime > MAXPULSE) || (RCstate == off)) {
        return ERROR;
    }
    while (RCpin > 1) {
        RCpin >>= 1;
        i++;
    }
    if (RC_upTime[i] == 0) {
        return ERROR;
    } else {
        RC_upTime[i] = pulseTime;
        dbprintf("\nPin #%u uptime set to %u uSec", i, RC_upTime[i]);
    }
    return SUCCESS;
}

/****************************************************************************
 Function: RC_GetPulseTime

 Parameters
     RCpin: a single pin from the #define'd RC_PORTxxx pins to retrieve the
     currently set high time (provided for completeness)

 Returns
    High time of pulse in uSeconds (unsigned short int), will return 0 if pin is
    not active.

 Description
    Gets the currenly set pulse time of the input pin.

 Notes: None.

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
short int RC_GetPulseTime(unsigned short int RCpin) {
    char i = 0;
    if (RCstate == off) {
        return ERROR;
    }
    dbprintf("\nGetting RC pin time for pin 0x%X", RCpin);
    while (RCpin > 1) {
        RCpin >>= 1;
        i++;
    }
    dbprintf(" - Uptime: %u [uSec]", RC_upTime[i]);
    return (RC_upTime[i]);
}

/****************************************************************************
 Function: RC_End

 Parameters
    None.

 Returns
    char: SUCESS or ERROR

 Description
    Shuts down the RC_Servo module, releases all pins back to inputs.
 
 Notes
    As currently implemented, this causes an immediate shutdown, which might
    result in a short pulse ( < 1msec ). This needs to be addressed later.

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
char RC_End(void) {
    char i, curPin, bitVal;
    dbprintf("\nShutting down RC module");
    if (RCstate == off) {
        return ERROR;
    }
    if ((RCstate == idling)||(RCstate == first)) {
        mT4IntEnable(0);
        for (i = 0; i < numRCPins; i++) {
            curPin = RCpinMap[i];
            RC_ClearPin(i);
            RC_upTime[curPin] = 0;
            *RC_TRISSET[curPin] = rcBitsMap[curPin]; // set the RC_Pin to input
            dbprintf("\nShutdown pin %u[0x%X]", i, curPin);
        }
        RCstate = off;
        return SUCCESS;
    }
    if (RCstate == cycling) {
        RCstate = cycling_shuttingdown;
        dbprintf("\nCycling, shutdown first pin, wait to kill all others");
        curPin = RCpinMap[0];
        RC_upTime[curPin] = 0;
        *RC_TRISSET[curPin] = rcBitsMap[curPin]; // set the RC_Pin to input
        dbprintf("\nShutdown pin %u[0x%X]", 0, curPin);
        return SUCCESS;
    }
}

/****************************************************************************
 Function: Timer4IntHandler

 Parameters: None.

 Returns: None.

 Description
    Implements the RC_Servo state machine through the Timer4 Interrupt handler.
    Raises and lowers the appropriate RC pins, and implements a countdown to get
    to the 20msec repetition rate.

 Notes
    Potentially unstable as writing to Timer4 overflow register (PR4) while
    Timer4 is still running. Also, TMR4 is volatile, so reading and resetting for
    the "idling" case could potentially overflow.

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
void __ISR(_TIMER_4_VECTOR, ipl4) Timer4IntHandler(void) {
    static char numPin = 0;
    char curPin, prevPin;
    unsigned short int currentTime;

    mT4ClearIntFlag();
    switch (RCstate) {

        case first:
            numPin = 0;
            RC_SetPin(numPin);
            RC_SetPeriod(numPin);
            uSecondsLeftToGo -= RC_GetTime(numPin);
            if (++numPin == numRCPins) { // only one pin in RC set
                RCstate = idling;
            } else {
                RCstate = cycling;
            }
            break;

        case cycling:
            RC_SetPin(numPin);
            RC_ClearPin(numPin - 1);
            RC_SetPeriod(numPin);
            uSecondsLeftToGo -= RC_GetTime(numPin);
            if (++numPin == numRCPins) { // done with pins
                RCstate = idling;
            }
            break;

        case idling:
            RC_ClearPin(numPin - 1);
            currentTime = ReadTimer4();
            if ((uSecondsLeftToGo * uSEC + currentTime) < FULLOVERFLOW) {
                WritePeriod4(currentTime + uSEC * uSecondsLeftToGo);
                uSecondsLeftToGo = RCPERIODTIME;
                RCstate = first;
            } else { // need to cycle through
                uSecondsLeftToGo -= MAXPULSE;
                WritePeriod4(currentTime + uSEC * MAXPULSE);
            }
            break;

        case cycling_shuttingdown:
            RC_ClearPin(numPin - 1);
            {
                char i;
                for (i = 0; i < numRCPins; i++) {
                    curPin = RCpinMap[i];
                    RC_ClearPin(i);
                    RC_upTime[curPin] = 0;
                    *RC_TRISSET[curPin] = rcBitsMap[curPin]; // set the RC_Pin to input
                    dbprintf("\nShutdown pin %u[0x%X]", i, curPin);
                }
            }
            RCstate = off;
            mT4IntEnable(0);
            dbprintf("\nFinal shutdown of RC Servo system");
            break;


        default:
            mT4IntEnable(0);
            dbprintf("\nHorrible Error, stopping Timer4");
            break;
    }
}

/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/
#ifdef RCSERVO_TEST
#include <p32xxxx.h>
#include "serial.h"
#include "RCServo.h"
#include <plib.h>
#include <stdio.h>

#define DELAY() for(i=0;i < NOPCOUNT; i++) __asm("nop")
#define NOPCOUNT 60000
#define TOTALCYCLES 2000

int main(void) {
    int i,j, inc, width = 1000;
    inc = 100;

    SERIAL_Init();
    AD1PCFG = 0xFF;
    INTEnableSystemMultiVectoredInt();

    printf("\nHello World!");
    RC_Init(RC_PORTX03 | RC_PORTX04 | RC_PORTY06 | RC_PORTY07 | RC_PORTZ08 | RC_PORTV03);
    RC_SetPulseTime(RC_PORTX03, width);

    LATFbits.LATF0 ^= 1;
    LATGbits.LATG6 ^= 1;

    for (j=0;j < TOTALCYCLES; j++) {
        DELAY();
        LATFbits.LATF0 ^= 1;
        LATGbits.LATG6 ^= 1;
        width += inc;
        if (width > 2000) {
            inc *= -1;
            width += inc;
        }
        if (width < 1000) {
            inc *= -1;
            width += inc;
        }
        RC_SetPulseTime(RC_PORTX03, width);

    }
    RC_End();
    return 0;
}
#endif