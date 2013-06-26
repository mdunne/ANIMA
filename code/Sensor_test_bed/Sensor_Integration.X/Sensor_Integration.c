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

#define DEBUG_VERBOSE

//#define BMA180_PRESENT



#define STARTUP_DELAY 3000
#define GPS_FIX 0b0111
#define GPS_NO_FIX 0b1111

#define ONEHUNDREDKILOHERTZ_I2C 100000
#define FOURHUNDREDKILOHERTZ_I2C 400000
#define EIGHTHUNDERDKILOHERTZ_I2C 800000
#define DATA_TIMER 5


#define I2C_BUS_SPEED FOURHUNDREDKILOHERTZ_I2C
//#define I2C_BUS_SPEED EIGHTHUNDERDKILOHERTZ_I2C

#define SetLedState(i) LED_SetBank(LED_BANK1,i);

tSensorData SensorData;
static unsigned char curDataSet;
static int SampleTime;
static short AxisData[3];
static unsigned char GPS_Fix;



void Sensor_Integration_PrintData(void);

enum {
    WARM_UP = 0,
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
    //    GPS_Fix=1;
    //    //while(1)
    //    //{
    //        SetLedState(GPS_Fix);
    //        printf("%X\r\n",GPS_Fix);
    //        GPS_Fix<<=1;
    //        InitTimer(0, 1000);
    //        while (!IsTimerExpired(0));
    //        if(GPS_Fix>8)
    //            GPS_Fix=1;
    //    //}
    //    while (1) {
    //        GPS_Fix = GPS_FIX;
    //        SetLedState(TAKING_DATA & GPS_Fix);
    //        InitTimer(0, 1000);
    //        while (!IsTimerExpired(0));
    //        GPS_Fix = GPS_NO_FIX;
    //        SetLedState(TAKING_DATA & GPS_Fix);
    //        InitTimer(0, 1000);
    //        while (!IsTimerExpired(0));
    //
    //    }

    SetLedState(WARM_UP);
    unsigned int I2C_Clock;
    I2C_Clock = I2C_Init(I2C_BUS_SPEED);
#ifdef DEBUG_VERBOSE
    printf("I2C Clock set to %d\r\n", I2C_Clock);
#endif
    //printf("Waiting %d seconds to allow all devices to start up completly\r\n", STARTUP_DELAY / 1000);

   // printf("If you press 'a' during this time period the card will dump all data and hold\r\nif you press 'b' it will only dump the latest");
    InitTimer(0, STARTUP_DELAY);
   // while (!IsTimerExpired(0));
    DataLogging_Init();
    //Sensor_Integration_DataDumpWholeCard();
    //while(1);
    char inChar = 0;
    while (!IsTimerExpired(0)) {
        if (!IsReceiveEmpty()) {
            inChar = GetChar();
            if (inChar == 'a') {
                DataLogging_Init();
                //DataLogging_PrintDirectory();
                Sensor_Integration_DataDumpWholeCard();
                printf("Data has been dumped\r\n");
                while (1);
                Sensor_Integration_DataDump();


                while (1);
            }
            if (inChar == 'b') {
                DataLogging_Init();
                Sensor_Integration_DataDumpLatest();
                while (1);
            }
        }
    }



    SetLedState(FREESCALE_ACCEL_INIT);
#ifdef DEBUG_VERBOSE
    printf("Initiating Initialization of freeScale Accelerometer\r\n");
#endif

    free_accel_init();
#ifdef DEBUG_VERBOSE
    printf("Freescale Accelerometer Initialized\r\n");
#endif


    SetLedState(BOSCH_ACCELEROMETER_INIT);
#ifdef DEBUG_VERBOSE
    printf("Initiating Initialization of Bosch Accelerometer\r\n");
#endif
#ifdef BMA180_PRESENT
    bosch_accel_init();
#endif
#ifdef DEBUG_VERBOSE
    printf("Bosch Accelerometer Initialized\r\n");
#endif


    SetLedState(FREESCALE_MAG_INIT);
#ifdef DEBUG_VERBOSE
    printf("Initiating Initialization of freeScale Magnetometer\r\n");
#endif
    free_mag_init();
#ifdef DEBUG_VERBOSE
    printf("Freescale Magnetometer Initialized\r\n");
#endif

    SetLedState(HONEYWELL_MAG_INIT);
#ifdef DEBUG_VERBOSE
    printf("Freescale Magnetometer Initialized\r\n");
#endif
    honey_mag_init();
#ifdef DEBUG_VERBOSE
    printf("Honeywell Magnetometer Initialized\r\n");
#endif

