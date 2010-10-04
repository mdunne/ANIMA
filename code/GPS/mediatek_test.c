



#include "p33FJ256GP710.h"
#include "stdio.h"
#include "uart2.h"
#include "uart1.h"
#include "anima_gps.h"

_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 

//#define TESTOVERFLOWBUFFER




   
int main (void)
{
   unsigned char attributes;
   unsigned char size = 0, i;
        PLLFBD =38;
        CLKDIVbits.PLLPOST=0;
        CLKDIVbits.PLLPRE=0;
        __builtin_write_OSCCONH(0b011);
        __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	UART2Init();
	init_gps(BAUD_38400);
	//UART1Init(BAUD_38400);
	printf("starting Mediatek GPS Test\r\n");
	char msg[]="$PGCMD,16,1,1,1,1,1*6B\r\n";
	char msg2[]="$PGCMD,16,0,0,0,0,0*6A\r\n";
	char r1hz[]="$PMTK220,1000*1F";
	char r4hz[]="$PMTK220,250*29";
	char r10hz[]="$PMTK220,100*2F";
	//gpsControlData.newDatatoParse=1;
	printf("new data to parse: %d",gpsControlData.newDatatoParse);
	//UART1PutMsg(MEDIATEK_NMEA);
	char hmm;
   while(1)
   {
	   //gpsControlData.newDatatoParse=1;
	   if(gpsControlData.newDatatoParse==1)
	   {
		   /*print_circ_buf();
		   printf("size in main: %d\r\n", (int)UART1GetLength());
		   for(i=0;i<50;i++)
		   {
			   UART1GetChar();   
			}*/ 
		   	//printf("what is going on\r\n");
		   	processNewGpsData();
		   	if(gpsControlData.newData==1)
		   	{
			printf("time: %02d:%02d:%02d",gpsControlData.hour,gpsControlData.min,gpsControlData.sec);
			printf(" Lat: %.4f: Lon: %.4f", gpsControlData.lat , gpsControlData.lon);
			printf(" Height: %.4f hdop: %d fix: %d sats: %d", gpsControlData.height, gpsControlData.hdop , gpsControlData.fix , gpsControlData.sats);
			
			printf("\r\n");
			gpsControlData.newData=0;
			}
		   		//while (UART1GetLength() > 0) //{

		//buildAndCheckSentence(GPS_GetChar());
		/*	hmm=UART1GetChar();
			printf("size: %d %c\r\n",UART1GetLength(),hmm);
			hmm=UART1GetChar();
			printf("size: %d %c\r\n",UART1GetLength(),hmm);
			printf("overflows: %d\r\n",get_overflowcount());*/
			
			/*hmm = UART1GetLength();
			printf("\r\n");
			for(i=0;i<hmm;i++) {
				printf("%c",UART1GetChar());
			}*/
			/*hmm=UART1GetChar();
			if(hmm!=0)
				printf("%c",hmm);*/
				
			
		//}
		   //	printf("%c",GPS_GetChar());
		   	//printf("infinit loop do you think\r\n");
		   	//printf("new data: %d",gpsControlData.newData);
		   	/*if(gpsControlData.newData==1)
		   	{
			printf("time: %d:%d:%d\r\n",gpsControlData.hour,gpsControlData.min,gpsControlData.sec);
			gpsControlData.newData=0;
			}*/
		   //printf("There is new data\r\n");
		   gpsControlData.newDatatoParse=0;
	   }
	}
}








