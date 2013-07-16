/*
 * File:   Stepper.c
 * Author: Elkaim
 *
 * Created on January 2, 2012, 9:49 PM
 */

#include <p32xxxx.h>
#include <plib.h>

#include "Stepper.h"
#include "Serial.h"
#include "PORTS.h"


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define STEPPER_TEST
//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
    #define dbprintf(...) printf(__VA_ARGS__)
#else
    #define dbprintf(...)
#endif

/* Note that you need to set the prescalar and periferal clock appropriate to
 * the processor board that you are using. In order to calculate the minimal
 * prescalar: Prescalar = (2000*F_PB/(1000000*0xFFFF))+1, round down */
#ifndef F_CPU
#define F_CPU       80000000L
#define F_PB        (F_CPU/2)
#define F_PB_DIV8   (F_PB/8)
#define F_PB_DIV64  (F_PB/64)
#define ONE_KHZ_RATE  (F_PB_DIV8-1)/1000
#endif

#define MED_HZ_RATE 77
#define LOW_HZ_RATE 10
#define LOW_REP_NUM 64
#define TWENTY_KILOHERTZ 20000

#define LED_BANK1_3 LATDbits.LATD6
#define LED_BANK1_2 LATDbits.LATD11
#define LED_BANK1_1 LATDbits.LATD3
#define LED_BANK1_0 LATDbits.LATD5


#define ShutDownDrive() (COIL_A_ENABLE = 0, COIL_B_ENABLE = 0)
#define TurnOnDrive() (COIL_A_ENABLE = 1, COIL_B_ENABLE = 1)

/*******************************************************************************
 * PRIVATE STRUCTS and TYPEDEFS                                                *
 ******************************************************************************/
//integer round: (x - 1)/y + 1
/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

static int stepCount = 0;
static unsigned short int overflowReps = 0;
static unsigned char stepDir = FORWARD;
static enum {off,inited,stepping,halted,waiting} stepperState = off;
static enum {step_one,step_two,step_three,step_four} coilState = step_one;

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/
/**
 * @Function: CalculateOverflowPeriod(unsigned short int rate);
 * @param pulse rate is steps per second (0 = 0.5Hz, special case)
 * @return period overflow for timer to match step rate
 * @remark Calculates the overflow period and sets the module variable
 *         overflowReps to match for the right step rate.
 *         Note: rate 0 is a special case corresponding to 0.5Hz
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.28 23:21 */
unsigned short int CalculateOverflowPeriod(unsigned short int rate);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/* There are three possibilities for the step rate calculation that keep the
   step rate error to under 0.2% of the desired value, from within 0.5 to 2KHz:
   from 78 to 20Khz, Prescale is 1:8, Rollover = (F_PB/8-1)/PPS
   from 10 to 77Hz, Prescale is 1:64, Rollover = (F_PB/64-1)/PPS
   from 0.5 to 10Hz, Set rollover for a constant 1Khz, and increment to reach
   the desired time, Prescale is 1:8, Rollover = (F_PB/8-1)/1000 and the number
   of times to repeat is (1000-1)/PPS + 1                                     */
char Stepper_Init(unsigned short int rate)
{
    unsigned short int overflowPeriod;
    if (rate > TWENTY_KILOHERTZ) return ERROR;
    dbprintf("\nInitializing Stepper Module");
    stepCount = 0;
    overflowReps = 0;
    // Initialize hardware (no current flow)
    COIL_A_DIRECTION = 1;
    COIL_B_DIRECTION = 1;
    ShutDownDrive();
    TRIS_COIL_A_DIRECTION = 0;
    TRIS_COIL_A_ENABLE = 0;
    TRIS_COIL_B_DIRECTION = 0;
    TRIS_COIL_B_ENABLE = 0;
    // Calculate overflow time and prescalar
    overflowPeriod = CalculateOverflowPeriod(rate);
    dbprintf("\nOverflow Period: %u",overflowPeriod);
    dbprintf("\nNumber of Reps: %u",overflowReps);
    // Setup timer and interrupt
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_8, overflowPeriod);
//    OpenTimer5(T5_ON | T5_IDLE_STOP | T5_GATE_OFF | T5_PS_1_8 | T5_SOURCE_INT,overflowPeriod);
//    OpenTimer5(T5_ON | T5_PS_1_8 | T5_SOURCE_INT, overflowPeriod);
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_3 );
    mT3IntEnable(1);
    stepperState = inited;
    return SUCCESS;
}