    SetLedState(ST_COMPASS_INIT);
#ifdef DEBUG_VERBOSE
    printf("Initiating Initialization of ST Compass\r\n");
#endif
    st_compass_init();
    st_accel_SetRate(ST_ACCEL_100HERTZ);
#ifdef DEBUG_VERBOSE
    printf("ST Compass Initialized\r\n");
#endif

    SetLedState(GPS_INIT);
#ifdef DEBUG_VERBOSE
    printf("Initiating Initialization of GPS\r\n");
#endif
    //GPS_Init();
#ifdef DEBUG_VERBOSE
    printf("GPS Initialized Really?\r\n");
#endif

    SetLedState(DATA_LOGGING_INIT);
#ifdef DEBUG_VERBOSE
    printf("GPS Initialized Really?\r\n");
#endif
    DataLogging_Init();
#ifdef DEBUG_VERBOSE
    printf("Data Logging Initialized\r\n");
#endif
    InitTimer(0, 5000);
    while (!IsTimerExpired(0));


}


//record one data point from each of the sensors and add it to the struct
//will be wrapped within another which will record it to the card when needed

void Sensor_Integration_TakeData(void) {
    int curTime = GetTime();
#ifdef DEBUG_VERBOSE
    printf("Start of TakeData: %d\r\n", GetTime());
    printf("CurDataSet: %d", curDataSet);
#endif
    free_GetTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].FreeAccel.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].FreeAccel.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].FreeAccel.Z = AxisData[2];


#ifdef BMA180_PRESENT
    bosch_GetTriplet(AxisData);
#endif
    SensorData.SensorData.Entries[curDataSet].BoschAccel.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].BoschAccel.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].BoschAccel.Z = AxisData[2];

    //curTime=GetTime();

    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.X = st_Get_AccelXData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Y = st_Get_AccelYData();
    SensorData.SensorData.Entries[curDataSet].STCompass_Accel.Z = st_Get_AccelZData();


    free_GetTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].FreeMag.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].FreeMag.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].FreeMag.Z = AxisData[2];


    honey_GetMagTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].HoneyMag.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].HoneyMag.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].HoneyMag.Z = AxisData[2];


    st_GetMagTriplet(AxisData);
    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.X = AxisData[0];
    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Y = AxisData[1];
    SensorData.SensorData.Entries[curDataSet].STCompass_Mag.Z = AxisData[2];


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
#ifdef DEBUG_VERBOSE
    printf("Elapsed time to take data: %d\r\n", GetTime() - curTime);
#endif
    //Sensor_Integration_PrintData();
    curDataSet++;

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
    printf("time: %02d:%02d:%02d.%04d", SensorData.SensorData.Entries[curDataSet].GPS.Time.hour, SensorData.SensorData.Entries[curDataSet].GPS.Time.minute, SensorData.SensorData.Entries[curDataSet].GPS.Time.second, SensorData.SensorData.Entries[curDataSet].GPS.Time.millisecond);
    printf(" Lat: %.4f: Lon: %.4f", SensorData.SensorData.Entries[curDataSet].GPS.lat, SensorData.SensorData.Entries[curDataSet].GPS.lon);
    printf(" Height: %.4f fix: %d", SensorData.SensorData.Entries[curDataSet].GPS.height, SensorData.SensorData.Entries[curDataSet].GPS.fix);
    printf("\r\n");
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
    static unsigned int SectorCount = 0;
    if (gpsControlData.newDatatoParse == 1) {
        processNewGpsData();
        if (gpsControlData.fix > 0) {
            //turn led on here
            GPS_Fix = GPS_FIX;
        } else {
            //turn off here
            GPS_Fix = GPS_NO_FIX;
        }
        //printf("GpsData was parsed\r\n");

    }
    switch (curState) {
        case INIT_TIME:
            InitTimer(DATA_TIMER, SampleTime);
            curState = WAITING;
            break;
        case WAITING:
            if (IsTimerExpired(DATA_TIMER)) {
                SetLedState(TAKING_DATA & GPS_Fix);
                InitTimer(DATA_TIMER, SampleTime);
#ifdef DEBUG_VERBOSE
                printf("Time Expired at %d, Taking datapoint set\r\n", GetTime());
#endif
                Sensor_Integration_TakeData();
                //Sensor_Integration_PrintData();
                if (curDataSet >= DATA_POINTS) {
                    DataLogging_Log(SensorData.SectorAccess);
                    SectorCount++;
#ifdef DEBUG_VERBOSE
                    printf("\r\nSectors Used: %d\r\n", SectorCount);
#endif
                    curDataSet = 0;
                }

                SetLedState(WAITING_FOR_POINT & GPS_Fix);

            }
            break;
    }
}

