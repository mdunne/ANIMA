#include "p33FJ64MC802.h"
#include "circBuffer.h"
#include "uart2.h"
#include "stdio.h"


struct CircBuffer outgoingUart;
CBRef UART_transmitBuffer;
#define BUFFERSIZE 512
struct CircBuffer incomingUart;
CBRef UART_receiveBuffer;


	

void UART2Init(void)
{
		// Configure and open the port;
	// U2MODE Register
	// ==============
	U2MODEbits.UARTEN = 0;		// Disable the port		
	U2MODEbits.USIDL = 0;		// Stop on idle
	U2MODEbits.IREN	= 0;		// No IR decoder
	U2MODEbits.RTSMD = 0;		// Ready to send mode (irrelevant)
	U2MODEbits.UEN = 0;		// Only RX and TX
	U2MODEbits.WAKE	= 1;		// Enable at startup
	U2MODEbits.LPBACK = 0;		// Disable loopback
	U2MODEbits.ABAUD = 0;		// Disable autobaud
	U2MODEbits.URXINV = 0;		// Normal operation (high is idle)
	U2MODEbits.PDSEL = 0;		// No parity 8 bit
	U2MODEbits.STSEL = 0;		// 1 stop bit
	U2MODEbits.BRGH  = 1;		
	
	
	
	//__builtin_write_OSCCONL(0x46);
	__builtin_write_OSCCONL(OSCCON & ~(1<<6));
	//OSCCONbits.IOLOCK=0;
	
	
	RPOR5bits.RP11R=0b00101;  //connects uart 2 TX to RP11
	RPINR19bits.U2RXR= 10;    //connects RP10 to uart 2 RX
	
	//__builtin_write_OSCCONL(0x46);
	//__builtin_write_OSCCONL(0x57);
	__builtin_write_OSCCONL(OSCCON | (1<<6));
	//OSCCONbits.IOLOCK=1;
	
	IPC7 = 0x4400;
	// U2STA Register
	// ==============
	U2STAbits.URXISEL	= 0;		// RX interrupt on every character
	U2STAbits.OERR		= 0;		// clear overun error
	
	
	// U2BRG Register
	// ==============
	U2BRG = 86;			// Set the baud rate to 115200 by 86 576000 by 173
	
	// Enable the port;
	U2MODEbits.UARTEN	= 1;		// Enable the port	
	U2STAbits.UTXEN		= 1;		// Enable TX
	UART_transmitBuffer=(struct CircBuffer*)&outgoingUart;  //set up buffer for receive
	newCircBuffer(UART_transmitBuffer);
	//printf("%p\r\n",BufferB);

	IEC1bits.U2RXIE		= 1;		// Enable RX interrupts
	UART_receiveBuffer=(struct CircBuffer*)&incomingUart; //set up buffer for transmit
	newCircBuffer(UART_receiveBuffer);
}

//puts one char onto circular buffer for writing out to uart
//while enabling transmit interupt if needed

void UART2PutChar( char ch )
{
	if(getLength(UART_transmitBuffer)!=BSIZE)
	{
	writeBack(UART_transmitBuffer,ch);
	IEC1bits.U2TXIE=1;
	}
	if(U2STAbits.TRMT)
	{
		IFS1bits.U2TXIF=1;
	}	
}


//interupt for handling transmitting of bytes
void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void)
{
	IFS1bits.U2TXIF=0;
	if(getLength(UART_transmitBuffer)==0)
	{
		IEC1bits.U2TXIE=0;
	}
	else
	{
		U2TXREG=readFront(UART_transmitBuffer);
		//IEC1bits.U2TXIE=1;	
	}
}		

// function to read bytes from uart
//mostly defunct as now bytes are read by DMA
char UART2GetChar()
{
	//return getLength(UART_receiveBuffer);
	if(getLength(UART_receiveBuffer)==0)
	{
		return 0;
	}	
	return readFront(UART_receiveBuffer);
}
	

//static unsigned int BufferCount;

void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void)
{
	//UART2PutChar('q');
	//char temp;
	//temp=U2RXREG;
	while(U2STAbits.URXDA == 1){
		writeBack(UART_receiveBuffer, (unsigned char)U2RXREG);
	}
	
	// If there was an overun error clear it and continue
	if (U2STAbits.OERR == 1){
		U2STAbits.OERR = 0;
	}
	
	// clear the interrupt
	IFS1bits.U2RXIF = 0;
}

	
char UART2IsEmpty()
{
	if(getLength(UART_receiveBuffer)==0)
		return 1;
	return 0;
}	


char UART2HalfEmpty()
{
	if (getLength(UART_transmitBuffer)<=(BSIZE/2))
		return 1;
	else
		return 0;
}	