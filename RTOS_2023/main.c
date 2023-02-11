#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stddef.h"
#include "DIO.h"
#include "PWM.h"
#include "Btn_Handler.h"
#include "LED.h"



/*add timer config to freertosconfiq */
TimerHandle_t xButtonTimer = NULL;
TimerHandle_t xLedBlinkingTimer = NULL;

char R_button, L_button, Hazzred_button , led_mode = 0;
int right_button_pressed_counter,left_button_pressed_counter,hazzred_button_pressed_counter=0;
uint8_t ignition_button=0;
void get_readings(void);
TaskHandle_t task1ptr;
void vState_machine(void);
void toggle_led_mode(void);

TaskHandle_t task2ptr;

int main(void)
{


	PWM_INIT();
	xButtonTimer = xTimerCreate
	                   ( /* Just a text name, not used by the RTOS
	                     kernel. */
	                     "Timer_button",
	                     /* The timer period in ticks, must be
	                     greater than 0. */
						 5,
	                     /* The timers will auto-reload themselves
	                     when they expire. */
	                     pdTRUE,
	                     /* The ID is used to store a count of the
	                     number of times the timer has expired, which
	                     is initialised to 0. */
	                     ( void * ) 0,
	                     /* Each timer calls the same callback when
	                     it expires. */
						 get_readings
	                   );
	xLedBlinkingTimer = xTimerCreate
		                   ( /* Just a text name, not used by the RTOS
		                     kernel. */
		                     "Timer_led",
		                     /* The timer period in ticks, must be
		                     greater than 0. */
							  500 ,
		                     /* The timers will auto-reload themselves
		                     when they expire. */
		                     pdTRUE,
		                     /* The ID is used to store a count of the
		                     number of times the timer has expired, which
		                     is initialised to 0. */
		                     ( void * ) 0,
		                     /* Each timer calls the same callback when
		                     it expires. */
							 toggle_led_mode
		                   );
	xTaskCreate(vState_machine,"first",configMINIMAL_STACK_SIZE,NULL,1,&task1ptr);
	xTimerStart(xButtonTimer, 10 );
	xTimerStart(xLedBlinkingTimer, 10 );
	vTaskStartScheduler();
	while(1)
	{


	}
}

void toggle_led_mode(void){
		led_mode = !led_mode;
}
void get_readings(void)
{

		ignition_button = READ_IGNITON();

		if(!ignition_button){
			uint8_t hazard_data = READ_HAZARD_Button();
			uint8_t right_data = READ_RIGHT_Button();
			uint8_t left_data = READ_LEFT_Button();
			if(hazard_data){
				/*hazard btton pressed state*/
					Hazzred_button = 1;
					L_button = 0;
					R_button = 0;
			}
			else if(right_data){
				/*Right button pressed state*/
				right_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(right_button_pressed_counter%10)){
					R_button = 1;
					Hazzred_button = 0;
					L_button = 0;
					Stop_Blinking_Left();
				}
			}
			else if(left_data){
				/*Left Button pressed state*/
				left_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				if(!(left_button_pressed_counter%10)){
					L_button = 1;
					R_button = 0;
					Hazzred_button = 0;
					Stop_Blinking_Right();
				}
			}
			else{
				/*neutral state no button pressed*/
				Stop_Blinking_Right();
				Stop_Blinking_Left();
				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
				L_button = 0;
				R_button = 0;
				Hazzred_button = 0;

			}
		}else{
			/*Ignition is off*/
			Stop_Blinking_Right();
			Stop_Blinking_Left();
		}

}


void vState_machine(void)
{
	while(1)
	{

		if(!ignition_button){
			if(Hazzred_button){
				vBlink_Right(led_mode);
				Blink_LEFT(led_mode);
			}
			else if(R_button ){
				vBlink_Right(led_mode);
			}
			else if(L_button ){
				Blink_LEFT(led_mode);
			}
		}
	}
}


