#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "freescale_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05

typedef enum
{
	WAKE_UP
}COMMANDS;

#define I2C_ADDRESS 0x1C

void free_accel_init(void)
{
	char response=0;
	TRISBbits.TRISB9=0;
	TRISBbits.TRISB8=0;
	I2C1CONbits.I2CEN=0;
	I2C1CONbits.A10M=0;
	I2C1CONbits.SCLREL=1;
	I2C1CONbits.ACKDT=0;
	I2C1CONbits.DISSLW=1;
	I2C1BRG=511;
	I2C1RCV = 0x0000;
	I2C1TRN=0;
	I2C1CONbits.I2CEN=1;

	printf("Awakening Device\r\n");
	/*
	I2C1CONbits.SEN=1;
	while(I2C1CONbits.SEN==1);
	I2C1TRN=(I2C_ADDRESS<<1);
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon addressing");
		while(1);
	}
	
	I2C1TRN=0x2A;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon address to wake");
		while(1);
	}	
	I2C1TRN=1;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1){
		printf("Device Responded with NACK upon changing to awake mode");
		while(1);
	}
	I2C1CONbits.PEN=1;
	while(I2C1CONbits.PEN==1);
	printf("Device Awakened\r\n");
	*/
	printf("Device Awakened\r\n");
	return;	


}





int free_GetXData(void)
{
	int XData;
	XData=free_ReadInt(XDATA);
	return XData;
	
}

int free_GetYData(void)
{
	int YData;
	YData=free_ReadInt(YDATA);
	return YData;
	
}

int free_GetZData(void)
{
	int ZData;
	ZData=free_ReadInt(ZDATA);
	return ZData;
	
}


	
int free_ReadInt(char address){
	int Data=0;
	I2C1CONbits.SEN=1;
	while(I2C1CONbits.SEN==1);
	//char debugchar='0';
	
	I2C1TRN=I2C_ADDRESS<<1;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}	
	//printf("Accel Ackowledged\r\n");
	I2C1TRN=address;
	//UART2PutChar(debugchar);  //0
	//debugchar++;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}
	I2C1CONbits.RSEN=1;
	//UART2PutChar(debugchar); //1
	//debugchar++;
	while(I2C1CONbits.RSEN==1);
	I2C1TRN=(I2C_ADDRESS<<1)+1;
	//UART2PutChar(debugchar); //2
	//debugchar++;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}
	//UART2PutChar(debugchar); //3
	//debugchar++;
	I2C1CONbits.RCEN=1;
	//while(I2C1CONbits.RCEN==1);
	while(I2C1STATbits.RBF!=1);	
	Data=I2C1RCV<<8;
	
	
	//	UART2PutChar(debugchar);//4
	//debugchar++;
	I2C1CONbits.ACKEN=1;
	while (I2C1CONbits.ACKEN==1);
	//UART2PutChar(debugchar);
	I2C1CONbits.RCEN=1;

	//debugchar++;

	while(I2C1STATbits.RBF!=1);
	Data+=I2C1RCV;
	I2C1CONbits.ACKDT=1;
	I2C1CONbits.ACKEN=1;
	
	//UART2PutChar(debugchar);
	//debugchar++;

	while (I2C1CONbits.ACKEN==1);
	I2C1CONbits.ACKDT=0;
	I2C1CONbits.PEN=1;
	
	//UART2PutChar(debugchar);
	//debugchar++;

	while(I2C1CONbits.PEN==1);
	Data=Data>>2;
	return Data;
	
	
}



unsigned char free_WriteReg(char address){
	I2C1CONbits.SEN=1;
	while(I2C1CONbits.SEN==1);
	I2C1TRN=(I2C_ADDRESS<<1);
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon addressing");
		while(1);
	}
	
	I2C1TRN=0x2A;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon address to wake");
		while(1);
	}	
	I2C1TRN=1;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1){
		printf("Device Responded with NACK upon changing to awake mode");
		while(1);
	}
	I2C1CONbits.PEN=1;
	while(I2C1CONbits.PEN==1);
	
	return 1;		
}	