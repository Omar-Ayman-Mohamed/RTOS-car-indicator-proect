#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


unsigned char arr[2]= {0,0};

SemaphoreHandle_t xSemaphore;
TimerHandle_t xButtonTimer = NULL;
TimerHandle_t xLedBlinkingTimer = NULL;

char ignition_button,R_button, L_button, Hazzred_button , led_mode = 0;


//char valid_press= 0;
//led_right_blinking_counter,led_left_blinking_counter

void get_readings(void);
TaskHandle_t task1ptr;

void State_machine(void);
void toggle_led_mode(void);

TaskHandle_t task2ptr;


int main(void)
{
	DDRA  = 0xFF;	// Configure all PORTA pins as output pins
	xTaskCreate(State_machine,"first",configMINIMAL_STACK_SIZE,NULL,1,&task1ptr);
	xButtonTimer = xTimerCreate
	                   ( /* Just a text name, not used by the RTOS
	                     kernel. */
	                     "Timer_button",
	                     /* The timer period in ticks, must be
	                     greater than 0. */
						 ( 5 / portTICK_PERIOD_MS),
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
							 ( 500 / portTICK_PERIOD_MS),
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
	int right_button_pressed_counter,left_button_pressed_counter,hazzred_button_pressed_counter=0;
	while(1)
	{
		ignition_button = readIgnitionButton(); ////
		if(ignition_button){

			if(readHazzredButton()){////
				hazzred_button_pressed_counter++;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(hazzred_button_pressed_counter%10)){
					Hazzred_button = 1;
				}
			}
			else if(readRightButton()){////
				right_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(right_button_pressed_counter%10)){
					R_button = 1;
				}
			}
			else if(readLeftButton()){////
				left_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				if(!(left_button_pressed_counter%10)){
					L_button = 1;
				}
			}
		}
	}
}



void state_machine(void)
{
	while(1)
	{
		if(ignition_button){
			if(Hazzred_button){
				right_led_write(led_mode);
				left_led_write(led_mode);
			}
			else if(R_button ){
				rightLedWrite(led_mode);

			}
			else if(L_button ){
				leftLedWrite(led_mode);

			}
		}

	}
}





