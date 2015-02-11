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
#include <delays.h>

//Variables
extern unsigned char ones; //7 Seg Digit in one's place
extern unsigned char tens; //7 Seg Digit in ten's place
extern unsigned char sevenSeg[]; //7 Seg lookup (Declare and initialised)
extern char LCD_TEMP;

void Run_Buzzer(unsigned char status) { //Run Buzzer routine
	if(status) { //If status is on
		CCPR2L = 0b01111101; //Set duty cycle = 50%
		CCP2CON = 0b00111111; //Set PWM mode
	}
	else {
		CCP2CON = 0; //Disable PWM if status is off
	}
}

void Run_Lightbulb(unsigned char lightbulbPower) { //lightbulbPower Range: 0 to 250
		CCPR1L = lightbulbPower; // variable duty cycle, 8 bits of 10bit used.
		CCP1CON = 0b00001111; // DC1B1 & DC1B0 = 0(Other 2 bits of duty cycle not used), PWM mode
}

void Light_LED(unsigned char led) { //Light LEDs, unused, just in case
	RED_LED = led & 0x01; //No shift, mask.
	YELLOW_LED = (led >> 1) & 0x01; //Shift once, mask
	GREEN_LED = (led >> 2) & 0x01; //Shift twice, mask
}

void Light_SevenSeg(unsigned char n) { //Light seven segment
	ones = n % 10; //Get digit from one's place
	tens = n / 10; //Get digit from ten's place

	SEVEN_SEG_TWO = SEVEN_SEG_ONE; //Switch values
	SEVEN_SEG_ONE = !SEVEN_SEG_TWO; //Switch values
	if (SEVEN_SEG_ONE){ //If 7 segment 1 is on
		SEVEN_SEG_DATA = ~sevenSeg[ones]; //send value for one's place. (Bitwise NOT because of wrong calculation, lazy change)
	}
	else{
		SEVEN_SEG_DATA = ~sevenSeg[tens]; //Same thing, but opposite
	}
}

void Init_LCD(){				/* LCD display initialization */
// Special Sequence a) to d) required for 4-bit interface 
	Delay1KTCYx(15);			//   a)	15ms LCD power-up delay
	W_ctr_4bit(0x03);			//   b)	Function Set (DB4-DB7: 8-bit interface)
	Delay1KTCYx(5);			//   c)	5ms delay
	W_ctr_4bit(0x02);			//   d) Function Set (DB4-DB7: 4-bit interface)    
	W_ctr_4bit(0b00101000);		// Function Set - 4-bit, 2 lines, 5X7
 	W_ctr_4bit(0b00001100);		// Display on, cursor off
	W_ctr_4bit(0b00000110);		// Entry mode - inc addr, no shift
	W_ctr_4bit(0b00000001);		// Clear display & home position
}
 
void W_ctr_4bit(char x){ 
/* Write control word in term of 4-bit at a time to LCD */
//	LCD_RW	= 0;				// Logic ‘0’
	LCD_RS	= 0;				// Logic ‘0’
	LCD_TEMP 	= x;				// Store control word
	LCD_TEMP	>>= 2;				// send upper nibble of control word
	LCD_TEMP &= 0x3c;
	LCD_E	= 1;				// Logic ‘1’
	LCD_DATA 	= LCD_TEMP;
	Delay1KTCYx(1);				// 1ms delay
	LCD_E	= 0;				// Logic ‘0’
	Delay1KTCYx(1);				// 1ms delay
	LCD_TEMP	= x;				// Store control word
	LCD_TEMP <<= 2;
	LCD_TEMP	&= 0x3c;			// Send lower nibble of control word
	LCD_E	= 1;				// Logic ‘1’
	LCD_DATA 	= LCD_TEMP;
	Delay1KTCYx(1);				// 1ms delay
	LCD_E	= 0;				// Logic 0’
	Delay1KTCYx(1);				// 1ms delay
}

void W_data_4bit(char x){ 
/* Write text data in term of 4-bit at a time to LCD */
//	LCD_RW	 = 0;				// Logic ‘0’
	LCD_RS	 = 1;				// Logic ‘1’
	LCD_TEMP	 = x;				// Store text data
	LCD_TEMP  >>= 2;				// Send upper nibble of text data
	LCD_TEMP &= 0x3c;
	LCD_E	 = 1;				// Logic ‘1’
	LCD_DATA = LCD_TEMP;
	Delay1KTCYx(1);				// 1ms delay
	LCD_E	 = 0;				// Logic ‘0’
	Delay1KTCYx(1);				// 1ms delay
	LCD_TEMP	 = x;				// Store text data
	LCD_TEMP <<= 2;
	LCD_TEMP &= 0x0f;			// Send lower nibble of text data
	LCD_E	 = 1;				// Logic ‘1’
	LCD_DATA = LCD_TEMP;
	Delay1KTCYx(1);				// 1ms delay
	LCD_E	 = 0;				// Logic ‘0’
	Delay1KTCYx(1);				// 1ms delay
}

 
