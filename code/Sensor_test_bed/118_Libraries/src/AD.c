/*
 * File:   AD.c
 * Author: mdunne
 *
 * Created on November 22, 2011, 8:57 AM
 */

#include <p32xxxx.h>
#include "AD.h"

#include <peripheral/adc10.h>
#include <peripheral/ports.h>
#include <GenericTypeDefs.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define NUM_AD_PINS 13
#define NUM_AD_PINS_UNO 16


/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/
static unsigned int AD1PCFG_MASKS[NUM_AD_PINS] = {ENABLE_AN2_ANA, ENABLE_AN3_ANA,
    ENABLE_AN4_ANA, ENABLE_AN5_ANA, ENABLE_AN8_ANA, ENABLE_AN9_ANA,
    ENABLE_AN11_ANA, ENABLE_AN10_ANA, ENABLE_AN13_ANA, ENABLE_AN12_ANA,
    ENABLE_AN15_ANA, ENABLE_AN14_ANA, ENABLE_AN1_ANA};

static unsigned int AD1CSSL_MASKS[NUM_AD_PINS] = {SKIP_SCAN_AN2, SKIP_SCAN_AN3,
    SKIP_SCAN_AN4, SKIP_SCAN_AN5, SKIP_SCAN_AN8, SKIP_SCAN_AN9,
    SKIP_SCAN_AN11, SKIP_SCAN_AN10, SKIP_SCAN_AN13, SKIP_SCAN_AN12,
    SKIP_SCAN_AN15, SKIP_SCAN_AN14, SKIP_SCAN_AN1};

static unsigned int AD1PCFG_POS[NUM_AD_PINS] = {_AD1PCFG_PCFG2_POSITION, _AD1PCFG_PCFG3_POSITION,
    _AD1PCFG_PCFG4_POSITION, _AD1PCFG_PCFG5_POSITION, _AD1PCFG_PCFG8_POSITION, _AD1PCFG_PCFG9_POSITION,
    _AD1PCFG_PCFG11_POSITION, _AD1PCFG_PCFG10_POSITION, _AD1PCFG_PCFG13_POSITION, _AD1PCFG_PCFG12_POSITION,
    _AD1PCFG_PCFG15_POSITION, _AD1PCFG_PCFG14_POSITION, _AD1PCFG_PCFG1_POSITION};

static unsigned int UsedPins;
static unsigned int PinCount;
static unsigned int ADValues[NUM_AD_PINS];
static int PortMapping[NUM_AD_PINS];

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/
/****************************************************************************
 Function
     AD_Init

 Parameters
    Pins, used #defined AD_PORTxxx OR'd together for each A/D Pin

 Returns
     SUCCESS or ERROR

 Description
    Initializes the A/D pins requested into analog inputs and configures the A/D subsystem.
    It then generates the mapping for correctly reading the pin and then starts the A/D system.
 Notes
     None.

 Author
 Max Dunne, 2011.12.10
 ****************************************************************************/
unsigned char AD_Init(unsigned int Pins) {
    unsigned int cssl = 0;
    unsigned int pcfg = 0;
    unsigned char CurPin = 0;
    unsigned int PinCount2 = 0x00;
    int ADMapping[NUM_AD_PINS_UNO];

    if ((Pins == 0) || (Pins > 0x1FFF)) {
        return ERROR;
    }
    for (CurPin = 0; CurPin < NUM_AD_PINS_UNO; CurPin++) {
        ADMapping[CurPin] = -1;
    }
    for (CurPin = 0; CurPin < NUM_AD_PINS; CurPin++) {
        PortMapping[CurPin] = -1;
        if ((Pins & (1 << CurPin)) != 0) {
            cssl |= AD1CSSL_MASKS[CurPin];
            pcfg |= AD1PCFG_MASKS[CurPin];
            ADMapping[AD1PCFG_POS[CurPin]] = CurPin;
            PinCount++;
        }
    }
    for (CurPin = 0; CurPin < NUM_AD_PINS_UNO; CurPin++) {
        if (ADMapping[CurPin] != -1) {
            PortMapping[ADMapping[CurPin]] = PinCount2;
            PinCount2++;
        }
    }
    UsedPins = Pins;
    cssl = ~cssl;
    OpenADC10(ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON, ADC_VREF_AVDD_AVSS
            | ADC_SCAN_ON | ((PinCount - 1) << _AD1CON2_SMPI_POSITION) | ADC_BUF_16, ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_32Tcy | ADC_CONV_CLK_PB, pcfg, cssl);
    ConfigIntADC10(ADC_INT_ON | ADC_INT_PRI_1 | ADC_INT_SUB_PRI_3);

    EnableADC10();
    return SUCCESS;
}



