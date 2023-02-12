/*
 * PWM.c
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */

#include"PWM.h"

void PWM_INIT(void){
	DIO_SetPinDir((uint8_t)DIO_PORTB ,(uint8_t)Pin3, (uint8_t)OUTPUT);
	DIO_SetPinDir((uint8_t)DIO_PORTD ,(uint8_t)Pin7,(uint8_t) OUTPUT);
}
void Start_PWM1(void){
	TCCR0 |=  (unsigned char)(1u<<WGM00);
	TCCR0 |= (unsigned char) (1u<<WGM01);
	TCCR0 |= (unsigned char) (1u<<COM01);
	TCCR0 |= (unsigned char) (1u<<CS00);

	OCR0 = (unsigned char)204;
}
void Start_PWM2(void){
    TCCR2 |= (unsigned char)(1u<<WGM20);
    TCCR2 |= (unsigned char) (1u<<WGM21);
    TCCR2 |= (unsigned char)(1u<<COM21);
    TCCR2 |= (unsigned char) (1u<<CS20);

	OCR2 = (unsigned char)204;
}
void Stop_PWM1(void){
	TCCR0 &=(unsigned char)(~(unsigned char) (1u<<COM01));
	TCCR0 &=(unsigned char)(~(unsigned char) (1u<<CS00));
}
void Stop_PWM2(void){
	TCCR2 &=(unsigned char)(~(unsigned char) (1u<<COM21));
	TCCR2 &=(unsigned char)(~(unsigned char)(1u<<CS20));
}
