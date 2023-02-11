#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include"TIMER.h"
#include "stddef.h"
#include "DIO.h"




/*add timer config to freertosconfiq */

/*void Task1_Func(void);
TaskHandle_t task1 ;
void Task2_Func(void);
TaskHandle_t task2 ;
void Task3_Func(void);
TaskHandle_t task3 ;*/
void vBlink_Right(void );
void Blink_LEFT(void);
/*uint8_t READ_IGNITON(void);
uint8_t READ_HAZARD_Button(void);
uint8_t READ_RIGHT_Button(void);
uint8_t READ_LEFT_Button(void);*/
unsigned char arr[2]= {0,0};


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

	/*Timer0_INIT();*/
	/*Timer0_Start();*/


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
//	xTaskCreate(vState_machine,"first",configMINIMAL_STACK_SIZE,NULL,1,&task1ptr);
	/*Timer0_INIT();
	Timer0_Start();
	DIO_SetPinDir(DIO_PORTB ,Pin3, OUTPUT);*/
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
//	while(1){
		led_mode = !led_mode;
//	}

}
void get_readings(void)
{



//	while(1)
//	{

		ignition_button = READ_IGNITON(); ////
//		DIO_SetPinVal(DIO_PORTC , Pin4 , HIGH);
//		ignition_button = 1; ////
		if(!ignition_button){
			uint8_t hazard_data = READ_HAZARD_Button();
//			hazard_data=1;
			uint8_t right_data = READ_RIGHT_Button();
//			char right_data = 0;
			uint8_t left_data = READ_LEFT_Button();
			if(hazard_data){////
			/*	hazzred_button_pressed_counter++;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
*/
	/*			if(!(hazzred_button_pressed_counter%10)){*/
					Hazzred_button = 1;
					L_button = 0;
					R_button = 0;

//					DIO_SetPinVal(DIO_PORTC , Pin6 , HIGH);
				/*}*/
			}
			else if(right_data){////
				right_button_pressed_counter++;
				hazzred_button_pressed_counter=0;
				left_button_pressed_counter=0;
				if(!(right_button_pressed_counter%10)){
					R_button = 1;
					Hazzred_button = 0;
					L_button = 0;
					DIO_SetPinVal(DIO_PORTC , Pin3 , LOW);
					/*TCCR1B &=~ (1<<CS12);
					TCCR1B &=~ (1<<CS11);
					TCCR1B &=~ (1<<CS10);*/
					TCCR2 &=~ (1<<COM21);
					TCCR2 &=~ (1<<CS20);
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
					DIO_SetPinVal(DIO_PORTC , Pin6 , LOW);
					TCCR0 &=~ (1<<COM01);
					TCCR0 &=~ (1<<CS00);

				}
			}
			else{
				DIO_SetPinVal(DIO_PORTB , Pin3 , LOW);
				DIO_SetPinVal(DIO_PORTC , Pin3 , LOW);
				TCCR0 &=~ (1<<COM01);
				TCCR0 &=~ (1<<CS00);
				TCCR2 &=~ (1<<COM21);
				TCCR2 &=~ (1<<CS20);
				/*TCCR1B &=~ (1<<CS12);
				TCCR1B &=~ (1<<CS11);
				TCCR1B &=~ (1<<CS10);*/
				hazzred_button_pressed_counter=0;
				right_button_pressed_counter=0;
				left_button_pressed_counter=0;
				L_button = 0;
				R_button = 0;
				Hazzred_button = 0;

			}
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
	/*DDRB|=(1<<PB3);*/
	DIO_SetPinDir(DIO_PORTB ,Pin3, OUTPUT);
//	while(1){
//		DIO_SetPinVal(DIO_PORTC , Pin6 , HIGH);
	/*Timer0_Start();*/
		if(led_mode){
			/*TIMER0_PWM_Start();*/
			TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
			OCR0 = 204;
			DIO_SetPinVal(DIO_PORTC , Pin6 , HIGH);
		}else{
			/*TIMER0_PWM_Start();*/
			DIO_SetPinVal(DIO_PORTC , Pin6 , LOW);
			TCCR0 &=~ (1<<COM01);
			TCCR0 &=~ (1<<CS00);
//		}
//		vTaskDelay( 400 );
//		led_mode= !led_mode;
	}


}

void Blink_LEFT(void){
	DIO_SetPinDir(DIO_PORTD ,Pin7, OUTPUT);
	/*if(RIGHT_STATE == NOT_PRESSED){
	 TIMER1_PWM_STOP();
	 }*/
//	while(1){
//	Timer0_SET_DUTY_CYCLE(80);
//	if(led_mode){
//		TIMER0_PWM_Stop();
//	}else{
//		TIMER0_PWM_Start();
//	}
//		DIO_SetPinVal(DIO_PORTC , Pin3 , HIGH);
		if(led_mode){
			/*TIMER1_PWM_STOP();*/
			TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS20);
			OCR2 = 204;

			DIO_SetPinVal(DIO_PORTC , Pin3 , HIGH);
		}else{
			/*TIMER1_PWM_START();*/

			DIO_SetPinVal(DIO_PORTC , Pin3 , LOW);
			TCCR2 &=~ (1<<COM21);
			TCCR2 &=~ (1<<CS20);


		}
//	}
}

/*uint8_t READ_IGNITON(void){

	DIO_SetPinDir(DIO_PORTA ,Pin0, INPUT);
	uint8_t IGNITION_data = DIO_GetPinVal(DIO_PORTA ,Pin0) ;
	return IGNITION_data;
}*/
/*uint8_t READ_HAZARD_Button(void){
	DIO_SetPinDir(DIO_PORTA ,Pin1, INPUT);
	uint8_t HAZARD_data = DIO_GetPinVal(DIO_PORTA ,Pin1) ;
	/*Some logic is needed here or in hazard button function to handle rising edge
	 ex:
	 CURRENT_HAZARD_DATA = getpinval();
	 if((previuos == low)&&(current == high)){
	 return pressed ;
	 }else{
	 return unpressed;
	 }

	return HAZARD_data;
}*/
/*uint8_t READ_RIGHT_Button(void){
	DIO_SetPinDir(DIO_PORTA ,Pin2, INPUT);
	uint8_t right_data  = DIO_GetPinVal(DIO_PORTA ,Pin2) ;
	return right_data ;
}*/
/*uint8_t READ_LEFT_Button(void){
	DIO_SetPinDir(DIO_PORTA ,Pin3, INPUT);
	uint8_t right_data  = DIO_GetPinVal(DIO_PORTA ,Pin3) ;
	return right_data;

}*/
