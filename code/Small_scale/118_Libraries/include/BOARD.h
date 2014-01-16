/* 
 * File:   BOARD.h
 * Author: Max Dunne
 *
 * Created on December 19, 2012, 2:08 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#include <stdint.h>
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*****************************************************************************/
// Boolean defines for TRUE, FALSE, SUCCESS and ERROR
#ifndef FALSE
//#define FALSE ((int8_t) 0)
//#define TRUE ((int8_t) 1)
#endif
//#define ERROR ((int8_t) -1)
//#define SUCCESS ((int8_t) 1)


void BOARD_Init();

unsigned int BOARD_GetPBClock();
void BOARD_blinkStall();

#endif	/* BOARD_H */

