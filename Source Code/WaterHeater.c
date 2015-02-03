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
unsigned char ones;
unsigned char tens;
unsigned int temperature;
unsigned int power;
unsigned int powerChange = 1;
unsigned int i;
unsigned int waterFlow;
unsigned char an[] = {0x01, 0x05};
unsigned char sevenSeg[];


#pragma code Handler_High = 0x08
void Handler_High() {
	_asm
		goto ISR_High //Go to ISR
	_endasm
}
#pragma code

#pragma interrupt ISR_High
void ISR_High() {
	//Insert High Priority interrupt code
	if(INTCONbits.INT0IF) {
		temperature = Increase_Temperature(TEMP_STEP);
	}
}

#pragma code Handler_Low = 0x18
void Handler_Low() {
	_asm
		goto ISR_Low
	_endasm
}

#pragma interrupt ISR_Low
void ISR_Low() {
	//Insert Low Priority interrupt code
	if(INTCON3bits.INT1IF) {
		temperature = Decrease_Temperature(TEMP_STEP);
	}
}

void main() {
	ADCON0 = an[0];
	ADCON1 = 0x0D; //Use AN0 and AN1 as Analog Input, Internal VREF.
	ADCON2 = 0b00011011; //Left Justified, 6 TAD, Fosc/4
	INTCON = 0b11110000; //Enable all interrupts
	INTCON2 = 0b11110100; //INT0 High Priority
	INTCON3 = 0b00001000; //INT1 Low Priority, INT2 Disabled
	TRISA = 0xFF; //LCD E, LCD RS, Pot
	TRISB = 0xC3; //LCD DATA, PB
	TRISC = 0xC0; //7SEG SL1-SL2, Bulb, LED, S4
	TRISD = 0x00; //7SEG DATA, Buzzer
	TRISE = 0x00; //Not used.
	T2CON = 0b00000101; //Timer 2 On, Postscaler = 1:1, Prescaler = 1:4
	RCONbits.IPEN = 1; //Enable Interrupt Priorities
	PR2 = PR2_VALUE; //PR2 for PWM
	
	while(1) {
		
		waterFlow = Read_Potentiometer(an[0]);
		power = (waterFlow + map(temperature, TEMP_MIN, TEMP_MAX, 0, 256))/2;
		
		Light_SevenSeg(temperature);

//		if(powerChange) {
			Run_Lightbulb(power);
			powerChange = 0;
//		}
		Light_LED(power);
	
	}
}