void Sensor_Integration_SetSampleTime(unsigned int milliseconds) {
    SampleTime = milliseconds;
}




//only use the #defines for this, invalids are dropped out

void Sensor_Integration_SetSensorRate(unsigned int SampleRate) {
    switch (SampleRate) {
        case APPROX_SEVENTY_HERTZ:
#ifdef BMA180_PRESENT
            bosch_SetRate(BOSCH_75HERTZ);
#endif
            free_SetRate(FREE_100HERTZ);
            free_mag_SetRate(FREE_MAG_80HERTZ_16_OVERRATIO);
            honey_mag_SetRate(HONEY_RATE_75HERTZ);
            st_accel_SetRate(ST_ACCEL_100HERTZ);
            st_mag_SetRate(ST_MAG_RATE_75HERTZ);
            break;
    }
}

void Sensor_Integration_SetSensorScale(int Scale) {

    st_accel_SetScale(ST_ACCEL_2GSCALE);
    //printf("%d %d\r\n",ST_ACCEL_2GSCALE,st_accel_GetScale());
    free_SetScale(FREE_2GSCALE);
    //printf("%d %d\r\n",FREE_2GSCALE,free_GetScale());

    st_mag_SetGain(ST_MAG_GAIN_1100);
    //printf("%d %d\r\n",ST_MAG_GAIN_1100,st_mag_GetGain());
    honey_mag_SetGain(HONEY_GAIN_1090);
    //printf("%d %d\r\n",HONEY_GAIN_1090,honey_mag_GetGain());
    //while(1);

}
//will dump all the data on the card in a csv file format to the terminal

void Sensor_Integration_DataDump() {
    int NumEntries, CurEntry, CurEntrySize, CurPos, CurDataPoint;
    //first need to print the header which also establishes the data order
    printf("ID,Bosch_Accel_X,Bosch_Accel_Y,Bosch_Accel_Z,Free_Accel_X,Free_Accel_Y,Free_Accel_Z,Free_Mag_X,Free_Mag_Y,Free_Mag_Z,");
    while (!IsTransmitEmpty());
    printf("Honey_Mag_X,Honey_Mag_Y,Honey_Mag_Z,STCompass_Mag_X,STCompass_Mag_Y,STCompass_Mag_Z,STCompass_Accel_X,STCompass_Accel_Y,STCompass_Accel_Z,");
    while (!IsTransmitEmpty());
    printf("lat,lon,alt,gps_year,gps_month,gps_day,gps_hour,gps_minute,gps_second,gps_millisecond,gps_fix\r\n");
    while (!IsTransmitEmpty());
    //we don't take the last one as DataLoggingInit increments it
    NumEntries = DataLogging_NumEntries() - 1;
    for (CurEntry = 0; CurEntry < NumEntries; CurEntry++) {
        CurEntrySize = DataLogging_GetEntrySize(CurEntry);
        for (CurPos = 0; CurPos < CurEntrySize; CurPos++) {
            DataLogging_GetEntrySector(CurEntry, CurPos, SensorData.SectorAccess);
            for (CurDataPoint = 0; CurDataPoint < DATA_POINTS; CurDataPoint++) {
                printf("%d,", CurEntry);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].BoschAccel.X, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Y, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Z);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeAccel.X, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Y, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Z);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeMag.X, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Y, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Z);
                while (!IsTransmitEmpty());
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].HoneyMag.X, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Y, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Z);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Z);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Z);
                while (!IsTransmitEmpty());
                printf("%f,%f,%f,", SensorData.SensorData.Entries[CurDataPoint].GPS.lat, SensorData.SensorData.Entries[CurDataPoint].GPS.lon, SensorData.SensorData.Entries[CurDataPoint].GPS.height);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Date.year, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.month, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.day);
                printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.hour, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.minute, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.second);
                printf("%d,%d", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.millisecond, SensorData.SensorData.Entries[CurDataPoint].GPS.fix);
                printf("\r\n");
                while (!IsTransmitEmpty());
            }

        }
    }
}

