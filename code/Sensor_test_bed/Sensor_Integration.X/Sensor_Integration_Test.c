/* 
 * File:   Sensor_Integration_Test.c
 * Author: mdunne
 *
 * Created on July 11, 2012, 10:43 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Sensor_Integration.h"


/*
 * 
 */
#define SEVENTY_HERTZ 14
int main(void) {
    INTEnableSystemMultiVectoredInt();
    
    SERIAL_Init();
    // Turn on the interrupts
    short hi=836;
    printf("\r\nStarting the Sensor Integration Test V%f \r\n",0.9);
//    printf("\r\nStarting the Sensor Integration Test V \r\n",0.9);
    Sensor_Integration_Init();
    //Sensor_Integration_DataDump();
   // while(1);
    Sensor_Integration_SetSampleTime(SEVENTY_HERTZ);
    Sensor_Integration_SetSensorRate(APPROX_SEVENTY_HERTZ);
    Sensor_Integration_SetSensorScale(1);
    //Sensor_Integration_TakeData();
    

    //this should test a few things
    //first is reading all the sensors at once
    //and then getting all that data into a usable data structure to be recorded
    while(1){
        Sensor_Integration_HandleData();
    }
}

