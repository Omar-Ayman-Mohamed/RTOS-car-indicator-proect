/*
 * LED.c
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */

#include"LED.h"
#include"PWM.h"

void Blink_Right(char led_mode ){
		if(led_mode){
			Start_PWM1();
		}else{
			Stop_PWM1();
	}
}

void Blink_LEFT(char led_mode){
		if(led_mode){
			Start_PWM2();
		}else{
			Stop_PWM2();
		}
}
void Stop_Blinking_Right(void){
	Stop_PWM1();
}
void Stop_Blinking_Left(void){
	Stop_PWM2();
}
