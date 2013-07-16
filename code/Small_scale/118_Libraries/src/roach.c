/*
 * File:   roach.c
 * Author: mdunne
 *
 * Created on December 15, 2011, 12:59 PM
 */

#include <roach.h>
#include <p32xxxx.h>

#include <timers.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define LEFT_DIR _RF1
#define LEFT_DIR_INV _RE4
#define RIGHT_DIR _RD7
#define RIGHT_DIR_INV _RD6

#define HALL_FRONT_LEFT _RG6
#define HALL_FRONT_RIGHT _RB0
#define HALL_REAR_RIGHT _RB1
#define HALL_REAR_LEFT _RF5

#define LEFT_DIR_TRIS _TRISF1
#define LEFT_DIR_INV_TRIS _TRISE4
#define RIGHT_DIR_TRIS _TRISD7
#define RIGHT_DIR_INV_TRIS _TRISD6

#define HALL_FRONT_LEFT_TRIS _TRISG6
#define HALL_FRONT_RIGHT_TRIS _TRISB0
#define HALL_REAR_RIGHT_TRIS _TRISB1
#define HALL_REAR_LEFT_TRIS _TRISF5

#define LEFT_PWM PWM_PORTZ06
#define RIGHT_PWM PWM_PORTY12

#define LIGHT_SENSOR AD_PORTV4


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/****************************************************************************
 Function
     Roach_Init

 Parameters
    None.

 Returns
     SUCCESS if operation successful
     ERROR  otherwise

 Description
      Performs all the initialization necessary for the roach.
      this includes initializing the PWM module, the A/D converter, the
      data directions on some pins, and setting the initial motor directions.
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/
char Roach_Init(void) {
    //Initialize the serial port
    SERIAL_Init();
    TIMERS_Init();
    //set the control pins for the motors
    PWM_Init(LEFT_PWM | RIGHT_PWM, 200);
    LEFT_DIR_TRIS = 0;
    LEFT_DIR_INV_TRIS = 0;
    RIGHT_DIR_TRIS = 0;
    RIGHT_DIR_INV_TRIS = 0;
    LEFT_DIR = 0;
    LEFT_DIR_INV = ~LEFT_DIR;
    RIGHT_DIR = 0;
    RIGHT_DIR_INV = ~RIGHT_DIR;

    //set up the hall effect and divorce all the A/D pins
    AD1PCFG = 0xFF;
    HALL_FRONT_LEFT_TRIS = 1;
    HALL_FRONT_RIGHT_TRIS = 1;
    HALL_REAR_RIGHT_TRIS = 1;
    HALL_REAR_LEFT_TRIS = 1;


    //Initialize the light sensor
    AD_Init(LIGHT_SENSOR);

    //enable interrupts
    INTEnableSystemMultiVectoredInt();
}

/****************************************************************************
 Function
     LeftMtrSpeed

 Parameters
    newSpeed, A value between -10 and 10 which is the new speed
     of the motor. 0 stops the motor. A negative value is reverse.

 Returns
     SUCCESS if operation successful
     ERROR  otherwise

 Description
      This function is used to set the speed and direction
      of the left motor.
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/

char LeftMtrSpeed(char newSpeed) {
    if ((newSpeed < -10) || (newSpeed > 10)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        LEFT_DIR = 0;
        LEFT_DIR_INV = ~LEFT_DIR;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        LEFT_DIR = 1;
        LEFT_DIR_INV = ~LEFT_DIR;
    }
    if (SetDutyCycle(LEFT_PWM, newSpeed * 100) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/****************************************************************************
 Function
     RightMtrSpeed

 Parameters
    newSpeed, A value between -10 and 10 which is the new speed
     of the motor. 0 stops the motor. A negative value is reverse.

 Returns
     SUCCESS if operation successful
     ERROR  otherwise

 Description
      This function is used to set the speed and direction
      of the left motor.
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/

char RightMtrSpeed(char newSpeed) {
    if ((newSpeed < -10) || (newSpeed > 10)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        RIGHT_DIR = 0;
        RIGHT_DIR_INV = ~RIGHT_DIR;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        RIGHT_DIR = 1;
        RIGHT_DIR_INV = ~RIGHT_DIR;
    }
    if (SetDutyCycle(RIGHT_PWM, newSpeed * 100) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/****************************************************************************
 Function
     LightLevel

 Parameters
    None.

 Returns
     a 10-bit value corresponding to the amount of light received.

 Description
    Returns the current light level. A higher value means less light is detected.
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/

unsigned int LightLevel(void) {
    return ReadADPin(LIGHT_SENSOR);
}

/****************************************************************************
 Function
    ReadFrontLeftBumper

 Parameters
    None.

 Returns
     BUMPER_TRIPPED  if bumper is tripped
     BUMPER_NOT_TRIPPED otherwise

 Description
    Returns the state of the front left bumper
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/

unsigned char ReadFrontLeftBumper(void) {
    return !HALL_FRONT_LEFT;
}

/****************************************************************************
 Function
    ReadFrontRightBumper

 Parameters
    None.

 Returns
     BUMPER_TRIPPED  if bumper is tripped
     BUMPER_NOT_TRIPPED otherwise

 Description
    Returns the state of the front right bumper
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/

unsigned char ReadFrontRightBumper(void) {
    return !HALL_FRONT_RIGHT;
}

/****************************************************************************
 Function
    ReadRearLeftBumper

 Parameters
    None.

 Returns
     BUMPER_TRIPPED  if bumper is tripped
     BUMPER_NOT_TRIPPED otherwise

 Description
    Returns the state of the rear left bumper
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/



unsigned char ReadRearLeftBumper(void) {
    return !HALL_REAR_LEFT;
}

/****************************************************************************
 Function
    ReadRearRightBumper

 Parameters
    None.

 Returns
     BUMPER_TRIPPED  if bumper is tripped
     BUMPER_NOT_TRIPPED otherwise

 Description
    Returns the state of the rear right bumper
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/
unsigned char ReadRearRightBumper(void) {
    return !HALL_REAR_RIGHT;
}

/****************************************************************************
 Function
    ReadBumpers

 Parameters
    None.

 Returns
     4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right

 Description
    Returns the state of all 4 bumpers
 Notes
     None.

 Author
    Max Dunne, 2012.01.06
 ****************************************************************************/
