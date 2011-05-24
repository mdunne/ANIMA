



#include "p33FJ64MC802.h"
#include "stdio.h"
#include "uart2.h"
#include "stmicro_accel.h"


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
	
	printf("Microstick ST Micro Accelerometer test\r\n\r\n");
	stmicro_accel_init();
	//printf("Current Mode Settings: %X\r\n",stmicro_ReadReg(0x10));
	//while(1);
	
	printf("Scale is set to %d \r\n",stmicro_GetScale());
	
	stmicro_SetScale(STMICRO_4GSCALE);
	printf("Scale is set to %d and should be %d\r\n",stmicro_GetScale(),STMICRO_4GSCALE);
	stmicro_SetScale(STMICRO_2GSCALE);
	printf("Scale is set to %d and should be %d\r\n",stmicro_GetScale(),STMICRO_2GSCALE);
        printf("Control Reg 4 is: %d\r\n",stmicro_ReadReg(0x23));
	
	printf("Rate is set to %d \r\n",stmicro_GetRate());
	stmicro_SetRate(STMICRO_1000HERTZ);
	printf("Rate is set to %d and should be %d\r\n",stmicro_GetRate(),STMICRO_1000HERTZ);
	stmicro_SetRate(STMICRO_50HERTZ);
	printf("Rate is set to %d and should be %d\r\n",stmicro_GetRate(),STMICRO_50HERTZ);
	//printf("Current Mode Settings: %X\r\n",stmicro_ReadReg(0x10));
	char humanread=1;
        int maxX=stmicro_GetXData(), maxY=stmicro_GetYData(), maxZ=stmicro_GetZData();
        int minX=maxX, minY=maxY, minZ=maxZ;
        int curval=0;
	int i,j,data;
	for(i=0; i!=-1; i++)
		for(j=0; j!=100; j++)
			Nop();
	
	while(1)
	{
		//if (UART2HalfEmpty()){
			if (humanread==1)
			{
			printf("Cur X: %d \tCur Y: %d \tCur Z: %d\r\n",stmicro_GetXData(),stmicro_GetYData(),stmicro_GetZData());
			}
			else
			{
                            printf("max X: %d \tmax Y: %d \tmax Z: %d \tmin X: %d \tmin Y: %d min Z: %d\r\n",maxX,maxY,maxZ,minX,minY,minZ);
                            curval=stmicro_GetXData();
                            if (curval<minX){
                                minX=curval;
                            }
                            if (curval>maxX){
                                maxX=curval;
                            }
                            curval=stmicro_GetYData();
                            if (curval<minY){
                                minY=curval;
                            }
                            if (curval>maxY){
                                maxY=curval;
                            }
                            curval=stmicro_GetZData();
                            if (curval<minZ){
                                minZ=curval;
                            }
                            if (curval>maxZ){
                                maxZ=curval;
                            }
			}
			for(i=0; i!=-1; i++)
				Nop();
		//}	
		/*while(!UART2IsEmpty())
			UART2PutChar(UART2GetChar());*/
	}	

}








