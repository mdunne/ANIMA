/*
 * File:   PORTS.c
 * Author: Elkaim
 *
 * Created on December 26, 2011, 11:22 PM
 */

#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h>
#include "serial.h"
#include "PORTS.h"
#include "bits.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define PORTS_TEST
//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
    #define dbprintf(...) printf(__VA_ARGS__)
#else
    #define dbprintf(...)
#endif

#define NOPCOUNT 150000
#define NUMPINS 10
#define ZERO 0

#define PORTVWMASK 0xFC
#define PORTXYZMASK 0xFFC

#define PORTS_SetInput(port,i) *PORTS_TRISSET[port][i-2] = PortsBits[port][i-2]
#define PORTS_SetOutput(port,i) *PORTS_TRISCLR[port][i-2] = PortsBits[port][i-2]
#define PORTS_SetPin(port,i) *PORTS_LATSET[port][i-2] = PortsBits[port][i-2]
#define PORTS_ClearPin(port,i) *PORTS_LATCLR[port][i-2] = PortsBits[port][i-2]
#define PORTS_TogglePin(port,i) *PORTS_LATINV[port][i-2] = PortsBits[port][i-2]

/*
#define PortVSetInput(i) *PORTV_TRISCLR[i-2] = PortVBits[i-2]
#define PortVSetOutput(i) *PORTV_TRISSET[i-2] = PortVBits[i-2]
#define PortVSetPin(i) *PORTV_LATSET[i-2] = PortVBits[i-2]
#define PortVClearPin(i) *PORTV_LATCLR[i-2] = PortVBits[i-2]
#define PortVTogglePin(i) *PORTV_LATINV[i-2] = PortVBits[i-2]

#define PortWSetInput(i) *PORTW_TRISCLR[i-2] = PortWBits[i-2]
#define PortWSetOutput(i) *PORTW_TRISSET[i-2] = PortWBits[i-2]
#define PortWSetPin(i) *PORTW_LATSET[i-2] = PortWBits[i-2]
#define PortWClearPin(i) *PORTW_LATCLR[i-2] = PortWBits[i-2]
#define PortWTogglePin(i) *PORTW_LATINV[i-2] = PortWBits[i-2]

#define PortXSetInput(i) *PORTX_TRISCLR[i-2] = PortXBits[i-2]
#define PortXSetOutput(i) *PORTX_TRISSET[i-2] = PortXBits[i-2]
#define PortXSetPin(i) *PORTX_LATSET[i-2] = PortXBits[i-2]
#define PortXClearPin(i) *PORTX_LATCLR[i-2] = PortXBits[i-2]
#define PortXTogglePin(i) *PORTX_LATINV[i-2] = PortXBits[i-2]

#define PortYSetInput(i) *PORTY_TRISCLR[i-2] = PortYBits[i-2]
#define PortYSetOutput(i) *PORTY_TRISSET[i-2] = PortYBits[i-2]
#define PortYSetPin(i) *PORTY_LATSET[i-2] = PortYBits[i-2]
#define PortYClearPin(i) *PORTY_LATCLR[i-2] = PortYBits[i-2]
#define PortYTogglePin(i) *PORTY_LATINV[i-2] = PortYBits[i-2]

#define PortZSetInput(i) *PORTZ_TRISCLR[i-2] = PortZBits[i-2]
#define PortZSetOutput(i) *PORTZ_TRISSET[i-2] = PortZBits[i-2]
#define PortZSetPin(i) *PORTZ_LATSET[i-2] = PortZBits[i-2]
#define PortZClearPin(i) *PORTZ_LATCLR[i-2] = PortZBits[i-2]
#define PortZTogglePin(i) *PORTZ_LATINV[i-2] = PortZBits[i-2]
*/

/*******************************************************************************
 * PRIVATE STRUCTS and TYPEDEFS                                                *
 ******************************************************************************/

typedef union {
    struct {
        unsigned :2;
        unsigned bit3 :1;
        unsigned bit4 :1;
        unsigned bit5 :1;
        unsigned bit6 :1;
        unsigned bit7 :1;
        unsigned bit8 :1;
        unsigned bit9 :1;
        unsigned bit10 :1;
        unsigned bit11 :1;
        unsigned bit12 :1;
        unsigned :4;
    };
    unsigned short ui;
} portBitField_T;

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

static volatile unsigned int * const PORTS_TRISCLR[][NUMPINS] = {{&TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, NULL, NULL, NULL, NULL},
                          {&TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, &TRISBCLR, NULL, NULL, NULL, NULL},
                          {&TRISFCLR, &TRISBCLR, &TRISGCLR, &TRISFCLR, &TRISGCLR, &TRISFCLR, &TRISGCLR, &TRISDCLR, &TRISDCLR, &TRISDCLR},
                          {&TRISDCLR, &TRISDCLR, &TRISDCLR, &TRISDCLR, &TRISECLR, &TRISDCLR, &TRISECLR, &TRISDCLR, &TRISECLR, &TRISDCLR},
                          {&TRISECLR, &TRISFCLR, &TRISECLR, &TRISDCLR, &TRISECLR, &TRISDCLR, &TRISECLR, &TRISFCLR, &TRISECLR, &TRISFCLR}};
