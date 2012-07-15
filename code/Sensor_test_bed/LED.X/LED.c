/*
 * File:   LED.c
 * Author: Elkaim
 *
 * Created on December 18, 2011, 7:58 PM
 */

#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h>
#include "serial.h"
#include "LED.h"


/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define LED_TEST
//#define DEBUG_VERBOSE
#ifdef DEBUG_VERBOSE
    #define dbprintf(...) printf(__VA_ARGS__)
#else
    #define dbprintf(...)
#endif

#define NUMLEDBANKS 3
#define NUMLEDSPERBANK 4
#define BANK2OFFSET 4
#define BANK3OFFSET 8
#define FULLBANK 0x0F
#define NOPCOUNT 120000

#define LED_SetPinOutput(i) *LED_TRISCLR[i] = LED_bitsMap[i]
#define LED_SetPinInput(i) *LED_TRISSET[i] = LED_bitsMap[i];
#define LED_On(i) *LED_LATCLR[i] = LED_bitsMap[i];
#define LED_Off(i) *LED_LATSET[i] = LED_bitsMap[i];
#define LED_Toggle(i) *LED_LATINV[i] = LED_bitsMap[i];

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
static union {
    struct {
        unsigned int one_on : 1;
        unsigned int two_on : 1;
        unsigned int three_on : 1;
        unsigned int led_on : 1;
        unsigned :4;
    };
    unsigned char c;
} ledStatus = { .c = 0x00 };


static volatile unsigned int * const LED_TRISCLR[] = {&TRISDCLR, &TRISDCLR, &TRISECLR, &TRISECLR,
                                             &TRISGCLR, &TRISDCLR, &TRISGCLR, &TRISFCLR,
                                             &TRISGCLR, &TRISFCLR, &TRISFCLR, &TRISBCLR};

static volatile unsigned int * const LED_TRISSET[] = {&TRISDSET, &TRISDSET, &TRISESET, &TRISESET,
                                             &TRISGSET, &TRISDSET, &TRISGSET, &TRISFSET,
                                             &TRISGSET, &TRISFSET, &TRISFSET, &TRISBSET};

static volatile unsigned int * const LED_LATCLR[] = {&LATDCLR, &LATDCLR, &LATECLR, &LATECLR,
                                            &LATGCLR, &LATDCLR, &LATGCLR, &LATFCLR,
                                            &LATGCLR, &LATFCLR, &LATFCLR, &LATBCLR};

static volatile unsigned int * const LED_LATSET[] = {&LATDSET, &LATDSET, &LATESET, &LATESET,
                                            &LATGSET, &LATDSET, &LATGSET, &LATFSET,
                                            &LATGSET, &LATFSET, &LATFSET, &LATBSET};

static volatile unsigned int * const LED_LATINV[] = {&LATDINV, &LATDINV, &LATEINV, &LATEINV,
                                            &LATGINV, &LATDINV, &LATGINV, &LATFINV,
                                            &LATGINV, &LATFINV, &LATFINV, &LATBINV};

#ifdef JP_SPI_MASTER
static unsigned short int LED_bitsMap[]={BIT_9, BIT_2, BIT_7, BIT_6,
                                         BIT_8, BIT_7, BIT_7, BIT_6,
                                         BIT_6, BIT_4, BIT_5, BIT_0};
#else
static unsigned short int LED_bitsMap[]={BIT_5, BIT_3, BIT_11, BIT_6,
                                         BIT_7, BIT_8, BIT_7, BIT_6,
                                         BIT_6, BIT_4, BIT_5, BIT_0};
#endif

/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/

char LED_SetFullState(unsigned short int pattern);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
 Function: LED_Init

 Parameters
     banks: an unsigned char with a 1 in each position to set the bank as an LED
            bank, should be a bitwise OR of the #define'd LED_BANKx values.

 Returns
     char: SUCCESS or ERROR

 Description
    Initializes the LED subsystem, sets each pin in the bank as a digital output
    and turns the LED on.

 Notes: J3 SPI Jumpers should be set in MASTER position.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_Init(unsigned char banks)
{
    char i;
    dbprintf("\nInitializing LED subsystem");
    dbprintf("\nNote that SPI jumpers should be set into MASTER position");
    dbprintf("\nand that the LED jumpers should be installed.");
    if ((ledStatus.led_on)||(banks == 0)||(banks > 0x07)) {
        dbprintf("\nError: LED subsystem initialization failed");
        return ERROR;
    }
    ledStatus.led_on = TRUE;
    if (banks & LED_BANK1) {
        dbprintf("\nLED Bank1 enabled");
        ledStatus.one_on = TRUE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_SetPinOutput(i);
            LED_On(i);
        }
    }
    if (banks & LED_BANK2) {
        dbprintf("\nLED Bank2 enabled");
        ledStatus.two_on = TRUE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_SetPinOutput(i+BANK2OFFSET);
            LED_On(i+BANK2OFFSET);
        }
    }
    if (banks & LED_BANK3) {
        dbprintf("\nLED Bank3 enabled");
        ledStatus.three_on = TRUE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_SetPinOutput(i+BANK3OFFSET);
            LED_On(i+BANK3OFFSET);
        }
    }
    dbprintf("\nLED Subsystem Enabled");
    return SUCCESS;
}

