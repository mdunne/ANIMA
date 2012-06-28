/*
 * File:   RCServo.h
 * Author: Elkaim
 *
 * Software module to drive up to 10 RC servos using the standard PWM signaling. The nominal
 * input for the servos is a PWM signal with a 20Hz frequency, and a high time from 1msec to
 * 2msec with 1.5msec being centered. Resolusion of module is 1uSec.
 *
 *                   ________________       50mSec period           _______________
 * _________________|  1.0 to 2.0 mS |_____________________________|  1.5mS center |_____
 *
 * Each RC_servo pin must be enable during the RC_Init() function, and cannot be changed
 * unless the RC_Servo module is terminated using the RC_End() function.
 *
 * Pins are attached to the RC_Servo module using #defined RC_PORTxxx from the available
 * list of pins below (not all pins are available for RC servo use).
 *
 * NOTE: This module uses TIMER3 for its internal timing and interrupts. Certain servos
 *       have a larger range and can be driven from 0.5mS to 2.5mse, in this case, change
 *       MINPULSE to 500 and MAXPULSE to 2500 in the .h file.
 *
 * RCSERVO_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * Make sure it is commented out for module useage.
 *
 * Created on December 7, 2011, 8:56 AM
 */

#ifndef RCServo_H
#define RCServo_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define MINPULSE 1000
#define MAXPULSE 2000

#define RC_PORTX03 0x001
#define RC_PORTX04 0x002
#define RC_PORTY06 0x004
#define RC_PORTY07 0x008
#define RC_PORTZ08 0x010
#define RC_PORTZ09 0x020
#define RC_PORTV03 0x040
#define RC_PORTV04 0x080
#define RC_PORTW07 0x100
#define RC_PORTW08 0x200

#ifndef SUCCESS
#define SUCCESS 0
#define ERROR -1
#endif

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function: RC_Init(unsigned short int RCpins);
 * @param RCpins, used #defined RC_PORTxxx OR'd together for each RC servo pin
 * @return SUCCESS or ERROR
 * @remark Initialize the RC module for use. Uses TIMER4 hardware and initializes
 *         all enabled RC servo pins to 1.5mSec pulse width (0 degree deflection).
 * @author Gabriel Hugh Elkaim
 * @date 2011.12.15 16:42 */
char RC_Init(unsigned short int RCpins);

/**
 * @Function: RC_SetPulseTime(unsigned short int RCpin, unsigned short int pulseTime);
 * @param RCpin, use #defined RC_PORTxxx
 * @param pulseTime, pulse width in uSeconds from [1000 to 2000]
 * @return SUCCESS or ERROR
 * @remark Sets servo pulse to desired value from 1mSec to 2mSec in 1uSec increments.
 * @author Gabriel Hugh Elkaim
 * @date 2011.12.15 16:42 */
char RC_SetPulseTime(unsigned short int RCpin, unsigned short int pulseTime);

/**
 * @Function: RC_GetPulseTime(unsigned short int RCpin);
 * @param RCpin, use #defined RC_PORTxxx
 * @return PulseTime in uSeconds
 * @remark Gets the servo pulse width, provided for symmetry.
 * @author Gabriel Hugh Elkaim
 * @date 2011.12.15 16:42 */
short int RC_GetPulseTime(unsigned short int RCpin);

/**
 * @Function: RC_End(void);
 * @param none
 * @return SUCCESS or ERROR
 * @remark Shuts down the RC servo module. Releases TIMER4 and shuts down all
 *         servo outputs.
 * @author Gabriel Hugh Elkaim
 * @date 2011.12.15 16:42 */
char RC_End(void);

#endif
