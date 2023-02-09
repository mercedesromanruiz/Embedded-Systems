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



void main(void) {
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	int FREQ = 200;
	unsigned int N;	
	N = 10000000 / FREQ;
	
	unsigned char i;
	while(1) {
		i = (i + 1) % N;
		if (i == 0) PORTC += 1;
	}
}