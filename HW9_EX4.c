#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[21] = "RouletteWheel.c     ";
const unsigned char MSG1[21] = "                    ";

unsigned char TABLE[4] = {1, 2, 4, 8};
unsigned int STEP, BEEP, TOTALSTEPS, TIME;

void interrupt IntServe() {
	if(TMR0IF) {
		TMR0 = -50000 + 50;
		if(TOTALSTEPS != 0) {
			STEP = STEP + 1;
			PORTC = TABLE[STEP % 4];
			if(STEP%25 == 0) BEEP = 100;
			TOTALSTEPS = TOTALSTEPS - 1;
		}
		TMR0IF = 0;
	}
	if(TMR1IF) {
		TMR1 = -1 + 50;
		TIME = TIME + 0x10000;
		TMR1IF = 0;
	}
	if(TMR2IF) {
		if(BEEP!=0) BEEP = BEEP - 1;
		TMR2IF = 0;
	}
	if(TMR3IF) {
		TMR3 = - 28635 + 50;
		if(BEEP!=0) RC4  = !RC4;
		TMR3IF = 0;
	}
}

void main() {

	unsigned int i, WIN, N;

	// Initialize Ports
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	//LCD Display
	LCD_Init();
	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG1[i]);
	
	// TIMER0 10ms
	T0CS = 0;
	T0CON = 0x81;
	TMR0ON = 1;
	TMR0IE = 1;
	TMR0IP = 1;
	PEIE = 1;

	// TIMER1 100ns
	TMR1CS = 0;
	T1CON = 0x88;
	TMR1ON = 1;
	TMR1IE = 1;
	TMR1IP = 1;
	PEIE = 1;

	// TIMER2 1ms
	T2CON = 0x4D;
	PR2 = 249;
	TMR2ON = 1;
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;

	// TIMER3 174.61Hz
	TMR3CS = 0;
	T3CON = 0x81;
	TMR3ON = 1;
	TMR3IE = 1;
	TMR3IP = 1;
	PEIE = 1;

	GIE = 1;
	
	TIME = 0;
	STEP = 0;
	TOTALSTEPS = 0;
	BEEP = 0;

	while(1) {

		if(RB0) {
			LCD_Inst(1);
			N = TMR1 % 8;
			TOTALSTEPS = 600 + 25 * N;
		}		

		LCD_Move(1,0); LCD_Out(TIME, 10, 7);
		WIN = (STEP % 200) % 8;
		LCD_Move(0,0); LCD_Out(WIN, 2, 0);
	}
}