/*
The MIT License

Copyright (c) 2009 UCSC Autonomous Systems Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef _GPSref_H_
#define _GPSref_H_


#ifdef __cplusplus
       extern "C"{
#endif
       	
#include "circBuffer.h"
#include "mavlinkSensorMcu.h"

#include <p33fxxxx.h>
#include <uart.h>

#include <stdlib.h>
#include <string.h>


#define TOKEN_SIZE	15

// GPS Checksum Messages
// =====================
#define GGACS			86
#define RMCCS			75

// GPS Circular Buffers
// ====================
#define MSIZE			150

      	
void uartInit (void);
void gpsSentenceConfig (void);
void gpsFreqConfig (void);

unsigned char hex2char (unsigned char halfhex);
void gpsInit (void);
unsigned char gpsSeparate (unsigned char* outStream);
void gpsParse (void);
void getGpsMainData (float* data);
float degMinToDeg (unsigned char degrees, float minutes);
char gpSmbl (char symbl);
void parseRMC (unsigned char* stream);
void parseGGA (unsigned char* stream);
unsigned char getChecksum (unsigned char* sentence, unsigned char size);


#ifdef __cplusplus
       }
#endif
       
#endif /* _GPS_H_ */
