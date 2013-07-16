/*
 * File:   PORTS.h
 * Author: Elkaim
 *
 * Software module to access the 5 labeled ports on on the Uno32 I/O protection board. 
 * All ports have pins 1-2 and 13-14 grounded at the Uno32 I/O board. The Digital I/O
 * ports (X, Y, and Z) have 12 pins accessibe _03 through _12, and the Analog/Digital
 * I/O ports (V and W) have 6 pins accessible (_03 through _08), with the remaining pins
 * on the connector grounded.
 *
 * The individual ports pins can be addressed directly using the appropriate _TRIS and _LAT
 * #defines. Using the _TRIS to set direction (0 for output, 1 for ), and then manipulate
 * the pins direction with the _LAT to drive (1 for high, 0 for low) and the _BIT to read.
 * These can all be manipulated at the bit level. For Port level manipulation, there are
 * provided functions.
 *
 * The convention is that PORTxYY_TRIS (_LAT or _BIT) where x is V,W,X,Y, or Z, and YY is
 * 03 to 12 (with V and W going up only to 08).
 *
 * SPI_MASTER should be defined if both jumpers on the SPI CONTROL are towards the top 
 *            of the board. 
 *
 * PORTS_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * Make sure it is commented out for module useage.
 *
 * Created on December 26, 2011, 11:21 PM
 */

#ifndef PORTS_H
#define PORTS_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define JP_SPI_MASTER

#ifndef SUCCESS
#define SUCCESS 0
#define ERROR -1
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define PORTV 0
#define PORTW 1
#define PORTX 2
#define PORTY 3
#define PORTZ 4

//PORT V
#define PORTV03_TRIS TRISBbits.TRISB2
#define PORTV04_TRIS TRISBbits.TRISB3
#define PORTV05_TRIS TRISBbits.TRISB4
#define PORTV06_TRIS TRISBbits.TRISB5
#define PORTV07_TRIS TRISBbits.TRISB8
#define PORTV08_TRIS TRISBbits.TRISB9

#define PORTV03_BIT PORTBbits.RB2
#define PORTV04_BIT PORTBbits.RB3
#define PORTV05_BIT PORTBbits.RB4
#define PORTV06_BIT PORTBbits.RB5
#define PORTV07_BIT PORTBbits.RB8
#define PORTV08_BIT PORTBbits.RB9

#define PORTV03_LAT LATBbits.LATB2
#define PORTV04_LAT LATBbits.LATB3
#define PORTV05_LAT LATBbits.LATB4
#define PORTV06_LAT LATBbits.LATB5
#define PORTV07_LAT LATBbits.LATB8
#define PORTV08_LAT LATBbits.LATB9

//PORT W
#define PORTW03_TRIS TRISBbits.TRISB11
#define PORTW04_TRIS TRISBbits.TRISB10
#define PORTW05_TRIS TRISBbits.TRISB13
#define PORTW06_TRIS TRISBbits.TRISB12
#define PORTW07_TRIS TRISBbits.TRISB15
#define PORTW08_TRIS TRISBbits.TRISB14

#define PORTW03_BIT PORTBbits.RB11
#define PORTW04_BIT PORTBbits.RB10
#define PORTW05_BIT PORTBbits.RB13
#define PORTW06_BIT PORTBbits.RB12
#define PORTW07_BIT PORTBbits.RB15
#define PORTW08_BIT PORTBbits.RB14

#define PORTW03_LAT LATBbits.LATB11
#define PORTW04_LAT LATBbits.LATB10
#define PORTW05_LAT LATBbits.LATB13
#define PORTW06_LAT LATBbits.LATB12
#define PORTW07_LAT LATBbits.LATB15
#define PORTW08_LAT LATBbits.LATB14

// PORT X
#define PORTX03_TRIS TRISFbits.TRISF5
#define PORTX04_TRIS TRISBbits.TRISB0
#define PORTX05_TRIS TRISGbits.TRISG6
#define PORTX06_TRIS TRISFbits.TRISF4
#define PORTX07_TRIS TRISGbits.TRISG7   //switches with SPI_MASTER
#define PORTX08_TRIS TRISFbits.TRISF6
#define PORTX09_TRIS TRISGbits.TRISG8   //switches with SPI_MASTER
#define PORTX10_TRIS TRISDbits.TRISD7
#define PORTX11_TRIS TRISDbits.TRISD4
#define PORTX12_TRIS TRISDbits.TRISD6

