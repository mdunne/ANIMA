/*********************************************************************
 *
 *                    Simple Delay Routines 
 *
 *********************************************************************
 * FileName:        delay.c
 * Dependencies:    delay.h
 * Processor:       dsPIC33F
 * Complier:        MPLAB C30 v2.01.00 or higher
 *
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its dsPIC30F Microcontroller is intended 
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip's dsPIC30F Microcontroller products. 
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Richard Fischer      7/14/05 Initial release for LCD support
 * Priyabrata Sinha     1/27/06 Ported to non-prototype devices
 *
 ********************************************************************/

#include "delay.h"
#include "p33FJ256GP710.h"

unsigned int temp_count;

void Delay( unsigned int delay_count ) 
{
	TMR1=0;
	switch(delay_count)
	{
		case Delay_1mS_Cnt:
			T1CONbits.TCKPS=0b00;
			T1CONbits.TON=1;
			while(TMR1<=40000);
			T1CONbits.TON=0;
		break;
		case Delay_2mS_Cnt:
			T1CONbits.TCKPS=0b01;
			T1CONbits.TON=1;
			while(TMR1<=10000);
			T1CONbits.TON=0;
		break;
		case Delay_5mS_Cnt:
			T1CONbits.TCKPS=0b01;
			T1CONbits.TON=1;
			while(TMR1<=25000);
			T1CONbits.TON=0;
		break;
		case Delay_15mS_Cnt:
			T1CONbits.TCKPS=0b10;
			T1CONbits.TON=1;
			while(TMR1<=9375);
			T1CONbits.TON=0;
		break;		


	}	
	/*temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #3200, inner" );	
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");*/
}
	


void Delay_Us( unsigned int delayUs_count )
{
	TMR1=0;
	T1CONbits.TON=1;
	T1CONbits.TCKPS=0b00;
	while(TMR1<=7975);
	T1CONbits.TON=0;
	/*temp_count = delayUs_count +1;
	asm volatile("outer1: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done1");
	asm volatile("do #1500, inner1" );	
	asm volatile("nop");
	asm volatile("inner1: nop");
	asm volatile("bra outer1");
	asm volatile("done1:");*/
}		