void Sensor_Integration_DataDumpLatest() {
    int Entry, CurEntrySize, CurPos, CurDataPoint;
    //first need to print the header which also establishes the data order
    printf("ID,Bosch_Accel_X,Bosch_Accel_Y,Bosch_Accel_Z,Free_Accel_X,Free_Accel_Y,Free_Accel_Z,Free_Mag_X,Free_Mag_Y,Free_Mag_Z,");
    while (!IsTransmitEmpty());
    printf("Honey_Mag_X,Honey_Mag_Y,Honey_Mag_Z,STCompass_Mag_X,STCompass_Mag_Y,STCompass_Mag_Z,STCompass_Accel_X,STCompass_Accel_Y,STCompass_Accel_Z,");
    while (!IsTransmitEmpty());
    printf("lat,lon,alt,gps_year,gps_month,gps_day,gps_hour,gps_minute,gps_second,gps_millisecond,gps_fix\r\n");
    while (!IsTransmitEmpty());
    //we don't take the last one as DataLoggingInit increments it
    Entry = DataLogging_NumEntries() - 2;
    CurEntrySize = DataLogging_GetEntrySize(Entry);
    for (CurPos = 0; CurPos < CurEntrySize; CurPos++) {
        DataLogging_GetEntrySector(Entry, CurPos, SensorData.SectorAccess);
        for (CurDataPoint = 0; CurDataPoint < DATA_POINTS; CurDataPoint++) {
            printf("%d,", Entry);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].BoschAccel.X, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Y, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeAccel.X, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Y, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeMag.X, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Y, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Z);
            while (!IsTransmitEmpty());
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].HoneyMag.X, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Y, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Z);
            while (!IsTransmitEmpty());
            printf("%f,%f,%f,", SensorData.SensorData.Entries[CurDataPoint].GPS.lat, SensorData.SensorData.Entries[CurDataPoint].GPS.lon, SensorData.SensorData.Entries[CurDataPoint].GPS.height);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Date.year, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.month, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.day);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.hour, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.minute, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.second);
            printf("%d,%d", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.millisecond, SensorData.SensorData.Entries[CurDataPoint].GPS.fix);
            printf("\r\n");
            while (!IsTransmitEmpty());
        }

    }
}

void Sensor_Integration_DataDumpWholeCard(void) {
    int Entry, CurEntrySize, CurPos, CurDataPoint;
    unsigned int SectorCount = 0;
    //first need to print the header which also establishes the data order
    printf("ID,Bosch_Accel_X,Bosch_Accel_Y,Bosch_Accel_Z,Free_Accel_X,Free_Accel_Y,Free_Accel_Z,Free_Mag_X,Free_Mag_Y,Free_Mag_Z,");
    while (!IsTransmitEmpty());
    printf("Honey_Mag_X,Honey_Mag_Y,Honey_Mag_Z,STCompass_Mag_X,STCompass_Mag_Y,STCompass_Mag_Z,STCompass_Accel_X,STCompass_Accel_Y,STCompass_Accel_Z,");
    while (!IsTransmitEmpty());
    printf("lat,lon,alt,gps_year,gps_month,gps_day,gps_hour,gps_minute,gps_second,gps_millisecond,gps_fix\r\n");
    while (!IsTransmitEmpty());

    DataLogging_GetEntrySector(0, SectorCount, SensorData.SectorAccess);
    for (SectorCount = 0; SectorCount < 400000; SectorCount++) {
        Entry=DataLogging_GetEntrySector(0, SectorCount, SensorData.SectorAccess);
        //printf("%d\r\n", Entry);
        for (CurDataPoint = 0; CurDataPoint < DATA_POINTS; CurDataPoint++) {
            printf("%d,", Entry);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].BoschAccel.X, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Y, SensorData.SensorData.Entries[CurDataPoint].BoschAccel.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeAccel.X, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Y, SensorData.SensorData.Entries[CurDataPoint].FreeAccel.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].FreeMag.X, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Y, SensorData.SensorData.Entries[CurDataPoint].FreeMag.Z);
            while (!IsTransmitEmpty());
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].HoneyMag.X, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Y, SensorData.SensorData.Entries[CurDataPoint].HoneyMag.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Mag.Z);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.X, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Y, SensorData.SensorData.Entries[CurDataPoint].STCompass_Accel.Z);
            while (!IsTransmitEmpty());
            printf("%f,%f,%f,", SensorData.SensorData.Entries[CurDataPoint].GPS.lat, SensorData.SensorData.Entries[CurDataPoint].GPS.lon, SensorData.SensorData.Entries[CurDataPoint].GPS.height);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Date.year, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.month, SensorData.SensorData.Entries[CurDataPoint].GPS.Date.day);
            printf("%d,%d,%d,", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.hour, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.minute, SensorData.SensorData.Entries[CurDataPoint].GPS.Time.second);
            printf("%d,%d", SensorData.SensorData.Entries[CurDataPoint].GPS.Time.millisecond, SensorData.SensorData.Entries[CurDataPoint].GPS.fix);
            printf("\r\n");
            while (!IsTransmitEmpty());
        }
    }

}