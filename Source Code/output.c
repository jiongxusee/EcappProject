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
#include <constant.h>

//Prototypes
void Display_Seven_Seg(unsigned int);
void Display_LED(unsigned int);
void Run_Lightbulb(unsigned int);

//Variables
unsigned int lightbulbPower; //Range: 0 to 250

void Run_Lightbulb(lightbulbPower){
	PR2 = PR2_VALUE;
	
	if(power > 0) {
		CCPR1L = power; // 8 bits of 10bit used
		CCP1CON = 0b00001111; // DC1B1 & DC1B0 = 0(Other 2 bits of duty cycle not used), PWM mode
	}
	else {
		CCP1CON = 0; //Disable PWM if power = 0
	}
}