/****************************************************************************
 Function: LED_OnBank

 Parameters
     bank: one of the #define'd LED_BANKx values.
     pattern: char, which LEDs to turn on.

 Returns
     char: SUCCESS or ERROR

 Description
     Forces the LEDs in (bank) to ON for each bit that is high in the pattern.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_OnBank(unsigned char bank, unsigned char pattern)
{
    char i;
    pattern &= FULLBANK;
    if (ledStatus.led_on == FALSE) return ERROR;
    if ((bank & LED_BANK1)&&(ledStatus.one_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_On(i);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK2)&&(ledStatus.two_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_On(i+BANK2OFFSET);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK3)&&(ledStatus.three_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_On(i+BANK3OFFSET);
        }
        return SUCCESS;
    }
    return ERROR;
}

/****************************************************************************
 Function: LED_OffBank

 Parameters
     bank: one of the #define'd LED_BANKx values.
     pattern: char, which LEDs to turn off.

 Returns
     char: SUCCESS or ERROR

 Description
     Forces the LEDs in (bank) to off for each bit that is high in the pattern.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_OffBank(unsigned char bank, unsigned char pattern)
{
    char i;
    pattern &= FULLBANK;
    if (ledStatus.led_on == FALSE) return ERROR;
    if ((bank & LED_BANK1)&&(ledStatus.one_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Off(i);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK2)&&(ledStatus.two_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Off(i+BANK2OFFSET);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK3)&&(ledStatus.three_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Off(i+BANK3OFFSET);
        }
        return SUCCESS;
    }
    return ERROR;    
}

/****************************************************************************
 Function: LED_InvertBank

 Parameters
     bank: one of the #define'd LED_BANKx values.
     pattern: char, which LEDs to toggle.

 Returns
     char: SUCCESS or ERROR

 Description
     Forces the LEDs in (bank) to toggle for each bit that is high in the pattern.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_InvertBank(unsigned char bank, unsigned char pattern)
{
    char i;
    pattern &= FULLBANK;
    if (ledStatus.led_on == FALSE) return ERROR;
    if ((bank & LED_BANK1)&&(ledStatus.one_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Toggle(i);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK2)&&(ledStatus.two_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Toggle(i+BANK2OFFSET);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK3)&&(ledStatus.three_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) LED_Toggle(i+BANK3OFFSET);
        }
        return SUCCESS;
    }
    return ERROR;
}

/****************************************************************************
 Function: LED_SetBank

 Parameters
     bank: one of the #define'd LED_BANKx values.
     pattern: char, sets LEDs on (1) or off (0) as in the pattern.

 Returns
     char: SUCCESS or ERROR

 Description
     Forces the LEDs in (bank) to on (1) or off (0) to match the pattern.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_SetBank(unsigned char bank, unsigned char pattern)
{
    char i;
    pattern &= FULLBANK;
    if (ledStatus.led_on == FALSE) return ERROR;
    if ((bank & LED_BANK1)&&(ledStatus.one_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) {
                LED_On(i);
            } else LED_Off(i);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK2)&&(ledStatus.two_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) {
                LED_On(i+BANK2OFFSET);
            } else LED_Off(i+BANK2OFFSET);
        }
        return SUCCESS;
    }
    if ((bank & LED_BANK3)&&(ledStatus.three_on)) {
        for (i=0;i<NUMLEDSPERBANK;i++) {
            if (pattern & (1<<i)) {
                LED_On(i+BANK3OFFSET);
            } else LED_Off(i+BANK3OFFSET);
        }
        return SUCCESS;
    }
    return ERROR;
}

/****************************************************************************
 Function: LED_SetFullState

 Parameters
     pattern: uint16, pattern to set all LEDs.

 Returns
     char: SUCCESS or ERROR

 Description
     Like LED_SetBank above, but treats all three banks as one contiguous bank
     from 0 to 11, sets each LED on (1) or off (0) to match the pattern.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_SetFullState(unsigned short int pattern)
{
    char i;
    if ((ledStatus.led_on == FALSE)||(pattern > 0xFFF)) return ERROR;
    for(i = 0; i < NUMLEDSPERBANK; i++) {
        if (ledStatus.one_on) {
            if (pattern & (1<<i)) {
                LED_On(i);
            } else LED_Off(i);
        }
    }
    for(i = 0; i < NUMLEDSPERBANK; i++) {
        if (ledStatus.two_on) {
            if (pattern & (1<<(i+BANK2OFFSET))) {
                LED_On(i+BANK2OFFSET);
            } else LED_Off(i+BANK2OFFSET);
        }
    }
    for(i = 0; i < NUMLEDSPERBANK; i++) {
        if (ledStatus.three_on) {
            if (pattern & (1<<(i+BANK3OFFSET))) {
                LED_On(i+BANK3OFFSET);
            } else LED_Off(i+BANK3OFFSET);
        }
    }
    return SUCCESS;
}

/****************************************************************************
 Function: LED_End

 Parameters: none.

 Returns
     char: SUCCESS or ERROR

 Description
     Ends the LED subsystem, turns active LED pins into inputs and turns LEDs off.

 Notes: none.

 Author: Gabriel Hugh Elkaim, 2011.12.25 01:16
 ****************************************************************************/
