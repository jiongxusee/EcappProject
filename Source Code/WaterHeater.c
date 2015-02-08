/* Lecturer: Mr Lew Tong Yong
** Class: PE01
** Group Members: Gaurav C, Joseph Ang, Ashton Goh, Tay Wen Jie, See Jiongxu
**
** Please follow the conventions if you are coding..
** Structure: Open braces ({) on the same line. Close braces (}) on the next line.
** Structure: Proper indentations. (VERY IMPORTANT!)
** Structure: Empty line after every segment.
** Structure: Space after every comma and colon.
** Subroutines: Under_Score_Between_Every_Word(), each word start with caps.
** Subroutines: Action_Words_In_Front, like Start_ISR(), Stop_ISR().
** Variables: firstLetterOfSecondWordOnwardsCaps.
** Definitions: ALL CAPS.
** Comments: //Space before slashes
**
** Untidy codes will be rolled back. You have been warned.
*/

#include <p18f4520.h>
#include "constants.h"
#include "input.c"
#include "process.c"
#include "output.c"

//Variables
unsigned int upSwitchTime; //Time for switch debounce
unsigned int upSwitchFlag; //Flag for switch debounce
unsigned int downSwitchTime; //Time for switch debounce
unsigned int downSwitchFlag; //Flag for switch debouce
unsigned int buzzerOffTime; //Time to turn off buzzer
unsigned int buzzerFlag; //Flag to turn off buzzer
unsigned int subcount = 0; //Self explanatory
unsigned int temperature = TEMP_INIT; //Set initial temperature
unsigned int power; //Power for PWM of heating element
unsigned int i; //Integer useful for loops
unsigned int waterFlow; //waterFlow, ie. pot value
unsigned char ones; //seven segment 2 lookup
unsigned char tens; //seven segment 1 lookup
unsigned char an[] = {0x01, 0x05}; //ADC channel lookup
unsigned char MESS[] = "Good Day"; //LCD message
unsigned char sevenSeg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //7 Segment lookup
char lcdTemp; //To store upper nibble of lcd text

#pragma code Handler_High = 0x08 //Memory address for High priority ISR
void Handler_High() {
	_asm
		goto ISR_High //Go to ISR
	_endasm
}
#pragma code

#pragma interrupt ISR_High
void ISR_High() {
	//Insert High Priority interrupt code
	if(INTCONbits.INT0IF) { //Check S3 Flag
		while(INTCONbits.INT0IF){ //Keep in loop while Pressed
			INTCONbits.INT0IF = 0; //Reset Flag
		}
		upSwitchTime = subcount + (DEBOUNCE_TIME_MS * 10); //Schedule task timing
		upSwitchFlag = 1; //Set task undone
		buzzerOffTime = subcount + (BUZZER_RING_TIME_MS * 10); //Schedule task timing
		Run_Buzzer(1); //Run task
		buzzerFlag = 1; //Set task undone
		INTCONbits.INT0IF = 0; //Clear interrupt flag
	}
}

#pragma code Handler_Low = 0x18 //Memory address for Low priority ISR
void Handler_Low() {
	_asm
		goto ISR_Low
	_endasm
}

