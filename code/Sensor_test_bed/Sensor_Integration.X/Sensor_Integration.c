#include <Data_Logging.h>

#include <p32xxxx.h>
#include <stdio.h>

#include "serial.h"
#include "Sensor_Integration.h"
#include "LED.h"
#include "timers.h"
#include "freescale_accel.h"
#include "bosch_accel.h"
#include "freescale_mag.h"
#include "honeywell_mag.h"
#include "st_compass.h"
#include "gps.h"
#include "Data_Logging.h"
#include "I2C_Driver.h"

//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
    #define dbprintf(...) printf(__VA_ARGS__)
#else
    #define dbprintf(...)
#endif
#define STARTUP_DELAY 3000

#define ONEHUNDREDKILOHERTZ_I2C 100000
#define FOURHUNDREDKILOHERTZ_I2C 400000
#define DATA_TIMER 5


#define I2C_BUS_SPEED FOURHUNDREDKILOHERTZ_I2C

#define SetLedState(i) LED_SetBank(LED_BANK1,i)

tSensorData SensorData;
static unsigned char curDataSet;
static int SampleTime;

void Sensor_Integration_PrintData(void);

enum {
    WARM_UP,
    FREESCALE_ACCEL_INIT,
    BOSCH_ACCELEROMETER_INIT,
    FREESCALE_MAG_INIT,
    HONEYWELL_MAG_INIT,
    ST_COMPASS_INIT,
    GPS_INIT,
    DATA_LOGGING_INIT,
    ALL_SYSTEMS_INITED,
    WAITING_FOR_POINT,
    TAKING_DATA


} LED_States;

void Sensor_Integration_Init() {
    //printf("Size of SensorData: %d\r\n",sizeof(SensorData));
    //SensorData.SensorData.ID = 0xDEAD;
    //printf("first two bytes: %X %X\r\n", SensorData.SectorAccess[0], SensorData.SectorAccess[1]);

    //we need to initialize all the sensors and use the LED to show status


    curDataSet = 0;


    //first init timer libary and LED library for debug along with the I2C Driver
    TIMERS_Init();
    LED_Init(LED_BANK1);
    SetLedState(WARM_UP);
    unsigned int I2C_Clock;
    I2C_Clock = I2C_Init(I2C_BUS_SPEED);
    dbprintf("I2C Clock set to %d\r\n", I2C_Clock);

    dbprintf("Waiting %d seconds to allow all devices to start up completly\r\n", STARTUP_DELAY / 1000);

    InitTimer(0, STARTUP_DELAY);
    while (!IsTimerExpired(0));


    SetLedState(FREESCALE_ACCEL_INIT);
    dbprintf("Initiating Initialization of freeScale Accelerometer\r\n");
    free_accel_init();
    dbprintf("Freescale Accelerometer Initialized\r\n");


    SetLedState(BOSCH_ACCELEROMETER_INIT);
    dbprintf("Initiating Initialization of Bosch Accelerometer\r\n");
    bosch_accel_init();
    dbprintf("Bosch Accelerometer Initialized\r\n");


    SetLedState(FREESCALE_MAG_INIT);
    dbprintf("Initiating Initialization of freeScale Magnetometer\r\n");
    free_mag_init();
    dbprintf("Freescale Magnetometer Initialized\r\n");

    SetLedState(HONEYWELL_MAG_INIT);
    dbprintf("Initiating Initialization of Honeywell Magnetometer\r\n");
    honey_mag_init();
    dbprintf("Honeywell Magnetometer Initialized\r\n");

    SetLedState(ST_COMPASS_INIT);
    dbprintf("Initiating Initialization of ST Compass\r\n");
    st_compass_init();
    st_accel_SetRate(ST_ACCEL_100HERTZ);
    dbprintf("ST Compass Initialized\r\n");

    SetLedState(GPS_INIT);
    dbprintf("Initiating Initialization of GPS\r\n");
    GPS_Init();
    dbprintf("GPS Initialized\r\n");

    SetLedState(DATA_LOGGING_INIT);
    dbprintf("Initiating Initialization of Data Logging\r\n");
    DataLogging_Init();
    dbprintf("Data Logging Initialized\r\n");


}


//record one data point from each of the sensors and add it to the struct
//will be wrapped within another which will record it to the card when needed