#define PORTX03_BIT PORTFbits.RF5
#define PORTX04_BIT PORTBbits.RB0
#define PORTX05_BIT PORTGbits.RG6
#define PORTX06_BIT PORTFbits.RF4
#define PORTX07_BIT PORTGbits.RG7   //switches with SPI_MASTER
#define PORTX08_BIT PORTFbits.RF6
#define PORTX09_BIT PORTGbits.RG8   //switches with SPI_MASTER
#define PORTX10_BIT PORTDbits.RD7
#define PORTX11_BIT PORTDbits.RD4
#define PORTX12_BIT PORTDbits.RD6

#define PORTX03_LAT LATFbits.LATF5
#define PORTX04_LAT LATBbits.LATB0
#define PORTX05_LAT LATGbits.LATG6
#define PORTX06_LAT LATFbits.LATF4
#define PORTX07_LAT LATGbits.LATG7   //switches with SPI_MASTER
#define PORTX08_LAT LATFbits.LATF6
#define PORTX09_LAT LATGbits.LATG8   //switches with SPI_MASTER
#define PORTX10_LAT LATDbits.LATD7
#define PORTX11_LAT LATDbits.LATD4
#define PORTX12_LAT LATDbits.LATD6

#ifdef JP_SPI_MASTER
#define PORTX07_TRIS TRISGbits.TRISG7   //switches with SPI_MASTER
#define PORTX09_TRIS TRISGbits.TRISG8   //switches with SPI_MASTER
#define PORTX07_LAT LATGbits.LATG7   //switches with SPI_MASTER
#define PORTX09_LAT LATGbits.LATG8   //switches with SPI_MASTER
#define PORTX07_BIT PORTGbits.RG7   //switches with SPI_MASTER
#define PORTX09_BIT PORTGbits.RG8   //switches with SPI_MASTER
#else
#define PORTX07_TRIS TRISGbits.TRISG8   //switches with SPI_MASTER
#define PORTX09_TRIS TRISGbits.TRISG7   //switches with SPI_MASTER
#define PORTX07_LAT LATGbits.LATG8   //switches with SPI_MASTER
#define PORTX09_LAT LATGbits.LATG7   //switches with SPI_MASTER
#define PORTX07_BIT PORTGbits.RG8   //switches with SPI_MASTER
#define PORTX09_BIT PORTGbits.RG7   //switches with SPI_MASTER
#endif

//PORT Y
#define PORTY03_TRIS TRISDbits.TRISD11
#define PORTY04_TRIS TRISDbits.TRISD3
#define PORTY05_TRIS TRISDbits.TRISD5
#define PORTY06_TRIS TRISDbits.TRISD10
#define PORTY07_TRIS TRISEbits.TRISE7
#define PORTY08_TRIS TRISDbits.TRISD9
#define PORTY09_TRIS TRISEbits.TRISE6
#define PORTY10_TRIS TRISDbits.TRISD2
#define PORTY11_TRIS TRISEbits.TRISE5
#define PORTY12_TRIS TRISDbits.TRISD1

#define PORTY03_BIT PORTDbits.RD11
#define PORTY04_BIT PORTDbits.RD3
#define PORTY05_BIT PORTDbits.RD5
#define PORTY06_BIT PORTDbits.RD10
#define PORTY07_BIT PORTEbits.RE7
#define PORTY08_BIT PORTDbits.RD9
#define PORTY09_BIT PORTEbits.RE6
#define PORTY10_BIT PORTDbits.RD2
#define PORTY11_BIT PORTEbits.RE5
#define PORTY12_BIT PORTDbits.RD1

#define PORTY03_LAT LATDbits.LATD11
#define PORTY04_LAT LATDbits.LATD3
#define PORTY05_LAT LATDbits.LATD5
#define PORTY06_LAT LATDbits.LATD10
#define PORTY07_LAT LATEbits.LATE7
#define PORTY08_LAT LATDbits.LATD9
#define PORTY09_LAT LATEbits.LATE6
#define PORTY10_LAT LATDbits.LATD2
#define PORTY11_LAT LATEbits.LATE5
#define PORTY12_LAT LATDbits.LATD1

// PORT Z
#define PORTZ03_TRIS TRISEbits.TRISE4
#define PORTZ04_TRIS TRISFbits.TRISF1
#define PORTZ05_TRIS TRISEbits.TRISE3
#define PORTZ06_TRIS TRISDbits.TRISD0
#define PORTZ07_TRIS TRISEbits.TRISE2
#define PORTZ08_TRIS TRISDbits.TRISD8
#define PORTZ09_TRIS TRISEbits.TRISE1
#define PORTZ10_TRIS TRISFbits.TRISF3 // Also SERIAL port to FTDI
#define PORTZ11_TRIS TRISEbits.TRISE0
#define PORTZ12_TRIS TRISFbits.TRISF2 // Also SERIAL port to FTDI

