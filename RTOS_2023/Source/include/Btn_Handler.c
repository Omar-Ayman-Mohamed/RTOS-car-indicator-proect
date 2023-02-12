/*
 * Btn_Handler.c
 *
 *  Created on: Feb 11, 2023
 *      Author: wario
 */



#include "Btn_Handler.h"
#include "DIO.h"

uint8_t READ_IGNITON(void){

	DIO_SetPinDir(DIO_PORTA ,Pin0, INPUT);
	uint8_t IGNITION_data = DIO_GetPinVal(DIO_PORTA ,Pin0) ;
	return IGNITION_data;
}
uint8_t READ_HAZARD_Button(void){
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
	 */
	return HAZARD_data;
}
uint8_t READ_RIGHT_Button(void){
	DIO_SetPinDir(DIO_PORTA ,Pin2, INPUT);
	uint8_t right_data  = DIO_GetPinVal(DIO_PORTA ,Pin2) ;
	return right_data ;
}
uint8_t READ_LEFT_Button(void){
	DIO_SetPinDir(DIO_PORTA ,Pin3, INPUT);
	uint8_t right_data  = DIO_GetPinVal(DIO_PORTA ,Pin3) ;
	return right_data;

}
