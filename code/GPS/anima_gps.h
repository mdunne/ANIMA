#ifndef ANIMA_GPS_H
#define ANIMA_GPS_H

#include "uart1.h"

#define NMEA_SWITCH MEDIATEK_NMEA
#define INITIAL_BAUD MEDIATEK_INITIAL_BAUD 

//settings for mediatek 3329
#define MEDIATEK_NMEA "$PGCMD,16,1,0,0,0,1*6A\r\n"
#define MEDIATEK_INITIAL_BAUD BAUD_38400



//wrapper for functions, eventually will be able to select uart
#define GPS_PutChar UART1PutChar
#define GPS_PutMsg UART1PutMsg
#define GPS_UART_Init UART1Init

int init_gps();



#endif