#define PORTZ03_BIT PORTEbits.RE4
#define PORTZ04_BIT PORTFbits.RF1
#define PORTZ05_BIT PORTEbits.RE3
#define PORTZ06_BIT PORTDbits.RD0
#define PORTZ07_BIT PORTEbits.RE2
#define PORTZ08_BIT PORTDbits.RD8
#define PORTZ09_BIT PORTEbits.RE1
#define PORTZ10_BIT PORTFbits.RF3 // Also SERIAL port to FTDI
#define PORTZ11_BIT PORTEbits.RE0
#define PORTZ12_BIT PORTFbits.RF2 // Also SERIAL port to FTDI

#define PORTZ03_LAT LATEbits.LATE4
#define PORTZ04_LAT LATFbits.LATF1
#define PORTZ05_LAT LATEbits.LATE3
#define PORTZ06_LAT LATDbits.LATD0
#define PORTZ07_LAT LATEbits.LATE2
#define PORTZ08_LAT LATDbits.LATD8
#define PORTZ09_LAT LATEbits.LATE1
#define PORTZ10_LAT LATFbits.LATF3 // Also SERIAL port to FTDI
#define PORTZ11_LAT LATEbits.LATE0
#define PORTZ12_LAT LATFbits.LATF2 // Also SERIAL port to FTDI

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * Function: PORTS_SetPortDirection(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - output, 1 - input
 * @return SUCCESS or ERROR
 * @remark Function sets the director for port (eg: PORTX) for every pin on the
 *         port, matching the bit pattern for 0 (output) and 1 (input).
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_SetPortDirection(char port, unsigned short pattern);

/**
 * Function: PORTS_SetPortInputs(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - ignored, 1 - set to input
 * @return SUCCESS or ERROR
 * @remark Function sets the each pin with a 1 in the pattern or the port
 *         designated in port (use PORTx) to an input. 0's are unchanged.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_SetPortInputs(char port, unsigned short pattern);

/**
 * Function: PORTS_SetPortOutputs(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - ignored, 1 - set to output
 * @return SUCCESS or ERROR
 * @remark Function sets the direction of each pin with a 1 in the pattern or
 *         the port designated in port (use PORTx) to an output. 0's are unchanged.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_SetPortOutputs(char port, unsigned short pattern);

/**
 * Function: PORTS_ReadPort(char port);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @return Bit pattern corresponding to level inputs on pins of port
 * @remark Function reads the value of the port (PORTx) pins and returns them as
 *         a unsigned short (uint16). If pin is set as an output, it will read the
 *         value of LATCH, last value written to the pin.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
short int PORTS_ReadPort(char port);

/**
 * Function: PORTS_WritePort(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - set pin low, 1 - set pin high
 * @return SUCCESS or ERROR
 * @remark Function forces each pin in port (PORTx) that is an output to match
 *         the pattern (1 to high state, 0 to low state). Pins set as input are
 *         ignored.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_WritePort(char port, unsigned short pattern);

/**
 * Function: PORTS_SetPortBits(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - ignore, 1 - set pin high
 * @return SUCCESS or ERROR
 * @remark Function forces port (PORTx) pins high for each corresponding 1 in
 *         the pattern. 0's in patterns are left unchanged. Pins set to inputs
 *         are ignored.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_SetPortBits(char port, unsigned short pattern);

/**
 * Function: PORTS_ClearPortBits(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - ignore, 1 - set pin low
 * @return SUCCESS or ERROR
 * @remark Function forces port (PORTx) pins low for each corresponding 1 in
 *         the pattern. 0's in patterns are left unchanged. Pins set to inputs
 *         are ignored.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_ClearPortBits(char port, unsigned short pattern);

/**
 * Function: PORTS_TogglePortBits(char port, unsigned short pattern);
 * @param port, use #defined PORTx [V,W,X,Y,Z]
 * @param pattern, bit pattern: 0 - ignore, 1 - toggle pin
 * @return SUCCESS or ERROR
 * @remark Function forces port (PORTx) pins to change state for each
 *         corresponding 1 in the pattern. 0's in patterns are left unchanged.
 *         Pins set to inputs are ignored.
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.06 21:22 */
char PORTS_TogglePortBits(char port, unsigned short pattern);

#endif
