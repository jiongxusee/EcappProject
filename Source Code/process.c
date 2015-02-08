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
extern unsigned int temperature; //Temperature in Celsius

int Increase_Temperature(unsigned int value) { //Increase Temperature routine
	temperature = temperature + value; //Increase temperature
	if(temperature > TEMP_MAX) { //Check for temperature over max
		temperature = TEMP_MAX; //Set temperature to max
	}
	return temperature; //Self explanatory
}
int Decrease_Temperature(unsigned int value) { //Decrease Temperature routine
	temperature = temperature - value; //Decrease temperature
	if(temperature < TEMP_MIN) { //Check for temperature under max
		temperature = TEMP_MIN; //Set temperature to min
	}
	return temperature;//Self explanatory
}

int map(int value, int inMin, int inMax, int outMin, int outMax) { //Remap a value from a range to another range
	return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin; //Self explanatory
}