static volatile unsigned int * const PORTS_TRISSET[][NUMPINS] = {{&TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, NULL, NULL, NULL, NULL},
                          {&TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, &TRISBSET, NULL, NULL, NULL, NULL},
                          {&TRISFSET, &TRISBSET, &TRISGSET, &TRISFSET, &TRISGSET, &TRISFSET, &TRISGSET, &TRISDSET, &TRISDSET, &TRISDSET},
                          {&TRISDSET, &TRISDSET, &TRISDSET, &TRISDSET, &TRISESET, &TRISDSET, &TRISESET, &TRISDSET, &TRISESET, &TRISDSET},
                          {&TRISESET, &TRISFSET, &TRISESET, &TRISDSET, &TRISESET, &TRISDSET, &TRISESET, &TRISFSET, &TRISESET, &TRISFSET}};
static volatile unsigned int * const PORTS_LATCLR[][NUMPINS] = {{&LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, NULL, NULL, NULL, NULL},
                          {&LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, &LATBCLR, NULL, NULL, NULL, NULL},
                          {&LATFCLR, &LATBCLR, &LATGCLR, &LATFCLR, &LATGCLR, &LATFCLR, &LATGCLR, &LATDCLR, &LATDCLR, &LATDCLR},
                          {&LATDCLR, &LATDCLR, &LATDCLR, &LATDCLR, &LATECLR, &LATDCLR, &LATECLR, &LATDCLR, &LATECLR, &LATDCLR},
                          {&LATECLR, &LATFCLR, &LATECLR, &LATDCLR, &LATECLR, &LATDCLR, &LATECLR, &LATFCLR, &LATECLR, &LATFCLR}};
static volatile unsigned int * const PORTS_LATSET[][NUMPINS] = {{&LATBSET, &LATBSET, &LATBSET, &LATBSET, &LATBSET, &LATBSET, NULL, NULL, NULL, NULL},
                          {&LATBSET, &LATBSET, &LATBSET, &LATBSET, &LATBSET, &LATBSET, NULL, NULL, NULL, NULL},
                          {&LATFSET, &LATBSET, &LATGSET, &LATFSET, &LATGSET, &LATFSET, &LATGSET, &LATDSET, &LATDSET, &LATDSET},
                          {&LATDSET, &LATDSET, &LATDSET, &LATDSET, &LATESET, &LATDSET, &LATESET, &LATDSET, &LATESET, &LATDSET},
                          {&LATESET, &LATFSET, &LATESET, &LATDSET, &LATESET, &LATDSET, &LATESET, &LATFSET, &LATESET, &LATFSET}};
static volatile unsigned int * const PORTS_LATINV[][NUMPINS] = {{&LATBINV, &LATBINV, &LATBINV, &LATBINV, &LATBINV, &LATBINV, NULL, NULL, NULL, NULL},
                          {&LATBINV, &LATBINV, &LATBINV, &LATBINV, &LATBINV, &LATBINV, NULL, NULL, NULL, NULL},
                          {&LATFINV, &LATBINV, &LATGINV, &LATFINV, &LATGINV, &LATFINV, &LATGINV, &LATDINV, &LATDINV, &LATDINV},
                          {&LATDINV, &LATDINV, &LATDINV, &LATDINV, &LATEINV, &LATDINV, &LATEINV, &LATDINV, &LATEINV, &LATDINV},
                          {&LATEINV, &LATFINV, &LATEINV, &LATDINV, &LATEINV, &LATDINV, &LATEINV, &LATFINV, &LATEINV, &LATFINV}};

#ifdef JP_SPI_MASTER
static const unsigned short PortsBits[][NUMPINS] = {{BIT_2,BIT_3,BIT_4,BIT_5,BIT_8,BIT_9,ZERO,ZERO,ZERO,ZERO},
                                              {BIT_11,BIT_10,BIT_13,BIT_12,BIT_15,BIT_14,ZERO,ZERO,ZERO,ZERO},
                                              {BIT_5,BIT_0,BIT_6,BIT_4,BIT_7,BIT_6,BIT_8,BIT_7,BIT_4,BIT_6},
                                              {BIT_11,BIT_3,BIT_5,BIT_10,BIT_7,BIT_9,BIT_6,BIT_2,BIT_5,BIT_1},
                                              {BIT_4,BIT_1,BIT_3,BIT_0,BIT_2,BIT_8,BIT_1,BIT_3,BIT_0,BIT_2}};
