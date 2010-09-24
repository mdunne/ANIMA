#include "anima_gps.h"


int init_gps()
{
	GPS_UART_Init(INITIAL_BAUD);
	GPS_PutMsg(NMEA_SWITCH);
}	