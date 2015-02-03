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
extern unsigned int power; //Power in percentage

int Increase_Temperature(unsigned int value) {
	temperature = temperature + value;
	if(temperature > TEMP_MAX) {
		temperature = TEMP_MAX;
	}
	return temperature;
}
int Decrease_Temperature(unsigned int value) {
	temperature = temperature - value;
	if(temperature < TEMP_MIN) {
		temperature = TEMP_MIN;
	}
	return temperature;
}

int Convert_Temp_To_Power(unsigned int temp) {
	power = map(temp, TEMP_MIN, TEMP_MAX, POWER_MIN, POWER_MAX);
	return power;
}

int map(int value, int inMin, int inMax, int outMin, int outMax) {
	return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
