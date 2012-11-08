/*
 * File:   Sensor_Integration.h
 * Author: mdunne
 *
 * Created on July 11, 2012, 10:54 AM
 */

#ifndef Sensor_Integration_H
#define Sensor_Integration_H
#include "Data_Logging.h"




//unsigned char Block_Access[SECTOR_SIZE];

#define DATA_POINTS 8


typedef struct tSensorDataEntry {

    struct {
        short X;
        short Y;
        short Z;
    } BoschAccel;

    struct {
        short X;
        short Y;
        short Z;
    } FreeAccel;

    struct {
        short X;
        short Y;
        short Z;
    } FreeMag;

    struct {
        short X;
        short Y;
        short Z;
    } HoneyMag;

    struct {
        short X;
        short Y;
        short Z;
    } STCompass_Mag;

    struct {
        short X;
        short Y;
        short Z;
    } STCompass_Accel;

    struct {
        float lat;
        float lon;
        float height;

        struct {
            unsigned char year;
            unsigned char month;
            unsigned char day;
        } Date;

        struct {
            unsigned  hour : 5;
            unsigned minute : 5;
            unsigned second : 5;
            unsigned short millisecond;
        } Time;
        unsigned char fix;
    } GPS;
} tSensorDataEntry;

typedef union tSensorData {
    unsigned char SectorAccess[SD_SECTOR_SIZE];
    struct {
        unsigned short ID; //this needs to be here to allow for the id, not sure whether top or bottom for now
        tSensorDataEntry Entries[DATA_POINTS];
    } SensorData;
} tSensorData;

extern tSensorData SensorData;


enum
{
    APPROX_SEVENTY_HERTZ=0
}SENSOR_RATES;

void Sensor_Integration_Init();
void Sensor_Integration_HandleData(void);
void Sensor_Integration_TakeData(void);
void Sensor_Integration_SetSampleTime(unsigned int milliseconds);
void Sensor_Integration_DataDump();
void Sensor_Integration_DataDumpLatest();
void Sensor_Integration_DataDumpWholeCard(void);
void Sensor_Integration_SetSensorScale(int Scale);

#endif
