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
#include "servo.h"

void initialize_servo_motor()
{
	int testFactor=1; //leave servo at min rotation
	DDRB |= 0x20;  //set OC1A to output

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
void servo_move_to_0()
{
	OCR1A = 1000;//Set servo at min rotation
}
void servo_move_to_90()
{
	OCR1A = 2000; //Set servo at max rotation
	
}
