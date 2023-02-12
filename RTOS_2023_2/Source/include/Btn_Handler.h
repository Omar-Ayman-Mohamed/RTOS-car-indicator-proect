/*
 * Btn_Handler.h
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_HAL_BTN_HANDLER_H_
#define SOURCE_INCLUDE_HAL_BTN_HANDLER_H_

#include <avr/io.h>
#include "stddef.h"
#include "DIO.h"


uint8_t READ_IGNITON(void);
uint8_t READ_HAZARD_Button(void);/*instead of void it can take pin number*/
uint8_t READ_RIGHT_Button(void);
uint8_t READ_LEFT_Button(void);

#endif /* SOURCE_INCLUDE_HAL_BTN_HANDLER_H_ */
