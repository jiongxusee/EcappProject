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

//Variables
extern unsigned char ones;
extern unsigned char tens;
extern unsigned char sevenSeg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F3, 0x6F};

void Run_Lightbulb(unsigned char lightbulbPower) { //lightbulbPower Range: 0 to 250
	
	if(lightbulbPower > 0) { 		
		CCPR1L = lightbulbPower; // 8 bits of 10bit used
		CCP1CON = 0b00001111; // DC1B1 & DC1B0 = 0(Other 2 bits of duty cycle not used), PWM mode
	}
	else {
		CCP1CON = 0; //Disable PWM if power = 0
	}
}

void Light_LED(unsigned char led) {
	RED_LED = led & 0x01;
	YELLOW_LED = (led >> 1) & 0x01;
	GREEN_LED = (led >> 2) & 0x01;
}

void Light_SevenSeg(unsigned char n) {
	ones = n % 10;
	tens = n / 10;

	SEVEN_SEG_TWO = 0;
	SEVEN_SEG_ONE = 1;
	SEVEN_SEG_DATA = sevenSeg[ones];
	SEVEN_SEG_ONE = 0;
	SEVEN_SEG_DATA = 0;
	SEVEN_SEG_TWO = 1;
	SEVEN_SEG_DATA = sevenSeg[tens];
}
