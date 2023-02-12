/*
 * DIO.c
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */


#include "DIO.h"

void DIO_SetPinDir(uint8_t port ,uint8_t pin, uint8_t dir)
{
	switch (port)
	{
		case DIO_PORTA:
		(dir == OUTPUT)? (SET_BIT(DDRA,pin)):(CLR_BIT(DDRA,pin));
		break;

		case DIO_PORTB:
		(dir == OUTPUT)? (SET_BIT(DDRB,pin)):(CLR_BIT(DDRB,pin));
		break;

		case DIO_PORTC:
		(dir == OUTPUT)? (SET_BIT(DDRC,pin)):(CLR_BIT(DDRC,pin));
		break;

		case DIO_PORTD:
		(dir == OUTPUT)? (SET_BIT(DDRD,pin)):(CLR_BIT(DDRD,pin));
		break;
	}
}


void DIO_SetPinVal(uint8_t port ,uint8_t pin , uint8_t val)
{
	switch (port)
	{
		case DIO_PORTA:
		(val == HIGH)? (SET_BIT(PORTA,pin)):(CLR_BIT(PORTA,pin));
		break;

		case DIO_PORTB:
		(val == HIGH)? (SET_BIT(PORTB,pin)):(CLR_BIT(PORTB,pin));
		break;

		case DIO_PORTC:
		(val == HIGH)? (SET_BIT(PORTC,pin)):(CLR_BIT(PORTC,pin));
		break;

		case DIO_PORTD:
		(val == HIGH)? (SET_BIT(PORTD,pin)):(CLR_BIT(PORTD,pin));
		break;
	}
}


uint8_t  DIO_GetPinVal(uint8_t port ,uint8_t pin)
{
	switch(port)
	{
		case  DIO_PORTA :
			return GET_BIT(PINA,pin);
			break;
		case  DIO_PORTB :
			return GET_BIT(PINB,pin);
			break;
		case  DIO_PORTC :
			return GET_BIT(PINC,pin);
			break;
		case  DIO_PORTD :
			return GET_BIT(PIND,pin);
			break;
	}
}


void  DIO_TogPinVal(uint8_t port ,uint8_t pin)
{
	switch(port)
	{
		case  DIO_PORTA :	TOG_BIT(PORTA,pin);
		break;
		case  DIO_PORTB :   TOG_BIT(PORTB,pin);
		break;
		case  DIO_PORTC :   TOG_BIT(PORTC,pin);
		break;
		case  DIO_PORTD :   TOG_BIT(PORTD,pin);
		break;
	}
}
