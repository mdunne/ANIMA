
//******************************************************************************
// Function Prototypes
//******************************************************************************

#ifndef UART2_H
#define UART2_H



char UART2GetChar();
//#ifdef DMAON

//void UART2Init(FSFILE *inpointer);
//#else
void UART2Init();
//#endif
char UART2IsEmpty();
void UART2PrintString( char *str );
void UART2PutChar( char ch );
void UART2PutDec( unsigned char dec );
void UART2PutHex( int toPrint );
char bufferreturn(unsigned int *buffer);
unsigned char oldcalc_checksum(unsigned char inBuffer[], unsigned char outBuffer[]);

char UART2HalfEmpty();


#endif


