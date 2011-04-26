



#include "p33FJ64MC802.h"
#include "stdio.h"
#include "uart2.h"
#include "freescale_accel.h"


_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 





   
int main (void)
{

   //unsigned char size = 0, i;
   
        PLLFBD =150;
        CLKDIVbits.PLLPOST=0;
        CLKDIVbits.PLLPRE=5;
        __builtin_write_OSCCONH(0b001);
        __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b001);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	
	
	UART2Init();
	LATBbits.LATB15  = 1; 				// set latch levels
	TRISBbits.TRISB15 = 0; 				// set IO as outputs
	//UART2PutChar('a');
	
	printf("Microstick FreeScale Accelerometer test\r\nAll input should be mirrored back to you\r\n");
	free_accel_init();
	printf("Scale is set to %d \r\n",free_GetScale());
	free_SetScale(FREE_4GSCALE);
	printf("Scale is set to %d and should be %d\r\n",free_GetScale(),FREE_4GSCALE);
	free_SetScale(FREE_2GSCALE);
	printf("Scale is set to %d and should be %d\r\n",free_GetScale(),FREE_2GSCALE);
	printf("Rate is set to %d \r\n",free_GetRate());
	free_SetRate(FREE_200HERTZ);
	printf("Rate is set to %d and should be %d\r\n",free_GetRate(),FREE_200HERTZ);
	free_SetRate(FREE_800HERTZ);
	printf("Rate is set to %d and should be %d\r\n",free_GetRate(),FREE_800HERTZ);
	
	char humanread=1;
	int i,j,data;
	for(i=0; i!=-1; i++)
		for(j=0; j!=100; j++)
			Nop();
	
	while(1)
	{
		//if (UART2HalfEmpty()){
			if (humanread==1)
			{
			printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n",free_GetXData(),free_GetYData(),free_GetZData());
			}
			else
			{
				data=free_GetXData();
				//UART2PutChar('$');
				//UART2PutChar('#');
				UART2PutChar(data>>8);
				UART2PutChar(data&0x00FF);
				
				UART2PutChar('\r');
				UART2PutChar('\n');
				
			}
			for(i=0; i!=-1; i++)
				Nop();
		//}	
		/*while(!UART2IsEmpty())
			UART2PutChar(UART2GetChar());*/
	}	

}








