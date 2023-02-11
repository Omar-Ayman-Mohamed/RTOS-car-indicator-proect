/*
 * TIMER.h
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_TIMER_H_
#define SOURCE_INCLUDE_TIMER_H_

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER_Cfg.h"
#include "TIMER_private.h"
#include "INT.h"

void Timer0_INIT (void);
void Timer0_Start(void);
void Timer0_Stop (void);
void Timer0_SET_DUTY_CYCLE (uint8_t percentage);

void TIMER0_PWM_Start(void);
void TIMER0_PWM_Stop(void);

#endif /* SOURCE_INCLUDE_TIMER_H_ */
