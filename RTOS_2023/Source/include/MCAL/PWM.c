/*
 * PWM.c
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */

#include"PWM.h"
void PWM_INIT(void){
	DIO_SetPinDir(DIO_PORTB ,Pin3, OUTPUT);
	DIO_SetPinDir(DIO_PORTD ,Pin7, OUTPUT);
}
void Start_PWM1(void){
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	OCR0 = 204;
}
void Start_PWM2(void){
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS20);
	OCR2 = 204;
}
void Stop_PWM1(void){
	TCCR0 &=~ (1<<COM01);
	TCCR0 &=~ (1<<CS00);
}
void Stop_PWM2(void){
	TCCR2 &=~ (1<<COM21);
	TCCR2 &=~ (1<<CS20);
}