void Sensor_Integration_TakeData(void) {
    int curTime = GetTime();
    //dbprintf("Start of TakeData: %d\r\n", GetTime());
    short AxisData[3];
    SensorData.SensorData.Entries[curDataSet].FreeAccel.X = free_GetXData();
    SensorData.SensorData.Entries[curDataSet].FreeAccel.Y = free_GetYData();
    SensorData.SensorData.Entries[curDataSet].FreeAccel.Z = free_GetZData();

    bosch_GetTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].BoschAccel.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].BoschAccel.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].BoschAccel.Z = AxisData[2];

    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.X = st_Get_AccelXData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Y = st_Get_AccelYData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Z = st_Get_AccelZData();

    free_GetTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].FreeMag.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].FreeMag.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].FreeMag.Z = AxisData[2];

    SensorData.SensorData.Entries[curDataSet].HoneyMag.X = honey_mag_GetXData();
    SensorData.SensorData.Entries[curDataSet].HoneyMag.Y = honey_mag_GetXData();
    SensorData.SensorData.Entries[curDataSet].HoneyMag.Z = honey_mag_GetXData();

    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.X = st_Get_MagXData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Y = st_Get_MagYData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Z = st_Get_MagZData();

    SensorData.SensorData.Entries[curDataSet].GPS.lat = gpsControlData.lat;
    SensorData.SensorData.Entries[curDataSet].GPS.lon = gpsControlData.lon;
    SensorData.SensorData.Entries[curDataSet].GPS.height = gpsControlData.height;
    SensorData.SensorData.Entries[curDataSet].GPS.Date.year = gpsControlData.year;
    SensorData.SensorData.Entries[curDataSet].GPS.Date.month = gpsControlData.month;
    SensorData.SensorData.Entries[curDataSet].GPS.Date.day = gpsControlData.day;
    SensorData.SensorData.Entries[curDataSet].GPS.Time.hour = gpsControlData.hour;
    SensorData.SensorData.Entries[curDataSet].GPS.Time.minute = gpsControlData.min;
    SensorData.SensorData.Entries[curDataSet].GPS.Time.second = gpsControlData.sec;
    SensorData.SensorData.Entries[curDataSet].GPS.Time.millisecond = gpsControlData.millisec;
    SensorData.SensorData.Entries[curDataSet].GPS.fix = gpsControlData.fix;
    dbprintf("Elapsed time to take data: %d\r\n", GetTime() - curTime);
    curDataSet++;
    //Sensor_Integration_PrintData();
}


//debug function to print out all data in the current struct

void Sensor_Integration_PrintData(void) {
    printf("printing DataSet %d\r\n", curDataSet);
    printf("FreeAccel--->(%5d,%5d,%5d) ", SensorData.SensorData.Entries[curDataSet].FreeAccel.X, SensorData.SensorData.Entries[curDataSet].FreeAccel.Y, SensorData.SensorData.Entries[curDataSet].FreeAccel.Z);
    printf("BoschAccel-->(%5d,%5d,%5d) ", SensorData.SensorData.Entries[curDataSet].BoschAccel.X, SensorData.SensorData.Entries[curDataSet].BoschAccel.Y, SensorData.SensorData.Entries[curDataSet].BoschAccel.Z);
    printf("STCompAccel->(%5d,%5d,%5d)\r\n", SensorData.SensorData.Entries[curDataSet].STCompass_Accel.X, SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Y, SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Z);
    printf("FreeMag----->(%5d,%5d,%5d) ", SensorData.SensorData.Entries[curDataSet].FreeMag.X, SensorData.SensorData.Entries[curDataSet].FreeMag.Y, SensorData.SensorData.Entries[curDataSet].FreeMag.Z);
    printf("HoneyMag---->(%5d,%5d,%5d) ", SensorData.SensorData.Entries[curDataSet].HoneyMag.X, SensorData.SensorData.Entries[curDataSet].HoneyMag.Y, SensorData.SensorData.Entries[curDataSet].HoneyMag.Z);
    printf("STMag------->(%5d,%5d,%5d)\r\n", SensorData.SensorData.Entries[curDataSet].STCompass_Mag.X, SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Y, SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Z);
    //printf("GPS->lat\r\n");



}

//first timer
//we check to see if DATA_TIMER is ACTIVE and if not start the time and drop out
//if timer is active

enum {
    INIT_TIME,
    WAITING
} DATA_STATES;

void Sensor_Integration_HandleData(void) {

    static unsigned char curState = INIT_TIME;
    if (gpsControlData.newDatatoParse == 1) {
        processNewGpsData();
        gpsControlData.newDatatoParse;
    }
    switch (curState) {
        case INIT_TIME:
            InitTimer(DATA_TIMER, SampleTime);
            curState = WAITING;
            break;
        case WAITING:
            if (IsTimerExpired(DATA_TIMER)) {
                SetLedState(TAKING_DATA);
                dbprintf("Time Expired at %d, Taking datapoint set\r\n",GetTime());
                Sensor_Integration_TakeData();
                if (curDataSet >= DATA_POINTS) {
                    DataLogging_Log(SensorData.SectorAccess);
                    curDataSet = 0;
                }
                InitTimer(DATA_TIMER, SampleTime);
                SetLedState(WAITING_FOR_POINT);

            }
            break;
    }
}



void Sensor_Integration_SetSampleTime(unsigned int milliseconds)
{
    SampleTime=milliseconds;
}