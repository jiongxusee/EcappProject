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

//Prototypes
void Handler_High(void);
void ISR_High(void);
void Handler_Low(void);
void ISR_Low(void);

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
}

void main() {
	ADCON0 = POTENTIOMETER_SELECT;
	ADCON1 = 0x0B; //Use AN0 to AN3 as Analog Input, Internal VREF.
	TRISA = 0xFF; //LCD E, LCD RS, Pot
	TRISB = 0xC3; //LCD DATA, PB
	TRISC = 0xC0; //7SEG SL1-SL2, Bulb, LED, S4
	TRISD = 0x00; //7SEG DATA, Buzzer
	TRISE = 0x00; //Not used.
	T2CON = 0b00000101; //Timer 2 On, Postscaler = 1:1, Prescaler = 1:4
	RCONbits.IPEN = 1; //Enable Interrupt Priorities

}