#else
static const unsigned short PortBits[][NUMPINS] = {{BIT_2,BIT_3,BIT_4,BIT_5,BIT_8,BIT_9,ZERO,ZERO,ZERO,ZERO},
                                              {BIT_11,BIT_10,BIT_13,BIT_12,BIT_15,BIT_14,ZERO,ZERO,ZERO,ZERO},
                                              {BIT_5,BIT_0,BIT_6,BIT_4,BIT_8,BIT_6,BIT_7,BIT_7,BIT_4,BIT_6},
                                              {BIT_11,BIT_3,BIT_5,BIT_10,BIT_7,BIT_9,BIT_6,BIT_2,BIT_5,BIT_1},
                                              {BIT_4,BIT_1,BIT_3,BIT_0,BIT_2,BIT_8,BIT_1,BIT_3,BIT_0,BIT_2}};
#endif
/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/

unsigned short PortReadV(void);
unsigned short PortReadW(void);
unsigned short PortReadX(void);
unsigned short PortReadY(void);
unsigned short PortReadZ(void);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

char PORTS_SetPortDirection(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port is in range
        dbprintf("\nPort initialization failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) { // covers both PORTV and PORTW
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  { // covers ports PORTX, PORTY, and PORTZ
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set as input for "1" in position
            PORTS_SetInput(port,i);
        } else PORTS_SetOutput(port,i);
    }
    return SUCCESS;
}

char PORTS_SetPortInputs(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port is in range
        dbprintf("\nPort initialization failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set as input for "1" in position
            PORTS_SetInput(port,i);
        }
    }
    return SUCCESS;
}

char PORTS_SetPortOutputs(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port is in range
        dbprintf("\nPort initialization failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set as output for "1" in position
            PORTS_SetOutput(port,i);
        }
    }
    return SUCCESS;
}

short int PORTS_ReadPort(char port)
{
    if ((port < 0)||(port > PORTZ)) {
        dbprintf("Port Read failed: Invalid Port");
        return ERROR;
    }
    switch(port) {
        case PORTV:
            return PortReadV();
            break;
        case PORTW:
            return PortReadW();
            break;
        case PORTX:
            return PortReadX();
            break;
        case PORTY:
            return PortReadY();
            break;
        case PORTZ:
            return PortReadZ();
        default:
            dbprintf("\nBad things have happened to arrive here");
            return ERROR;
            break;
    }
}

char PORTS_WritePort(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port has only one bit active
        dbprintf("\nPort write failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set for "1" in position
            PORTS_SetPin(port,i);
        } else PORTS_ClearPin(port,i);
    }
    return SUCCESS;
}

char PORTS_SetPortBits(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port has only one bit active
        dbprintf("\nPort Set Bits failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set for "1" in position
            PORTS_SetPin(port,i);
        }
    }
    return SUCCESS;
}

char PORTS_ClearPortBits(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port>PORTZ)) { // test if port has only one bit active
        dbprintf("\nPort Clear Bits failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set for "1" in position
            PORTS_ClearPin(port,i);
        }
    }
    return SUCCESS;
}

