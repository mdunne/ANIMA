/*
 * File:   pwm.h
 * Author: mdunne
 *
 * Software module to run the PWM module of the Uno32. The available pins for
 * which the PWM works are #defined below (PortZ-6, PortY-4,10,12, and PortX-11),
 * and are set by the hardware (cannot be modified).
 *
 * NOTE: Module uses TIMER2 for its interrupts.
 *
 * PWM_TEST (in the .c file) conditionally compiles the test harness for the code. 
 * Make sure it is commented out for module useage.
 *
 * Created on November 12, 2011, 9:27 AM
 */

#ifndef pwm_H
#define pwm_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define PWM_500HZ 500
#define PWM_1KHZ 1000
#define PWM_2KHZ 2000
#define PWM_5KHZ 5000
#define PWM_10KHZ 10000
#define PWM_20KHZ 20000
#define PWM_30KHZ 30000
#define PWM_40KHZ 40000

#define PWM_PORTZ06 (1<<0)
#define PWM_PORTY12 (1<<1)
#define PWM_PORTY10 (1<<2)
#define PWM_PORTY04 (1<<3)
#define PWM_PORTX11 (1<<4)

#define MIN_PWM 0
#define MAX_PWM 1000

#define PWM_ERR     -1
#define PWM_OK       0

#ifndef SUCCESS
#define SUCCESS 0
#define ERROR -1
#endif


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: PWM_Init
 * @param Channels, used #defined PWM_PORTxxx OR'd together for each PWM Channel
 * @param Period, An integer representing the frequency in hertz
 * @return SUCCESS or ERROR
 * @remark Initializes the OC channels into PWM mode and sets up the channels at frequncy given
 * @author Max Dunne
 * @date 2011.11.12  */
char PWM_Init(unsigned char Channels, unsigned int Period);

/**
 * Function: SetDutyCycle
 * @param Channels, use #defined PWM_PORTxxx
 * @param Duty, duty cycle for the channel (0-1000)
 * @return SUCCESS or ERROR
 * @remark Sets the Duty Cycle for a Single Channel
 * @author Max Dunne
 * @date 2011.11.12  */
char SetDutyCycle(char Channel, unsigned int Duty);


/**
 * Function: PWM_End
 * @param None
 * @return None
 * @remark Disables the PWM sub-system.
 * @author Max Dunne
 * @date 2011.11.12  */
void PWM_End(void);




#endif
