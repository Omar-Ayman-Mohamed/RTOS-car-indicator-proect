/*
 * LED.h
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_HAL_LED_H_
#define SOURCE_INCLUDE_HAL_LED_H_
#include "stddef.h"
#include "DIO.h"
void Blink_Right(char led_mode );
void Blink_LEFT(char led_mode);
void Stop_Blinking_Right(void);
void Stop_Blinking_Left(void);

#endif /* SOURCE_INCLUDE_HAL_LED_H_ */
