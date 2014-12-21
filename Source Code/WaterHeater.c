#include <p18f4520.h>
#include <constant.h>
#include <input.c>
#include <process.c>
#include <output.c>



void main() {
	ADCON = 0x0F;
	TRISA = 0xFF;
	TRISB = 0xFF;
	TRISC = 0xFF;
	TRISD = 0xFF;
	TRISE = 0xFF;

}