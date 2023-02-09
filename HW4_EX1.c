/* 
ECE 376 - Homework #4
Exercise 1
*/

#include <pic18.h>
#include <math.h>

void main(void) {
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

/*
// --- PART A ---

	unsigned char i;
	while(1) {
		i = (i + 1) % 8;
		if(i == 0) PORTC += 1;
	}

*/ 
/*
// --- PART B ---

	unsigned char i;
	while(1) {
	i = (i + 1) % 7;
	if(i == 0) PORTC += 1;
	}
*/
	
// --- PART C ---
/*
	unsigned long int A, B, C;
	unsigned char i;
	A = 0x12345678;
	B = 0x1234;
	while(1) {
		i = (i + 1) % 8;
		if(i == 0) PORTC += 1;
		C = A/B;
	}
*/
/*
// --- PART D ---
	float A, B, C;
	A = 3.14159265379;
	while(1) {
		i = (i + 1) % 8;
		if(i == 0) PORTC += 1;
		C = cos(A);
	}
*/ 
}