char LED_End(void)
{
    char i;
    dbprintf("\nShutting down the LED subsystem");
    if (!ledStatus.led_on) {
        dbprintf("\nERROR: System not initialized");
        return ERROR;
    }
    if (ledStatus.one_on) { // shut down bank one
        dbprintf("\nShutting down bank one");
        ledStatus.one_on = FALSE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_Off(i);
            LED_SetPinInput(i);
        }
    }
    if (ledStatus.two_on) { // shut down bank two
        dbprintf("\nShutting down bank two");
        ledStatus.two_on = FALSE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_Off(i+BANK2OFFSET);
            LED_SetPinInput(i+BANK2OFFSET);
        }
    }
    if (ledStatus.three_on) { // shut down bank one
        dbprintf("\nShutting down bank three");
        ledStatus.three_on = FALSE;
        for (i = 0; i < NUMLEDSPERBANK; i++) {
            LED_Off(i+BANK3OFFSET);
            LED_SetPinInput(i+BANK3OFFSET);
        }
    }
    ledStatus.led_on = FALSE;
    return SUCCESS;
}

/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef LED_TEST

#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
int main(void) {
    int i, j, k, count;
    unsigned char pat;
    SERIAL_Init();
    AD1PCFG = 0xFF;
    INTEnableSystemMultiVectoredInt();


    dbprintf("\nLED Module Unit Test\n\n");
    LED_Init(LED_BANK1);

    for(count=0; count<10; count++) {
        dbprintf("\nTesting LED_OnBank");
        for(j=0;j<NUMLEDBANKS;j++) {
            LED_OnBank((1<<j),0x0F);
        }
        DELAY();
        dbprintf("\nTesting LED OffBank");
        for(j=0;j<NUMLEDBANKS;j++) {
            LED_OffBank((1<<j),0x0F);
        }
        DELAY();
        LED_OnBank(LED_BANK1,0x0F);
        DELAY();
        LED_OffBank(LED_BANK1,0x0F);
        LED_OnBank(LED_BANK2,0x0F);
        DELAY();
        LED_OffBank(LED_BANK2,0x0F);
        LED_OnBank(LED_BANK3,0x0F);
        DELAY();
        LED_OffBank(LED_BANK3,0x0F);
        LED_OnBank(LED_BANK2,0x0F);
        DELAY();
        LED_OffBank(LED_BANK2,0x0F);
        LED_OnBank(LED_BANK1,0x0F);
        DELAY();
        LED_OffBank(LED_BANK1,0x0F);
        DELAY();
        LED_OnBank(LED_BANK1,0x01);
        LED_OnBank(LED_BANK2,0x01);
        LED_OnBank(LED_BANK3,0x01);
        DELAY();
        dbprintf("\nTesting LED_InvertBank");
        for(k=0;k<3;k++) {
            for(j=0;j<NUMLEDBANKS;j++) {
                LED_InvertBank((1<<j),(0x03<<k));
            }
            DELAY();
        }
        for(k=0;k<3;k++) {
            for(j=0;j<NUMLEDBANKS;j++) {
                LED_InvertBank((1<<j),(0x0C>>k));
            }
            DELAY();
        }
        dbprintf("\nTesting LED_SetFullState");
        LED_SetFullState(0x00);
        DELAY();
        for(j=0;j<12;j++) {
            LED_SetFullState(1<<j);
            DELAY();
        }
        for (j=0;j<12;j++) {
            LED_SetFullState(0x800 >> j);
            DELAY();
        }
        dbprintf("\nTesting LED_SetBank");
        pat = 0x05;
        for(k=0;k<4;k++) {
            for(j=0;j<NUMLEDBANKS;j++) {
                LED_SetBank((1<<j),pat);
                pat ^= 0x0F;
            }
            DELAY();
        }
    }

    LED_End();
    return 0;
}
#endif