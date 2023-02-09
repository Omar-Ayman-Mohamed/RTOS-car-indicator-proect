#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stddef.h"
#include "DIO.h"
#include"TIMER.h"


/*add timer config to freertosconfiq */

/*void Task1_Func(void);
TaskHandle_t task1 ;
void Task2_Func(void);
TaskHandle_t task2 ;
void Task3_Func(void);
TaskHandle_t task3 ;*/
void Blink_Right(void);
void Blink_LEFT(void);
char READ_IGNITON(void);
char READ_HAZARD_Button(void);/*instead of void it can take pin number  */
char READ_RIGHT_Button(void);
char READ_LEFT_Button(void);
unsigned char arr[2]= {0,0};

SemaphoreHandle_t xSemaphore;
TimerHandle_t xButtonTimer = NULL;
TimerHandle_t xLedBlinkingTimer = NULL;

char ignition_button,R_button, L_button, Hazzred_button , led_mode = 0;

void get_readings(void);
TaskHandle_t task1ptr;

void State_machine(void);
void toggle_led_mode(void);

TaskHandle_t task2ptr;

int main(void)
{
	DDRC  = 0xFF;	// Configure all PORTC pins as output pins


/*	TimerHandle_t xTimer = xTimerCreate("timer1",10,pdTRUE,1,Task1_Func);
	TimerHandle_t xTimer2 = xTimerCreate("timer2",50,pdTRUE,1,Task2_Func);
	TimerHandle_t xTimer3 = xTimerCreate("timer2",100,pdTRUE,1,Task3_Func); */
/*	xTaskCreate(Task1_Func,"task1",configMINIMAL_STACK_SIZE,NULL,0,&task1);
	xTaskCreate(Task2_Func,"task2",configMINIMAL_STACK_SIZE,NULL,0,&task2);
	xTaskCreate(Task3_Func,"task3",configMINIMAL_STACK_SIZE,NULL,2,&task3);*/

/*	xTimerStart(xTimer, 10 );
	xTimerStart(xTimer2, 50 );
	xTimerStart(xTimer3, 100 );
*/
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


/*void Task1_Func(void)
{
	while(1)
	{
		PORTC ^= (1u<<5);
		vTaskDelay( 50 );//pdMS_TO_TICKS( 20 )

	}
}*/

/*void Task3_Func(void){
	/*while(1){
		PORTC ^= (1u<<6);
	vTaskDelay( 100 );//pdMS_TO_TICKS( 20 )
	}

}*/

/*void Task2_Func(void)
{
	/*TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 50 );
	xLastWakeTime = xTaskGetTickCount();*/

	/*while(1)*//*{
		PORTC ^= (1u<<3);
		/*vTaskDelay( 200 );
	}*/
	/*	vTaskDelayUntil( &xLastWakeTime, xPeriod );*/

/*}*/

void toggle_led_mode(void){
	led_mode = !led_mode;
}
void get_readings(void)
{
	int right_button_pressed_counter,left_button_pressed_counter,hazzred_button_pressed_counter=0;
	while(1)
	{
		ignition_button = READ_IGNITON(); ////
		if(ignition_button){
			char hazard_data = READ_HAZARD_Button();
			char right_data = READ_RIGHT_Button();
			char left_data = READ_LEFT_Button();
			if(hazard_data){////
				hazzred_button_pressed_counter++;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(hazzred_button_pressed_counter%10)){
					Hazzred_button = 1;
				}
			}
			else if(right_data){////
				right_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(right_button_pressed_counter%10)){
					R_button = 1;
				}
			}
			else if(left_data){////
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
				Blink_Right(led_mode);
				Blink_LEFT(led_mode);
			}
			else if(R_button ){
				Blink_Right(led_mode);

			}
			else if(L_button ){
				Blink_LEFT(led_mode);

			}
		}

	}
}
void Blink_Right(char led_mode){
	/*if(LEFT_STATE == NOT_PRESSED){
	 TIMER0_PWM_STOP();
	 }*/
	/*Timer1_SET_DUTY_CYCLE(80);*/
	if(led_mode){
		/*TIMER1_PWM_STOP();*/
		DIO_SetPinVal(PORTC , 6 , LOW);
	}else{
		/*TIMER1_PWM_START();*/
		DIO_SetPinVal(PORTC , 6 , HIGH);
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

