/*
ECE 376 - Homework #4
Exercise 2
*/
#include <pic18.h>

void Wait(unsigned int DATA) {
	unsigned int i, j;
	for (i=0; i<DATA; i++) {
		for (j=0; j<1000; j++);
	}
}

void Beep(unsigned int FREQ){
	unsigned char i;
	i = (i + 1) % FREQ;
	if(i == 0) PORTC += 1;
	}	
}

void main(void) {
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	
}