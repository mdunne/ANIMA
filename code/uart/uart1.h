
//******************************************************************************
// Function Prototypes
//******************************************************************************

#ifndef UART1_H
#define UART1_H

#define BAUD_600 4165
#define BAUD_1200 2082
#define BAUD_2400 1041
#define BAUD_4800 520
#define BAUD_9600 259
#define BAUD_14400 173
#define BAUD_19200 129
#define BAUD_38400 64
#define BAUD_57600 42
#define BAUD_115200 21
#define BAUD_230400 10
#define BAUD_460800 4
#define BAUD_921600 2


char UART1GetChar();
void UART1Init(int baud_rate);
//#endif
char UART1IsEmpty();
int UART1GetLength();
void UART1PrintString( char *str );
void UART1PutChar( char ch );
void UART1PutDec( unsigned char dec );
void UART1PutHex( int toPrint );
char bufferreturn(unsigned int *buffer);
char UART1PutMsg(char *message);

unsigned char get_overflowcount();

void print_circ_buf();

#endif


