/*
 * File:   BOARD.c
 * Author: Max
 *
 * Created on December 19, 2012, 2:08 PM
 */

#include <BOARD.h>
#include <xc.h>
//#include <serial.h>
#include <plib.h>
#include <peripheral/osc.h>
#include <peripheral/lock.h>
#include <LED.h>
#include <peripheral/ports.h>


//#pragma config FPLLIDIV = DIV_2
//#pragma config FCKSM = CSECMD
#define SYSTEM_CLOCK 80000000L
#define  PB_CLOCK SYSTEM_CLOCK

void BOARD_Init() {
    unsigned int dma_status;
    unsigned int int_status;
    //DEVCFG1bits.FCKSM = 0;
    //mSYSTEMUnlock(int_status, dma_status);
    //DEVCFG1bits.FCKSM = 0;
    //DEVCFG2bits.FPLLIDIV=1;
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
    SYSKEY = 0;
    SYSTEMConfig(SYSTEM_CLOCK, SYS_CFG_ALL);
    ANSELA=0;
    ANSELB=0;
    ANSELC=0;
    //OSCConfig(OSC_FRC_PLL, OSC_PLL_MULT_20, OSC_PLL_POST_1, OSC_FRC_POST_1);
    //OSCCONbits.NOSC=0x1;
    OSCSetPBDIV(OSC_PB_DIV_1);

    //mSYSTEMLock(int_status, dma_status);
    // AD1PCFG = 0xffff;

    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
    SERIAL_Init();

    //printf("This code compiled at %s on %s\r\n", __TIME__, __DATE__);
}

unsigned int BOARD_GetPBClock() {
    return PB_CLOCK;
}

//oddball function to blink LEDs and print something to the screen to determine if processor is stalled or not

void BOARD_BlinkStall() {
    LED_Init(LED_BANK1);
    int count = 0;
    while (1) {
        if (!IsTimerActive(0)) {
            // LATCbits.LATC5 ^= 1;
            //LATBbits.LATB9 ^= 1;
            InitTimer(0, 500);
            printf("TOP: %X\r\n", count);
            LED_SetBank(LED_BANK1, count);
            count++;

        }
    }
}


#ifdef BOARD_TEST

int main(void) {
    BOARD_Init();
    printf("If you can see this BOARD_Init Successfully ran\r\n");
    TRISEbits.TRISE4 = 0;

    while (1) {
        LATEbits.LATE4 ^= 1;
    }
}


#endif