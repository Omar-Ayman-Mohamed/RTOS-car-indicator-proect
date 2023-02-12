/*
 * DIO.h
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_DIO_H_
#define SOURCE_INCLUDE_DIO_H_
#include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_private.h"

typedef struct
{
	uint8_t no_of_channels;
	uint8_t group_ids[];
}ChannelGroupType;

enum{DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD};
enum{Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7};
enum{LOW, HIGH, INPUT, OUTPUT};

void    DIO_SetPinDir(uint8_t port ,uint8_t pin, uint8_t dir);
void    DIO_SetPinVal(uint8_t port ,uint8_t pin , uint8_t val);
uint8_t DIO_GetPinVal(uint8_t port ,uint8_t pin);
void    DIO_TogPinVal(uint8_t port ,uint8_t pin);
/*void    DIO_ChannelGroupWrite(uint8_t, uint8_t);
uint8_t DIO_ChannelGroupRead (uint8_t, uint8_t);*/

#endif /* SOURCE_INCLUDE_DIO_H_ */
