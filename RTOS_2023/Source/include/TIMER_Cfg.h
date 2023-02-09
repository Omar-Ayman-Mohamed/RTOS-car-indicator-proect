/*
 * TIMER_Cfg.h
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_TIMER_CFG_H_
#define SOURCE_INCLUDE_TIMER_CFG_H_


#define TIMER0_MODE    CTC_MODE


#define TIMER0_FREQ	           PRE_1024
#define TIMER0_OC0_PIN_MODE    OC_pin_NON_INVERTING_PWM

#define  OC_pin_DISCONNECTED		 0
#define  OC_pin_NON_INVERTING_PWM	 2
#define  OC_pin_INVERTING_PWM		 3

#define  NORMAL_MODE         0
#define  PWM_PHASE_CORRECT   1
#define  CTC_MODE            2
#define  PWM_FAST_MODE       3


#define  PRE_1               1
#define  PRE_8               2
#define  PRE_64              3
#define  PRE_256             4
#define  PRE_1024            5
#define  Ext_CLK_At_Falling  6
#define  Ext_CLK_At_Rising   7
#endif /* SOURCE_INCLUDE_TIMER_CFG_H_ */
