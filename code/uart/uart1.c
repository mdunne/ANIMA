#include "p33FJ256GP710.h"
#include "circBuffer.h"
//#include "apDefinitions.h"
//#include "MultiCircBuffer.h"
#include "UART1.h"
#include "stdio.h"
#include "loggerDefinitions.h"
#ifdef __DEBUG
	#include "uart2.h"
#endif

struct CircBuffer outgoingUart1;
CBRef UART1_transmitBuffer;
#define BUFFERSIZE 512
struct CircBuffer incomingUart1;
CBRef UART1_receiveBuffer;

//struct MultiCircBuffer SPIerrorBuffer;
//MCBRef SPI_errorBuffer;

//static DWORD CurrentSector;

//#ifdef DMAON
	
	// struct containing all parts a packet to allow easy writing
	
	

	

		
	unsigned char BufferA1[DMABUFFERSIZE] __attribute__((space(dma))) = {0};
	unsigned char BufferB1[DMABUFFERSIZE] __attribute__((space(dma))) = {0};
	static char bufferflag;
	static char need_buffer;
	//FSFILE * pointer;
	

//#endif

void UART1Init(int baud_rate)
{
		// Configure and open the port;
	// U2MODE Register
	// ==============
	U1MODEbits.UARTEN = 0;		// Disable the port		
	U1MODEbits.USIDL = 0;		// Stop on idle
	U1MODEbits.IREN	= 0;		// No IR decoder
	U1MODEbits.RTSMD = 0;		// Ready to send mode (irrelevant)
	U1MODEbits.UEN = 0;		// Only RX and TX
	U1MODEbits.WAKE	= 1;		// Enable at startup
	U1MODEbits.LPBACK = 0;		// Disable loopback
	U1MODEbits.ABAUD = 0;		// Disable autobaud
	U1MODEbits.URXINV = 0;		// Normal operation (high is idle)
	U1MODEbits.PDSEL = 0;		// No parity 8 bit
	U1MODEbits.STSEL = 0;		// 1 stop bit
	//U1MODEbits.BRGH  = 1;		
	
	//IPC7 = 0x4400;
	// U2STA Register
	// ==============
	U1STAbits.URXISEL	= 0;		// RX interrupt on every character
	U1STAbits.OERR		= 0;		// clear overun error
	U1STAbits.URXISEL=0;
	
	// U2BRG Register
	// ==============
	U1BRG = baud_rate;			// Set the baud rate to 115200 by 86 576000 by 173
	
	// Enable the port;
	IEC0bits.U1RXIE		= 1;		// Enable RX interrupts
	U1MODEbits.UARTEN	= 1;		// Enable the port	
	U1STAbits.UTXEN		= 1;		// Enable TX
	UART1_transmitBuffer=(struct CircBuffer*)&outgoingUart1;  //set up buffer for receive
	newCircBuffer(UART1_transmitBuffer);
	//printf("%p\r\n",BufferB);

	UART1_receiveBuffer=(struct CircBuffer*)&incomingUart1; //set up buffer for transmit
	newCircBuffer(UART1_receiveBuffer);
}

//puts one char onto circular buffer for writing out to uart
//while enabling transmit interupt if needed

void UART1PutChar( char ch )
{
	if(getLength(UART1_transmitBuffer)!=BSIZE)
	{
	writeBack(UART1_transmitBuffer,ch);
	IEC0bits.U1TXIE=1;
	}
	if(U1STAbits.TRMT)
	{
		IFS0bits.U1TXIF=1;
	}	
}


//interupt for handling transmitting of bytes
void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void)
{
	IFS0bits.U1TXIF=0;
	if(getLength(UART1_transmitBuffer)==0)
	{
		IEC0bits.U1TXIE=0;
	}
	else
	{
		U1TXREG=readFront(UART1_transmitBuffer);
		//IEC1bits.U2TXIE=1;	
	}
}		

// function to read bytes from uart
char UART1GetChar()
{
	//return getLength(UART1_receiveBuffer);
	if(getLength(UART1_receiveBuffer)==0)
	{
		return 0;
	}	
	return readFront(UART1_receiveBuffer);
}
	




void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void)
{
	//UART1PutChar('q');
	//char temp;
	//temp=U2RXREG;
	//UART2PutChar('e');
	while(U1STAbits.URXDA == 1){
		writeBack(UART1_receiveBuffer, (unsigned char)U1RXREG);
	}
	
	// If there was an overun error clear it and continue
	if (U1STAbits.OERR == 1){
		U1STAbits.OERR = 0;
	}
	
	// clear the interrupt
	IFS0bits.U1RXIF = 0;
}

	
char UART1IsEmpty()
{
	if(getLength(UART1_receiveBuffer)==0)
		return 1;
	return 0;
}

char UART1PutMsg(char *message)
{

		while(*message !='\0')
		{
	        UART2PutChar(*message);
	        UART1PutChar(*message++);
        }
}	