/*
 * servo.c
 *
 * Created: 2019-04-25 10:37:14
 *  Author: gunda
 */ 

#include<avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "servo.h"

void initializeServoMotor()
{
	int testFactor=1; //leave servo at min rotation
	PORTB=0b00100000;
	DDRB= 0xFF;  //set OC1A to output (among others)

	//Initialize Timer/Counter 1
	//System Clock as source
	//Mode 8: Phase and Freq. Correct PWM top=ICR1
	//OC1A output: Non-inverted
	//OC1B output: currently disabled
	//OC1C output: currently disabled

	ICR1=20000/testFactor;
	OCR1A=1000/testFactor; //set 1ms pulse  1000=1ms  2000=2ms
	TCCR1A=(1<<COM1A1);//COM1A1 Clear OCnA when match counting up,Set on down
	TCCR1B=(1<<WGM13)|(1<<CS11);// Phase and Freq correct ICR1=Top
}
void moveServoTo0Degrees()
{
	OCR1A = 1000;//Leave servo at min rotation
}
void moveServoTo90degrees()
{
	OCR1A = 2000; //leave servo at max rotation
	
}
