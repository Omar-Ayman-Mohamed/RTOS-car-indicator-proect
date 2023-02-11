/*
 * TIMER_private.h
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_TIMER_PRIVATE_H_
#define SOURCE_INCLUDE_TIMER_PRIVATE_H_

#include "STD_TYPES.h"
#include "DIO.h"

#define  SREG  (*((volatile uint8_t *)(0x5F)))	  //i-bit
#define  TCCR0 (*((volatile uint8_t *)(0x53)))	  // WGM00/01  CS00/01/02
#define  TCNT0 (*((volatile uint8_t *)(0x52)))	  // counting register
#define  OCR0  (*((volatile uint8_t *)(0x5C)))	  // Comparing register
#define  TIMSK (*((volatile uint8_t *)(0x59)))	  // interrupt enable  for OVF,CTC

//-----TCCR0-------------
#define FOC0   7
#define WGM00  6
#define COM01  5
#define COM00  4
#define WGM01  3
#define CS02   2
#define CS01   1
#define CS00   0
//---------TIMSK--------------

#define OCIE0  1
#define TOIE0  0

#endif /* SOURCE_INCLUDE_TIMER_PRIVATE_H_ */
