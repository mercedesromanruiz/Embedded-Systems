/*
ECE 376 - Homework #4
Exercise 2
*/
#include <pic18.h>


void Beep(unsigned int FREQ, unsigned int DUR) {
	unsigned int i, j, k;
	for (i = 0; i < DUR; i++) {
		for (j = 0; j < 1000; j++) {
			i = (i + 1) % 42;
			if (i == 0) PORTC += 1;
		}
	}
}

void main(void) {
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;
	
	Beep(200,100);

}