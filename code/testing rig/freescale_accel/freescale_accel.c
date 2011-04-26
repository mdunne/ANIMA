#include "p33FJ64MC802.h"
#include "uart2.h"
#include "stdio.h"


#include "freescale_accel.h"


#define XDATA 0x01
#define YDATA 0x03
#define ZDATA 0x05
#define SCALE_MASK 0b00000011
#define RATE_MASK 0b00111000
#define MODE_MASK 0x01


typedef enum{
STATUS=0x00,
OUT_X_MSB,
OUT_X_LSB,
OUT_Y_MSB,
OUT_Y_LSB,
OUT_Z_MSB,
OUT_Z_LSB,
F_SETUP=0x09,
TRIG_CFG,
SYSMOD,
INT_SOURCE,
WHO_AM_I,
XYZ_DATA_CFG,
HP_FILTER_CUTOFF,
PL_STATUS,
PL_CFG,
PL_COUNT,
PL_BF_ZCOMP,
P_L_THS_REG,
FF_MT_CFG,
FF_MT_SRC,
FF_MT_THS,
FF_MT_COUNT,
TRANSIENT_CFG=0x1D,
TRANSIENT_SRC,
TRANSIENT_THS,
TRANSIENT_COUNT,
PULSE_CFG,
PULSE_SRC,
PULSE_THSX,
PULSE_THSY,
PULSE_THSZ,
PULSE_TMLT,
PULSE_LTCY,
PULSE_WIND,
ASLP_COUNT,
CTRL_REG1,
CTRL_REG2,
CTRL_REG3,
CTRL_REG4,
CTRL_REG5,
OFF_X,
OFF_Y,
OFF_Z	
} REGISTERS;
	
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
	free_ChangeMode(FREE_ACTIVEMODE);
	printf("Device Awakened\r\n");
	return;	


}





int free_GetXData(void)
{
	int XData;
	XData=free_ReadInt(OUT_X_MSB);
	return XData;
	
}

int free_GetYData(void)
{
	int YData;
	YData=free_ReadInt(OUT_Y_MSB);
	return YData;
	
}

int free_GetZData(void)
{
	int ZData;
	ZData=free_ReadInt(OUT_Z_MSB);
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


//
unsigned char free_WriteReg(char address,char data){
	
	I2C1CONbits.SEN=1;
	while(I2C1CONbits.SEN==1);
	I2C1TRN=(I2C_ADDRESS<<1);
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon addressing");
		while(1);
	}
	
	I2C1TRN=address;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK upon address to wake");
		while(1);
	}	
	I2C1TRN=data;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1){
		printf("Device Responded with NACK upon changing to awake mode");
		while(1);
	}
	I2C1CONbits.PEN=1;
	while(I2C1CONbits.PEN==1);
	
	return 1;		
}

//
unsigned char free_ReadReg(char address){
	unsigned char data=0;
	I2C1CONbits.SEN=1;
	while(I2C1CONbits.SEN==1);

	I2C1TRN=I2C_ADDRESS<<1;
	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}	

	I2C1TRN=address;

	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}
	I2C1CONbits.RSEN=1;

	while(I2C1CONbits.RSEN==1);
	I2C1TRN=(I2C_ADDRESS<<1)+1;

	while(I2C1STATbits.TRSTAT!=0);
	if (I2C1STATbits.ACKSTAT==1)
	{
		printf("Device Responded with NACK");
		while(1);
	}
	I2C1CONbits.RCEN=1;
	//while(I2C1CONbits.RCEN==1);
	while(I2C1STATbits.RBF!=1);
	data=I2C1RCV;
	I2C1CONbits.PEN=1;
	while(I2C1CONbits.PEN==1);
	return data;
}



unsigned char free_GetScale(){
	unsigned char Scale,regist;
	Scale=255;
	regist=free_ReadReg(XYZ_DATA_CFG);
	regist&=SCALE_MASK;
	//printf("regist: %X\r\n",regist);
	if (regist==0)
		Scale=FREE_2GSCALE;
	if (regist==1)
		Scale=FREE_4GSCALE;
	if (regist==2)
		Scale=FREE_8GSCALE;

	return Scale;
}	
unsigned char free_SetScale(char scale){
	
	char regist,fun=XYZ_DATA_CFG;
	free_ChangeMode(FREE_STANDBYMODE);
	regist=free_ReadReg(XYZ_DATA_CFG);
	
	if (scale==FREE_2GSCALE)
		regist=(regist&(~SCALE_MASK))+0;
	if (scale==FREE_4GSCALE)
		regist=(regist&(~SCALE_MASK))+1;
	if (scale==FREE_8GSCALE)
		regist=(regist&(~SCALE_MASK))+2;
	free_WriteReg(XYZ_DATA_CFG,regist);
	free_ChangeMode(FREE_ACTIVEMODE);
	return 0;
	
}

//

void free_ChangeMode(char Mode){
	char Cur_Mode=0;
	Cur_Mode=free_ReadReg(CTRL_REG1);
	Cur_Mode&=(~MODE_MASK); //remove current mode
	if(Mode==FREE_STANDBYMODE){
		free_WriteReg(CTRL_REG1,Cur_Mode);
	}
	if(Mode==FREE_ACTIVEMODE){
		Cur_Mode|=MODE_MASK;
		free_WriteReg(CTRL_REG1,Cur_Mode);
	}		
}
//
unsigned char free_SetRate(char Rate){
	char regist;
	free_ChangeMode(FREE_STANDBYMODE);
	regist=free_ReadReg(CTRL_REG1);
	regist&=(~RATE_MASK);
	regist=regist+(Rate<<2);
	/*
	if (scale==FREE_2GSCALE)
		regist=(regist&(~SCALE_MASK))+0;
	if (scale==FREE_4GSCALE)
		regist=(regist&(~SCALE_MASK))+1;
	if (scale==FREE_8GSCALE)
		regist=(regist&(~SCALE_MASK))+2;
		*/
	free_WriteReg(CTRL_REG1,regist);
	free_ChangeMode(FREE_ACTIVEMODE);
	return 0;
	
}
//

unsigned char free_GetRate(){
	unsigned char Rate,regist;
	Rate=255;
	regist=free_ReadReg(CTRL_REG1);
	regist&=RATE_MASK;
	Rate=regist>>2;
	//printf("regist: %X\r\n",regist);
	/*if (regist==0)
		Scale=FREE_2GSCALE;
	if (regist==1)
		Scale=FREE_4GSCALE;
	if (regist==2)
		Scale=FREE_8GSCALE;
	*/
	return Rate;
}