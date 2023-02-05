#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "DIO.h"
#include"TIMER.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"


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
/*edit 5/2/2023 21:02pm author : omar */
void Blink_Right(void);
void Blink_LEFT(void);
char READ_IGNITON(void);
char READ_HAZARD_Button(void);/*instead of void it can take pin number  */
char READ_RIGHT_Button(void);
char READ_LEFT_Button(void);
/*                                  */

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

/*edit 5/2/2023 21:02pm author : omar */
void Blink_Right(char led_mode){
	/*if(LEFT_STATE == NOT_PRESSED){
	 TIMER0_PWM_STOP(); 
	 }*/
	Timer1_SET_DUTY_CYCLE(80);
	if(led_mode){
		TIMER1_PWM_STOP();
	}else{
		TIMER1_PWM_START();
	}
}
void Blink_LEFT(char led_mode){
	/*if(RIGHT_STATE == NOT_PRESSED){
	 TIMER1_PWM_STOP(); 
	 }*/
	Timer0_SET_DUTY_CYCLE(80);
	if(led_mode){
		TIMER0_PWM_STOP();
	}else{
		TIMER0_PWM_START();
	}
}
char READ_IGNITON(void){
	DIO_SetPinDir(PORTA ,PIN0, INPUT);
	char IGNITION_data = DIO_GetPinVal(PORTA ,PIN0) ; 
	return IGNITION_data;
}
char READ_HAZARD_Button(void){
	DIO_SetPinDir(PORTA ,PIN1, INPUT);
	char HAZARD_data = DIO_GetPinVal(PORTA ,PIN1) ;
	/*Some logic is needed here or in hazard button function to handle rising edge
	 ex: 
	 CURRENT_HAZARD_DATA = getpinval();
	 if((previuos == low)&&(current == high)){
	 return pressed ; 
	 
	 }else{
	 return unpressed;
	 }
	 */
	return HAZARD_data;
}
char READ_RIGHT_Button(void){
	DIO_SetPinDir(PORTA ,PIN2, INPUT);
	char RIGHT_data = DIO_GetPinVal(PORTA ,PIN2) ; 
	return RIGHT_data;
}
char READ_LEFT_Button(void){
	DIO_SetPinDir(PORTA ,PIN3, INPUT);
	char LEFT_data = DIO_GetPinVal(PORTA ,PIN2); 
	return LEFT_data;
}
/*end of edit 21:04 pm author : omar*/