char Stepper_ChangeStepRate(unsigned short int rate)
{
    unsigned short int overflowPeriod;
    if ((rate > TWENTY_KILOHERTZ)||(stepperState == off)) return ERROR;
    dbprintf("\nChanging step rate");
    T5CONbits.ON = 0; // halt timer5
    overflowPeriod = CalculateOverflowPeriod(rate);
    WritePeriod5(overflowPeriod);
    if (stepperState != halted) {
        T3CONbits.ON = 1; // restart timer3
    }
    return SUCCESS;
}

char Stepper_SetSteps(char direction, unsigned int steps)
{
    if (stepperState == off) return ERROR;
    if ((direction==FORWARD)||(direction==REVERSE)) {
        stepDir = direction;
        stepCount = steps;
        switch(stepperState) {
            case waiting:
            case inited:
                stepperState = stepping;
                break;
            default:
                break;
        }
        return SUCCESS;
    }
    return ERROR;
}

char Stepper_IncrementSteps(char direction, unsigned int steps)
{
    unsigned int tempSteps;
    if ((stepperState == off)||(steps==0)) return ERROR;
    if ((direction==FORWARD)||(direction==REVERSE)) {
        if ((direction==FORWARD)&&(stepDir==FORWARD)) {
            stepCount += steps;
        }
        if ((direction==REVERSE)&&(stepDir==REVERSE)) {
            stepCount += steps;
        }
        if ((direction==FORWARD)&&(stepDir==REVERSE)) {
            if (steps > stepCount) {
                tempSteps = steps - stepCount;
                stepDir = FORWARD;
                stepCount = tempSteps;
            } else {
                stepCount -= steps;
            }
        }
        if ((direction==REVERSE)&&(stepDir==FORWARD)) {
            if (steps > stepCount) {
                tempSteps = steps - stepCount;
                stepDir = REVERSE;
                stepCount = tempSteps;
            } else {
                stepCount -= steps;
            }
        }
    }
    if (stepperState != halted) {
        if (stepCount > 0) stepperState = stepping;
        else {
            stepperState = waiting;
            ShutDownDrive();
        }
    }
    return SUCCESS;
}

char Stepper_GetDirection(void)
{
    return stepDir;
}

unsigned int Stepper_GetRemainingCount(void)
{
    return stepCount;
}

char Stepper_Halt(void)
{
    if ((stepperState == off)||(stepperState == halted)) return ERROR;
    dbprintf("\nHalting Stepper drive");
    T3CONbits.ON = 0; // stop timer3, turn off drive
    ShutDownDrive();
    return SUCCESS;
}

char Stepper_Resume(void)
{
    if (stepperState != halted) return ERROR;
    dbprintf("\nResuming Stepper drive");
    if (stepCount > 0) {
        stepperState = stepping;
    } else {
        stepperState = waiting;
    }
    T3CONbits.ON = 1; // restart timer3
    return SUCCESS;
}