#pragma interrupt ISR_Low //Low priority interrupt
void ISR_Low() {
	//Insert Low Priority interrupt code
	if(INTCON3bits.INT1IF) { //Check S2 Flag
		while(INTCON3bits.INT1IF){ //Keep in loop while Pressed
			INTCON3bits.INT1IF = 0; //Reset Flag
		}
		downSwitchTime = subcount + (DEBOUNCE_TIME_MS * 10); //Schedule task timing
		downSwitchFlag = 1; //Set task undone
		buzzerOffTime = subcount + (BUZZER_RING_TIME_MS * 10); //Schedule task timing
		Run_Buzzer(1); //Run task
		buzzerFlag = 1; //Set task undone
		INTCON3bits.INT1IF = 0; //Clear interrupt flag
	}
	if(INTCONbits.TMR0IF) { //Timer Interrupt every 0.1ms
		TMR0L = TMR0_RESET; //Refill timer 0
		PORTEbits.RE0 = ~PORTEbits.RE0; //RE0 for measuring frequency.
		subcount++; //subcount every 0.1ms
		
		/* Implementation of a task-scheduling method.
		** 
		** Each unit of time is determined by a loop count(In this case "subcount").
		** When the task is scheduled, two things are set.
		** 1. Task timing
		** Task is scheduled by adding a predetermined value to the current time.
		** 2. Task Flag
		** Task flag is set by setting a FLAG variable to High.
		**
		** An IF statement will check if the task is to be done during that loop.
		** After the task is done, the FLAG variable is set back to low.
		** 
		** This allows a "Delay" without actually using a delay, thus allowing other tasks
		** to be done, saving instruction cycles 
		*/
				


		if ((subcount % 10) == 0) { //Repeat every 1ms
			waterFlow = Read_Potentiometer(an[0]); //Read ADC
			power = (waterFlow + map(temperature, TEMP_MAX, TEMP_MIN, 0, 256))/2; //remap range of values and average
			if(waterFlow > 0xF0 || temperature < ROOM_TEMP) { //If no waterflow or water below room temperature
				power = 0; //Turn off heating element
				YELLOW_LED = 0; //Turn off waterflow indicator
			}
			else {
				YELLOW_LED = 1; //Leave waterflow indicator on
			}
			Light_SevenSeg(temperature); //Light 7 segment with temperature
			if(power > POWER_MAX){ //If power greater than max
				power = POWER_MAX; //Set power = max
			}
			Run_Lightbulb(power); //Run PWM
		}
		if (subcount == upSwitchTime && upSwitchFlag) { //Check task undone
			temperature = Increase_Temperature(TEMP_STEP); //Do task
			upSwitchFlag = 0; //Set task done
		}
		if (subcount == downSwitchTime && downSwitchFlag) { //Check task undone
			temperature = Decrease_Temperature(TEMP_STEP); //Do task
			downSwitchFlag = 0; //Set task done
		}
		if (subcount == buzzerOffTime && buzzerFlag) { //Check task undone
			Run_Buzzer(0); //Do task
			buzzerFlag = 0; //Set task done
		}
		
		INTCONbits.TMR0IF = 0; //Clear interrupt flag
		PORTEbits.RE0 = ~PORTEbits.RE0; //RE0 for measuring frequency.
	}
	
}

void main() {
	
	TRISA = 0xFF; //LCD E, LCD RS, Pot
	TRISB = 0xC3; //LCD DATA, PB
	TRISC = 0xC0; //7SEG SL1-SL2, Bulb, LED, S4
	TRISD = 0x00; //7SEG DATA, Buzzer
	TRISE = 0x00; //Not used.
	
	ADCON0 = an[0]; //Select ADC Channel
	ADCON1 = 0x0D; //Use AN0 and AN1 as Analog Input, Internal VREF.
	ADCON2 = 0b00011011; //Left Justified, 6 TAD, Fosc/4
	RCONbits.IPEN = 1; //Enable Interrupt Priorities
	INTCON = 0b00110000; //Enable interrupts, temporary disable interrupts
	INTCON2 = 0b11110000; //INT0 High Priority, TMR0 Low Priority
	INTCON3 = 0b00001000; //INT1 Low Priority, INT2 Disabled
	IPR1 = 0b00000000; //TMR2 Low Priority, TMR1 Low Priority
	PIE1 = 0b00000000; //TMR2 Interrupt Disable, TMR1 Interrupt Disable
	T0CON = 0b11001000; //TMR0 8 bits, no prescaler
	T2CON = 0b00000101; //Timer 2 On, Postscaler = 1:1, Prescaler = 1:4
	PR2 = PR2_VALUE; //PR2 for PWM
	TMR0L = TMR0_RESET; //Fill timer0
	
	INTCONbits.GIEH = 1; //Enable interrupts
	INTCONbits.GIEL = 1; //Enable interrupts
	while(1) {
		GREEN_LED = 1; //Turn on green LED

//		for(i = 0; i < MESS[i]; i++){
//			LCD_Data_4bit(MESS[i]);
//		}
	}
}