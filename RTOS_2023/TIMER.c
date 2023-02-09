/*
 * TIMER.c
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */


#include "TIMER.h"

void Timer0_INIT()
{
	GIE();
	#if (TIMER0_MODE == NORMAL_MODE)
	SET_BIT(TIMSK,TOIE0);
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);

   	#elif (TIMER0_MODE == PWM_PHASE_CORRECT)
	TCCR0 |= TIMER0_OC0_PIN_MODE<<4;
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	SET_BIT(DDRB,3);//set OC0 as OUTPUT PIN

	#elif (TIMER0_MODE == CTC_MODE)
	SET_BIT(TIMSK,OCIE0);
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

	#elif (TIMER0_MODE == PWM_FAST_MODE)
	TCCR0 |= TIMER0_OC0_PIN_MODE << 4;
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(DDRB,3);//set OC0 as OUTPUT PIN

	#endif
}

void Timer0_Start()
{
	switch(TIMER0_FREQ)
	{
		case PRE_1024:
		{
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		} break;

		case PRE_256:
		{
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		} break;

		case PRE_64:
		{
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		} break;

		case PRE_8:
		{
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		} break;

		case PRE_1:
		{
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		} break;
	}
}

void Timer0_Stop()
{
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}

void TIMER0_PWM_Stop(void)
{
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
}

void TIMER0_PWM_Start(void)
{
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}

void Timer0_SET_DUTY_CYCLE (uint8_t percentage)
{
	if (percentage <= 0)
	{
		OCR0 = 0;
	}

	else if (percentage >= 100)
	{
		OCR0 = 255;
	}

	else
	{
		OCR0 = (uint8_t) (((percentage * 256)/100)-1);
	}
}