unsigned char ReadBumpers(void) {
    return (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
}








//#define ROACH_TEST
#ifdef ROACH_TEST
    #pragma config FPLLIDIV 	= DIV_2		//PLL Input Divider
    #pragma config FPLLMUL 		= MUL_20	//PLL Multiplier
    #pragma config FPLLODIV 	= DIV_1 	//System PLL Output Clock Divid
    #pragma config FNOSC 		= PRIPLL	//Oscillator Selection Bits
    #pragma config FSOSCEN 		= OFF		//Secondary Oscillator Enable
    #pragma config IESO 		= OFF		//Internal/External Switch O
    #pragma config POSCMOD 		= XT		//Primary Oscillator Configuration
    #pragma config OSCIOFNC 	= OFF		//CLKO Output Signal Active on the OSCO Pin
    #pragma config FPBDIV 		= DIV_2		//Peripheral Clock Divisor
    #pragma config FCKSM 		= CSECMD	//Clock Switching and Monitor Selection
    #pragma config WDTPS 		= PS1		//Watchdog Timer Postscaler
    #pragma config FWDTEN		= OFF		//Watchdog Timer Enable
    #pragma config ICESEL		= ICS_PGx2	//ICE/ICD Comm Channel Select
    #pragma config PWP 			= OFF		//Program Flash Write Protect
    #pragma config BWP 			= OFF		//Boot Flash Write Protect bit
    #pragma config CP 			= OFF		//Code Protect



    #include <p32xxxx.h>
    #include <roach.h>
//#include <plib.h>

int main(void) {
    int light_level = 0;
    Roach_Init();
    printf("Welcome to the Roach Test\r\n");
    printf("Bump states and light levels will be printed to the terminal every .1 seconds while also controlling the motor speed\r\n");
    InitTimer(0, 2000);
    while (!IsTimerExpired(0));
    
    while (1) {
        light_level = LightLevel() / 100;
        if (ReadFrontLeftBumper()) {
            LeftMtrSpeed(light_level);
        }
        if (ReadFrontRightBumper()) {
            RightMtrSpeed(light_level);
        }
        if (ReadRearLeftBumper()) {
            LeftMtrSpeed(light_level*-1);
        }
        if (ReadRearRightBumper()) {
            RightMtrSpeed(light_level*-1);
        }
        if(IsTimerExpired(0)==TIMER_EXPIRED){
            printf("%d\t%d\t%d\t%d\t%d", ReadFrontLeftBumper(), ReadFrontRightBumper(), ReadRearLeftBumper(), ReadRearRightBumper(), LightLevel());
            InitTimer(0, 100);
        }
    }
    return 0;
}

#endif