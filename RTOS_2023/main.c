#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stddef.h"
#include "DIO.h"




/*add timer config to freertosconfiq */


void vBlink_Right(void );
void Blink_LEFT(void);
void Start_PWM1(void);
void Stop_PWM1(void);
void Start_PWM2(void);
void Stop_PWM2(void);
void PWM_INIT(void);

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

					Hazzred_button = 1;
					L_button = 0;
					R_button = 0;


			}
			else if(right_data){////
				right_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(right_button_pressed_counter%10)){
					R_button = 1;
					Hazzred_button = 0;
					L_button = 0;
					Stop_PWM2();
				}
			}
			else if(left_data){////
				left_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				if(!(left_button_pressed_counter%10)){
					L_button = 1;
					R_button = 0;
					Hazzred_button = 0;
					Stop_PWM1();

				}
			}
			else{
				/*neutral state*/
				Stop_PWM1();

				Stop_PWM2();

				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
				L_button = 0;
				R_button = 0;
				Hazzred_button = 0;

			}
		}else{
			Stop_PWM1();
			Stop_PWM2();
		}
//	}
}


void vState_machine(void)
{
	while(1)
	{

		if(!ignition_button){


			if(Hazzred_button){
//				DIO_SetPinVal(DIO_PORTC , Pin6 , HIGH);
				vBlink_Right();
				Blink_LEFT();
//				DIO_SetPinVal(DIO_PORTC , Pin3 , HIGH);
			}
			else if(R_button ){
//				DIO_SetPinVal(DIO_PORTC , Pin3 , LOW);
				vBlink_Right();


			}
			else if(L_button ){
//				DIO_SetPinVal(DIO_PORTC , Pin6, LOW);
				Blink_LEFT();

			}
		}

	}
}
void vBlink_Right(void ){

		if(led_mode){
			Start_PWM1();

		}else{
			Stop_PWM1();

	}


}

void Blink_LEFT(void){


		if(led_mode){


			Start_PWM2();

		}else{

			Stop_PWM2();



		}
//	}
}
void PWM_INIT(void){
	DIO_SetPinDir(DIO_PORTB ,Pin3, OUTPUT);
	DIO_SetPinDir(DIO_PORTD ,Pin7, OUTPUT);
}
void Start_PWM1(void){
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	OCR0 = 204;
}
void Start_PWM2(void){
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS20);
	OCR2 = 204;
}
void Stop_PWM1(void){
	TCCR0 &=~ (1<<COM01);
	TCCR0 &=~ (1<<CS00);
}
void Stop_PWM2(void){
	TCCR2 &=~ (1<<COM21);
	TCCR2 &=~ (1<<CS20);
}
