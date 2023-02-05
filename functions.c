void Blink_Right(void);
void Blink_LEFT(void);
char READ_IGNITON(void);
char READ_HAZARD_Button(void);/*instead of void it can take pin number  */
char READ_RIGHT_Button(void);
char READ_LEFT_Button(void);

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