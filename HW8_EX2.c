#include <pic18.h>
#include "lcd_portd.c"

const unsigned char MSG0[20] = "HW8_EX2.c     ";
const unsigned char MSG1[20] = "Note D2 (73.42 Hz)";

unsigned int N;

void interrupt IntServe() {
	if (TMR2IF) {
		if(RB0) N = (N + 1)%12;
		if (N == 0) RC0 = !RC0;
		else RC0 = 0;
		TMR2IF = 0;
	}
}

void main() {
	unsigned char i;
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 15;

	T2CON = 0x5D;
	PR2 = 236;
	TMR2ON = 1;
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;
	
	GIE = 1;	

	while(1);
}