char PORTS_TogglePortBits(char port, unsigned short pattern)
{
    unsigned char i,topbit;
    if ((port < 0)||(port > PORTZ)) { // test if port has only one bit active
        dbprintf("\nPort Clear Bits failed, must be called with a single PORTx");
        return ERROR;
    }
    if (port <= PORTW) {
        topbit = 8;
        pattern &= PORTVWMASK;
    } else  {
        topbit = 12;
        pattern &= PORTXYZMASK;
    }
    for(i=2;i<topbit;i++) {
        if (pattern & (1<<i)) { // set for "1" in position
            PORTS_TogglePin(port,i);
        }
    }
    return SUCCESS;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

unsigned short PortReadV(void)
{
    portBitField_T portV = {.ui = 0x000};
    portV.bit3 = PORTV03_BIT;
    portV.bit4 = PORTV04_BIT;
    portV.bit5 = PORTV05_BIT;
    portV.bit6 = PORTV06_BIT;
    portV.bit7 = PORTV07_BIT;
    portV.bit8 = PORTV08_BIT;
    return(portV.ui);
}

unsigned short PortReadW(void)
{
    portBitField_T portW = {.ui = 0x000};
    portW.bit3 = PORTW03_BIT;
    portW.bit4 = PORTW04_BIT;
    portW.bit5 = PORTW05_BIT;
    portW.bit6 = PORTW06_BIT;
    portW.bit7 = PORTW07_BIT;
    portW.bit8 = PORTW08_BIT;
    return(portW.ui);
}

unsigned short PortReadX(void)
{
    portBitField_T portX = {.ui = 0x000};
    portX.bit3 = PORTX03_BIT;
    portX.bit4 = PORTX04_BIT;
    portX.bit5 = PORTX05_BIT;
    portX.bit6 = PORTX06_BIT;
    portX.bit7 = PORTX07_BIT;
    portX.bit8 = PORTX08_BIT;
    portX.bit9 = PORTX09_BIT;
    portX.bit10 = PORTX10_BIT;
    portX.bit11 = PORTX11_BIT;
    portX.bit12 = PORTX12_BIT;
    return(portX.ui);
}

unsigned short PortReadY(void)
{
    portBitField_T portY = {.ui = 0x000};
    portY.bit3 = PORTY03_BIT;
    portY.bit4 = PORTY04_BIT;
    portY.bit5 = PORTY05_BIT;
    portY.bit6 = PORTY06_BIT;
    portY.bit7 = PORTY07_BIT;
    portY.bit8 = PORTY08_BIT;
    portY.bit9 = PORTY09_BIT;
    portY.bit10 = PORTY10_BIT;
    portY.bit11 = PORTY11_BIT;
    portY.bit12 = PORTY12_BIT;
    return(portY.ui);
}

unsigned short PortReadZ(void)
{
    portBitField_T portZ = {.ui = 0x000};
    portZ.bit3 = PORTZ03_BIT;
    portZ.bit4 = PORTZ04_BIT;
    portZ.bit5 = PORTZ05_BIT;
    portZ.bit6 = PORTZ06_BIT;
    portZ.bit7 = PORTZ07_BIT;
    portZ.bit8 = PORTZ08_BIT;
    portZ.bit9 = PORTZ09_BIT;
    portZ.bit10 = PORTZ10_BIT;
    portZ.bit11 = PORTZ11_BIT;
    portZ.bit12 = PORTZ12_BIT;
    return(portZ.ui);
}

/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/

#ifdef PORTS_TEST

#include <p32xxxx.h>
#include <plib.h>
#include <stdio.h>
#include "serial.h"
#include "PORTS.h"
#include "bits.h"

#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")
#define OUTPUTPORT PORTW
#define INPUTPORT PORTZ

int main(void) {
    int i;
    unsigned short pattern;
    char j,k;

    SERIAL_Init();
    AD1PCFG = 0xFF;
    INTEnableSystemMultiVectoredInt();
    printf("\nHello World!");
    printf("\nTesting SetPortDirection: PortW to outputs, all other ports to inputs");
    PORTS_SetPortOuputs(OUTPUTPORT,0xFFC);
    PORTS_SetPortInputs(INPUTPORT,0xFFC);
    PORTS_SetPortDirection(PORTX,0xFC);
    PORTS_SetPortDirection(PORTY,0xFC);
    PORTS_SetPortDirection(PORTV,0xFFC);

    printf("\nTesting WritePort: Strobe PortW sequentially, leave other pins alone");
    PORTS_WritePort(OUTPUTPORT,0xFFC);
    for(k=0;k<10;k++) {
        pattern = 0x004; // 0b0000 0100
        for(j=0;j<10;j++) {
            PORTS_WritePort(OUTPUTPORT,pattern);
            DELAY();
            pattern <<= 1;
        }
        for(j=0;j<10;j++) {
            PORTS_WritePort(OUTPUTPORT,pattern);
            DELAY();
            pattern >>= 1;
        }
    }
    printf("\nTesting SetPins: Set each pin on in sequence, leave other pins alone");
    PORTS_WritePort(OUTPUTPORT,0x000);
    for(j=0;j<12;j++) {
        PORTS_SetPortBits(OUTPUTPORT,(1<<j));
        DELAY();
    }
    printf("\n.");
    for(j=0;j<50;j++) {
        printf(".");
        DELAY();
    }
    printf("\nTesting ClearPins: Set each pin off in sequence, leave other pins alone");
    PORTS_WritePort(OUTPUTPORT,0xFFC);
    for(j=0;j<12;j++) {
        PORTS_ClearPortBits(OUTPUTPORT,(1<<j));
        DELAY();
    }
    printf("\n.");
    for(j=0;j<50;j++) {
        printf(".");
        DELAY();
    }
    printf("\nTesting TogglePins: Set each pin toggle in sequence, leave other pins alone");
    PORTS_WritePort(OUTPUTPORT,0xFFC);
    for(j=0;j<12;j++) {
        PORTS_TogglePortBits(OUTPUTPORT,(1<<j));
        DELAY();
    }
    printf("\nTesting PortRead, all pins on PORTY will be echod onto PORTX.");
    while(1) {
        pattern = PORTS_ReadPort(INPUTPORT);
        PORTS_WritePort(OUTPUTPORT,pattern);
    }
    return 0;
}
#endif