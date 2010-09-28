



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
	//UART1PutMsg(MEDIATEK_NMEA);
   while(1)
   {
	   //gpsControlData.newDatatoParse=1;
	   /*if(tGpsData.newDatatoParse==1)
	   {
		   printf("There is new data\r\n");
		   tGpsData.newDatatoParse=0;
	   }*/
	}  
	   /*if (!UART1IsEmpty())
	   {
		   while(!UART1IsEmpty())
		   {
			   printf("%c",UART1GetChar());
		   }
		} */ 
}








