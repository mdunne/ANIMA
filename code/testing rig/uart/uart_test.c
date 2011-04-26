



#include "p33FJ64MC802.h"
#include "stdio.h"
#include "uart2.h"

_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 





   
int main (void)
{
   unsigned char attributes;
   
   unsigned char size = 0, i;
   
        PLLFBD =41;
        CLKDIVbits.PLLPOST=0;
        CLKDIVbits.PLLPRE=0;
        __builtin_write_OSCCONH(0b001);
        __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b001);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	
	UART2Init();
	LATBbits.LATB15  = 1; 				// set latch levels
	TRISBbits.TRISB15 = 0x0000; 				// set IO as outputs
	//UART2PutChar('a');
	printf("Microstick UART test\r\nAll input should be mirrored back to you\r\n");
	while(1)
	{
		while(!UART2IsEmpty())
			UART2PutChar(UART2GetChar());
	}	

}








