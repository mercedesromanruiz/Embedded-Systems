#include <pic18.h>
#include "LCD_PortD.c"

unsigned char TABLE[4] = {1, 2, 4, 8};
unsigned int STEP, BEEP, STEPS;

void interrupt IntServe() {
	if(TMR0IF) {
		if(STEPS!=0) STEP = STEP + 1;
	}
	if(TMR1IF) {
		TIME = TIME + 1;
	}
	if(TMR2IF) {
		if(BEEP!=0) BEEP = BEEP - 1;
	}
	if(TMR3IF) {
		if(BEEP) RC0  = !RC0;
	}
}

void main() {

	STEP = 0;
	STEPS = 0;
	BEEP = 0;

	while(1) {
		while(!RB0);
		N = TMR1 % 8;
		STEPS = 600 + 25 * N;
		while(TURN) {
			PORTC = TABLE[STEP%4];
			if(STEPS%25 == 0) BEEP = 100;
			STEPS = STEPS - 1;
			WIN = (STEPS%200) / 8;
			LCD_Move(0,0); LCD_Out(WIN, 2, 0);
			LCD_Move(1,0); LCD_Out(TIME, 10, 7);
		}
	}
}