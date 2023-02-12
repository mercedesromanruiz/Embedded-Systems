/*
ECE 376 - Homework #4
Exercise 2
*/
#include <pic18.h>


void main(void) {
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	unsigned int i;
	unsigned int j;
	j = 100;
	while(j > 0) {
		RC0 = !RC0;
		for (i=0; i<1561; i++);
		j--;
	}
	

}