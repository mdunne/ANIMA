/*
 * File:   I2C_Driver_test.c
 * Author: mdunne
 *
 * Created on April 19, 2012, 1:16 PM
 */

#include <p32xxxx.h>
#include <serial.h>
#include <GenericTypeDefs.h>
#include "I2C_Driver.h"
#include <plib.h>


int main(void) {
    SERIAL_Init();
    int Real_Rate=0;
    char data_out=0;
    Real_Rate=I2C_Init(400000);
    TRISGbits.TRISG9=0;
    _RG9=0;
    //PORTClearBits(IOPORT_G,BIT_9);
    INTEnableSystemMultiVectoredInt();
    printf("\r\nAnima Sensor Test Board I2C driver test\r\nThis will verify I2C operation through use of a logic analyzer\r\n");
    printf("Rate returned from I2C Module: %d\r\n",Real_Rate);

    data_out=I2C_ReadReg(0x40,0x02);
    printf("\r\n%d\r\n",data_out);
    while(1);
    unsigned char ch = 0;
    while (1) {
        if (IsTransmitEmpty() == TRUE)
            if (IsReceiveEmpty() == FALSE)
                PutChar(GetChar());
    }

    return 0;
}