/****************************************************************************
 Function
    ADCIntHandler

 Parameters
    None

 Returns
     None

 Description
    Interrupt Handler for A/D. Reads all used pins into buffer.
 Notes
     None.

 Author
 Max Dunne, 2011.12.10
 ****************************************************************************/
void __ISR(_ADC_VECTOR, ipl1) ADCIntHandler(void) {
    mAD1ClearIntFlag();
    unsigned char CurPin = 0;
    for (CurPin = 0; CurPin <= PinCount; CurPin++) {
        ADValues[CurPin] = ReadADC10(CurPin);
    }
}


/****************************************************************************
 Function
    ReadADPin

 Parameters
    Pin, used #defined AD_PORTxxx to select pin

 Returns
    10-bit AD Value or ERROR

 Description
    Reads current value from buffer for given pin
 Notes
    PORTV3 no longer works if all pins are enabled as A/D

 Author
 Max Dunne, 2011.12.10
 ****************************************************************************/
unsigned int ReadADPin(unsigned int Pin) {
    if (!(UsedPins & Pin)) {
        return ERROR;
    }
    unsigned char TranslatedPin = 0;
    while (Pin > 1) {

        Pin >>= 1;
        TranslatedPin++;
    }
    return ADValues[PortMapping[TranslatedPin]];
}

/****************************************************************************
 Function
    AD_End

 Parameters
    None

 Returns
     None

 Description
    disables the A/D subsystem and release the pins used
 Notes
     None.

 Author
 Max Dunne, 2011.12.10
 ****************************************************************************/
void AD_End(void) {
    UsedPins = 0;
    PinCount = 0;
    CloseADC10();
    AD1PCFG = 0xFF;
}



#define AD_TEST
#ifdef AD_TEST
//pragmas are to set up the clock the same as it will be when using the ds30, once ds30 is up they should not be invoked
#pragma config FPLLIDIV 	= DIV_2		//PLL Input Divider
#pragma config FPLLMUL 		= MUL_20	//PLL Multiplier
#pragma config FPLLODIV 	= DIV_1 	//System PLL Output Clock Divid
#pragma config FNOSC 		= PRIPLL	//Oscillator Selection Bits
#pragma config FSOSCEN 		= OFF		//Secondary Oscillator Enable
#pragma config IESO 		= OFF		//Internal/External Switch O
#pragma config POSCMOD 		= XT		//Primary Oscillator Configuration
#pragma config OSCIOFNC 	= OFF		//CLKO Output Signal Active on the OSCO Pin
#pragma config FPBDIV 		= DIV_2		//Peripheral Clock Divisor
#pragma config FCKSM 		= CSECMD	//Clock Switching and Monitor Selection
#pragma config WDTPS 		= PS1		//Watchdog Timer Postscaler
#pragma config FWDTEN		= OFF		//Watchdog Timer Enable
#pragma config ICESEL		= ICS_PGx2	//ICE/ICD Comm Channel Select
#pragma config PWP 			= OFF		//Program Flash Write Protect
#pragma config BWP 			= OFF		//Boot Flash Write Protect bit
#pragma config CP 			= OFF		//Code Protect


//#pragma FPBDIV                  = DIV_2  //Peripheral clock, unsure why it is not included in the ds30 settings

#include <p32xxxx.h>
#include "serial.h"
#include <GenericTypeDefs.h>
#include "AD.h"

//#include <plib.h>
#include <plib.h>
#define TIMES_TO_READ 4000

int main(void) {
    unsigned int wait = 0;
    int readcount = 0;
    SERIAL_Init();
    INTEnableSystemMultiVectoredInt();
    mJTAGPortEnable(0);
    printf("\r\nUno A/D Test Harness\r\nThis will initialize all A/D pins and read them %d times", TIMES_TO_READ);
    printf("Value of pcfg before test: %X",AD1PCFG);


    AD_Init(AD_PORTV3 | AD_PORTV4 | AD_PORTV5 | AD_PORTV6 | AD_PORTV7 | AD_PORTV8 | AD_PORTW3 | AD_PORTW4 | AD_PORTW5 | AD_PORTW6 | AD_PORTW7 | AD_PORTW8 | BAT_VOLTAGE);
    char numtoread = 13;
    unsigned char cur = 0;
    while (readcount <= TIMES_TO_READ) {
        for (wait = 0; wait <= 100000; wait++)
            asm("nop");
        printf("\r\n");
        for (cur = 0; cur < numtoread; cur++) {
            printf("%d\t", ReadADPin(1 << cur));
        }
        printf("\r\n");
        readcount++;
    }
    printf("Done Reading Them\r\n");
    AD_End();
    printf("Value of pcfg after test: %X",AD1PCFG);
    return 0;
}
#endif