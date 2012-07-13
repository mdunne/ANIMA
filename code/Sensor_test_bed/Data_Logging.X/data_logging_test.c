/*****************************************************************************
 
                Microchip Memory Disk Drive File System
 
 *****************************************************************************
 FileName:        Demonstration3.c
 Dependencies:    FSIO.h
 Processor:       PIC32
 Compiler:        C32 
 Company:         Microchip Technology, Inc.

 Software License Agreement

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PICmicro� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PICmicro Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.


   Note:  This file is included to give you a basic demonstration of how the
           functions in this library work.  Prototypes for these functions,
           along with more information about them, can be found in FSIO.h
 *****************************************************************************/

//DOM-IGNORE-BEGIN
/********************************************************************
 Change History:
  Rev            Description
  ----           -----------------------
  1.3.0   		Initial Revision to support Long File Name Format
  1.3.4         Cleaned up the unnecessary part of main() function.
 ********************************************************************/
//DOM-IGNORE-END

/*******************************************************************************
//NOTE : ENABLE MACRO "SUPPORT_LFN" IN "FSconfig.h" FILE TO WORK WITH THIS DEMO.
         THIS DEMO IS INTENDED TO SHOW THE UTF16 FILE NAME OPERATIONS
 ********************************************************************************/

#include "FSIO.h"
#include <serial.h>
#include "Data_Logging.h"
#include "timers.h"
#include <p32xxxx.h>


char sendBuffer[] = "This is test string 1";
char send2[] = "2";
char receiveBuffer[50];

#if defined (__PIC32MX__)
    #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_2         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
#endif


union d_test
{
    
    struct
    {
        unsigned short entry_one;
        unsigned short entry_two;
        unsigned short entry_three;
    };
    unsigned char multi_d [2][3];
} d_test;


int main(void) {
    FSFILE * pointer;
#if defined(SUPPORT_LFN)
    char count = 80;
#endif
    char * pointer2;
    SearchRec rec;
    unsigned char attributes;
    unsigned char size = 0, i;
    SERIAL_Init();
    // Turn on the interrupts
    INTEnableSystemMultiVectoredInt();
    TIMERS_Init();
    printf("Starting the Data Logging Test\r\n");
    int count;

    //while (!MDD_MediaDetect());
    //MEDIA_INFORMATION   *mediaInformation;
    //MDD_SDSPI_InitIO();
    //mediaInformation = MDD_SDSPI_MediaInitialize();

    //FSInit();
        //char teststring[]="hello world";
        //pointer = FSfopen ("hmm.txt", "w");
   // FSfwrite(teststring,1,11,pointer);
    //FSfclose(pointer);
    //printf("file_closed\r\n");
    //while(1);
    d_test.multi_d[0][0]=0xDE;
    d_test.multi_d[0][1]=0xAD;
    d_test.multi_d[0][2]=0xBE;
    d_test.multi_d[1][0]=0xEF;
    d_test.multi_d[1][1]=0xFE;
    d_test.multi_d[1][2]=0xED;

    //printf("%X\t%X\t%X\r\n",d_test.entry_one,d_test.entry_two,d_test.entry_three);
    //while(1);
    //SYSTEMConfigPerformance(GetSystemClock());
    //mOSCSetPBDIV(OSC_PB_DIV_2);
    //Initialize the RTCC
    //RtccInit();
    //while(RtccGetClkStat()!=RTCC_CLK_ON);// wait for the SOSC to be actually running and RTCC to have its clock source
    // could wait here at most 32ms
    //RtccOpen(0x10073000, 0x07011602, 0);
    //printf("supposedly I'm running this code now")

    // Create a file
     count= GetTime();
    DataLogging_Init();
    unsigned char test_array[510];
    test_array[0]=30;
    for (count=0;count<300;count++)
    DataLogging_Log(test_array);
    DataLogging_PrintDirectory();
    
   // char teststring[]="hello world";
 
    //FSfwrite(teststring,1,11,pointer);
        //printf("Write 21 1-byte objects from sendBuffer into the file: FAILED\r\n");
        //while (1);
    //printf("File being closed\r\n");
    DataLogging_CloseLog();
    DataLogging_DumpInterface();
    //printf("It took %d milliseconds to perform operations",GetTime()-count);
}