char Stepper_End(void)
{
    if (stepperState == off) return ERROR;
    dbprintf("\nTerminating Stepper module");
    T3CONbits.ON = 0; // halt timer3
    stepperState = off;
    ShutDownDrive();
    // turn hardware pins back to inputs
    TRIS_COIL_A_DIRECTION = 1;
    TRIS_COIL_A_ENABLE = 1;
    TRIS_COIL_B_DIRECTION = 1;
    TRIS_COIL_B_ENABLE = 1;
    // reset module variables
    stepCount = 0;
    overflowReps = 0;
    coilState = step_one;
    // turn off timer and interrupt
    CloseTimer5();
    return SUCCESS;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

unsigned short int CalculateOverflowPeriod(unsigned short int rate)
{
    dbprintf("\nCalculating Overflow period");
    if (rate==0) {
        overflowReps = 2000;
        return(ONE_KHZ_RATE);
    }
    if (rate > MED_HZ_RATE) {
        overflowReps = 0;
        return ((F_PB_DIV8-1)/rate);
    }
    if (rate > LOW_HZ_RATE) {
        overflowReps = LOW_REP_NUM;
        return ((F_PB_DIV64-1)/rate);
    }
    // rate is less than 10Hz, switch to counted 1KHz pulses
    overflowReps = (1000-1)/rate + 1;
    return ONE_KHZ_RATE;
}

/****************************************************************************
 Function: Timer5IntHandler

 Parameters: None.

 Returns: None.

 Description
    Implements the Stepper motor FULL STEP drive state machine.

 Notes
    

 Author: Gabriel Hugh Elkaim, 2011.12.15 16:42
 ****************************************************************************/
void __ISR(_TIMER_3_VECTOR, ipl4) Timer3IntHandler(void)
{
    static unsigned short timerLoopCount = 0;
    LED_BANK1_0 ^= 1;
    if (++timerLoopCount > overflowReps) {
        timerLoopCount = 0;
        LED_BANK1_1 ^= 1;
        // execute Stepper Drive state machine here
        switch(stepperState) {
            case off: // should not get here
                dbprintf("\noff");
                T5CONbits.ON = 0; // halt timer5
                ShutDownDrive();
                CloseTimer5();
                break;

            case inited:
            case halted:
            case waiting:
                ShutDownDrive();
                if (stepCount < 0) stepCount = 0;
                LED_BANK1_2 ^= 1;
                break;

            case stepping:
                if (--stepCount <= 0) stepperState = waiting;
                LED_BANK1_3 ^= 1;
                TurnOnDrive();
                switch(coilState) {
                    case step_one:
                        // coil drive both forward
                        COIL_A_DIRECTION = 1;
                        COIL_B_DIRECTION = 1;
                        if (stepDir == FORWARD) coilState = step_two;
                        else coilState = step_four;
                        break;

                    case step_two:
                        // coil drive A forward, B reverse
                        COIL_A_DIRECTION = 1;
                        COIL_B_DIRECTION = 0;
                        if (stepDir == FORWARD) coilState = step_three;
                        else coilState = step_one;
                        break;

                    case step_three:
                        // coil drive both reverse
                        COIL_A_DIRECTION = 0;
                        COIL_B_DIRECTION = 0;
                        if (stepDir == FORWARD) coilState = step_four;
                        else coilState = step_two;
                        break;

                    case step_four:
                        // coild drive A reverse, B forward
                        COIL_A_DIRECTION = 0;
                        COIL_B_DIRECTION = 1;
                        if (stepDir == FORWARD) coilState = step_one;
                        else coilState = step_three;
                        break;
                }
                break;
        }
    }
    mT3ClearIntFlag();
}

/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/
#ifdef STEPPER_TEST

#define NOPCOUNT 150000
#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")

int main(void) {
    int i;
    unsigned short pattern;
    char j,k;

    SERIAL_Init();
    AD1PCFG = 0xFF;
    INTEnableSystemMultiVectoredInt();
    //enable LED bank 1
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD11 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD5 = 0;

    printf("\nHello World!");
    Stepper_Init(100);
    printf("\nStepping forward 420 steps");
    Stepper_SetSteps(FORWARD,420);
    for (j=0;j<10;j++) {
        DELAY();
        printf(".");
        DELAY();
        printf("\t%u",Stepper_GetRemainingCount());
    }
    while(Stepper_GetRemainingCount() > 1) {
        printf("o");
        DELAY();
    }
    printf("\nForward steps done");
    Stepper_SetSteps(REVERSE,220);
    while (Stepper_GetRemainingCount() > 1) {
        printf("+");
    }
    Stepper_End();

    TRIS_COIL_A_DIRECTION = 0;
    TRIS_COIL_A_ENABLE = 0;
    TRIS_COIL_B_DIRECTION = 0;
    TRIS_COIL_B_ENABLE = 0;

    ShutDownDrive();
    COIL_A_ENABLE = 0;
    COIL_A_DIRECTION = 0;
    COIL_B_ENABLE = 0;
    COIL_B_DIRECTION = 0;
    printf("\n Turning on COIL_B_DIRECTION (PortZ-07");
    for (j=0;j<10;j++) {
        printf("o");
        DELAY();
    }
    while (1) {
        COIL_B_DIRECTION ^= 1;
        DELAY();
        printf(".");
    }
    return 0;
}

#endif

