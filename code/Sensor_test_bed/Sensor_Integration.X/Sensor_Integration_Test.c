/* 
 * File:   Sensor_Integration_Test.c
 * Author: mdunne
 *
 * Created on July 11, 2012, 10:43 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Sensor_Integration.h"


/*
 * 
 */
int main(void) {
    INTEnableSystemMultiVectoredInt();
    
    SERIAL_Init();
    // Turn on the interrupts
    short hi=836;
    printf("\r\nStarting the Sensor Integration Test: \r\n");
    Sensor_Integration_Init();
    Sensor_Integration_SetSampleTime(250);
    //Sensor_Integration_TakeData();
    

    //this should test a few things
    //first is reading all the sensors at once
    //and then getting all that data into a usable data structure to be recorded
    while(1){
        Sensor_Integration_HandleData();
    }
}

