/* 
 * File:   sampler_test.c
 * Author: mdunne
 *
 * Created on April 15, 2014, 7:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "BOARD.h"
#include "Sampler.h"
#include "timers.h"
#include "serial.h"
#include "Data_Logging.h"
#include "DataEncoding.h"
//#include <plib.h>

#ifndef USE_FAKE_DATA
#include "freescale_accel.h"
#include "freescale_mag.h"
#include "gps.h"
#include "AD.h"
#include "LED.h"
#endif

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN = OFF
#pragma config OSCIOFNC = OFF

union {
    float testFloat;
    char testChar[4];
} testUnion;

void main(void) {
    BOARD_Init();
    printf("Welcome to the Sampler Test\r\n");
    MagAccelSet_t Bob;
    printf("Size of MagAccelSet: %d %d\r\n", sizeof (MagAccelSet_t), sizeof (Bob));
    GPSSet_t is;
    printf("Size of GPSSet: %d %d\r\n", sizeof (GPSSet_t), sizeof (is));
    TempSet_t not;
    printf("Size of GPSSet: %d %d\r\n", sizeof (TempSet_t), sizeof (not));
    //    while(1);
    //    testUnion.testFloat=37.000370;
    //    printf("The Float is %f\r\n",testUnion.testFloat);
    //    printf("The Hex of it is ");
    //    int i;
    //    for(i=0;i<4;i++)
    //    {
    //        printf("%02X\t",testUnion.testChar[i]);
    //    }
    //    while (1);
    TIMERS_Init();
    InitTimer(0, 5000);
    printf("Waiting to Ensure Stabilization\r\n");
    while (IsTimerActive(0));
    printf("Waiting on Card\r\n");
    DataLogging_Init();
    DataEncoding_Init();
    LED_Init(LED_BANK1);
#ifndef USE_FAKE_DATA
    free_accel_init();
    free_mag_init();
    GPS_Init();
    AD_ANIMA_Init();
#endif
    Sampler_Init();
//    uint8_t SampleIterator;
//    for (SampleIterator = 0; SampleIterator < 20; SampleIterator++) {
//        Sampler_SetAccelMagSampleRate(Sampler_GetAccelFrequency()/2);
//        while(!IsTransmitEmpty());
//    }
//    while (1);
    Sampler_SetAccelMagSampleRate(RATE_800_HERTZ);
    while (1) {
        Sampler_Sample();
        DataLogging_Log();
        if (gpsControlData.newDatatoParse == 1) {
            processNewGpsData();
        }
    }
    //------------------------------------------------------------------
    printf("Starting the timing test\r\n");
    printf("For the next 10 seconds you should see both Sampler timers increase at set rates\r\n");
    unsigned int CurTime = Sampler_GetSecondCount();
    unsigned int accelCount = 0;
    unsigned int DesyncTime = 0;
    //unsigned int StartTime=GetTime();
    unsigned int AccelFrequency = (int) Sampler_GetAccelFrequency();
    InitTimer(0, 10 * 1000);
    while (1) {
        if (CurTime != Sampler_GetSecondCount()) {
            accelCount = Sampler_GetAccelCount();
            CurTime = Sampler_GetSecondCount();
            printf("Ref: %d   Second: %d    Fast: %d", GetTime(), CurTime, accelCount / (int) Sampler_GetAccelFrequency());
            //            PutChar(48+accelCount % (CurTime * (int) AccelFrequency));
            if (CurTime != (accelCount / (int) AccelFrequency)) {
                if (DesyncTime == 0) {
                    DesyncTime = CurTime;
                }
            }
            printf("   Desync: %d  RawTime: %d  Mod: %d  Timebase: %d\r\n", DesyncTime, accelCount, (accelCount % (CurTime * (int) AccelFrequency)), (int) AccelFrequency);
            //            if (CurTime != (accelCount / (int) AccelFrequency))
            if ((accelCount % (CurTime * (int) AccelFrequency)) != 0) {
                while (1);
            }
        }
        //        if (IsTimerExpired(0)) {
        //            break;
        //        }
    }
    while (1);
}

