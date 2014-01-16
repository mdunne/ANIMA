/* 
 * File:   main.c
 * Author: mdunne
 *
 * Created on June 28, 2013, 11:30 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <BOARD.h>

#include "serial.h"
#include "timers.h"
#include <plib.h>
#include <peripheral/int.h>
#include <LED.h>

//#pragma config FRCDIV = 0
//#pragma config FPLLIDIV 	= DIV_2		//PLL Input Divider
//#pragma config FPLLMUL 		= MUL_20	//PLL Multiplier
//#pragma config FPLLODIV 	= DIV_1 	//System PLL Output Clock Divid
//#pragma config FNOSC 		= FRCPLL	//Oscillator Selection Bits
//#pragma config FSOSCEN 		= OFF		//Secondary Oscillator Enable
//#pragma config IESO 		= OFF		//Internal/External Switch O
//#pragma config POSCMOD 		= HS		//Primary Oscillator Configuration
//#pragma config OSCIOFNC 	= OFF		//CLKO Output Signal Active on the OSCO Pin
//#pragma config FPBDIV 		= DIV_2		//Peripheral Clock Divisor
//#pragma config FCKSM 		= CSECMD	//Clock Switching and Monitor Selection
//#pragma config WDTPS 		= PS1		//Watchdog Timer Postscaler
//#pragma config FWDTEN		= OFF		//Watchdog Timer Enable
//#pragma config ICESEL		= ICS_PGx2	//ICE/ICD Comm Channel Select
//#pragma config PWP 			= OFF		//Program Flash Write Protect
//#pragma config BWP 			= OFF		//Boot Flash Write Protect bit
//#pragma config CP 			= OFF		//Code Protect
//#pragma config FCKSM = CSECMD

//#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_2, FWDTEN = OFF
//#pragma config POSCMOD = HS, FNOSC = FRCPLL, FPBDIV = DIV_1, IESO = OFF
//#pragma config FNOSC=FRCPLL
//#pragma config WDTPS = PS1, OSCIOFNC = OFF, FCKSM = CSECME

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF

int main(void) {
    //DEVCFG1bits.FCKSM = 0;
    int c = 0;
    // for (c = 0; c < 100000; c++) {
    //     Nop();
    //  }

    BOARD_Init();

    //INTEnableSystemMultiVectoredInt();
    //SERIAL_Init();
    //DEVCFG1bits.FCKSM
    //TIMERS_Init();
    //    SYSKEY = 0;
    //    SYSKEY = 0xAA996655;
    //    SYSKEY = 0x556699AA;
    //    OSCCONbits.FRCDIV = 0b111;
    //    OSCConfig(OSC_FRC_PLL, OSC_PLL_MULT_20, OSC_PLL_POST_1, OSC_PB_DIV_1);



    LED_Init(LED_BANK1);
    LED_SetBank(LED_BANK1,~2);
    //while(1);
    //SERIAL_Init();
    //LATBbits.LATB7 = 1;
    TIMERS_Init();
    unsigned char count=0;
    //while (1) {
    // LATCbits.LATC3 ^= 1;
    //}

    
    printf("Hello World\r\n");
    while (1) {
        if (!IsTimerActive(0)) {
            // LATCbits.LATC5 ^= 1;
            //LATBbits.LATB9 ^= 1;
            InitTimer(0, 500);
            printf("TOP: %X\r\n",count);
            LED_SetBank(LED_BANK1,count);
            count++;
            
        }
        if (!IsReceiveEmpty()) {
            //LATBbits.LATB8 ^= 1;
            printf("%c", GetChar());
        }
    }

    while (1);
}

