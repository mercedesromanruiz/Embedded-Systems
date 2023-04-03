#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[21] = "HW3_EX2.c       ";
const unsigned char MSG1[21] = "                ";

void interrupt IntServe() {
	if(TMR0IF) {
		TMR0 = -38223 + 50;
		RC0 = !RC0;
		TMR0IF = 0;
	}
	if(TMR1IF) {
		TMR1 = -34053 + 50;
		RC1 = !RC1;
		TMR1IF = 0;
	}
	if(TMR2IF) {
		RC2 = !RC2;
		TMR2IF = 0;
	}
	if(TMR3IF) {
		TMR3 = -28635 + 50;
		RC3 = !RC3;
		TMR3IF = 0;
	}
}

void main() {

	unsigned char i;
	
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	LCD_Init();
	
	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG1[i]);

	Wait_ms(100);

	T0CS = 0;
	T0CON = 0x88;
	TMR0ON = 1;
	TMR0IE = 1;
	TMR0IP = 1;
	PEIE = 1;

	TMR1CS = 0;
	T1CON = 0x81;
	TMR1ON = 1;
	TMR1IE = 1;
	TMR1IP = 1;
	PEIE = 1;
	
	T2CON = 0x5F;
	PR2 = 158;
	TMR2ON = 1;
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;
	
	TMR3CS = 0;
	T3CON = 0x81;
	TMR3ON = 1;
	TMR3IE = 1;
	TMR3IP = 1;
	PEIE = 1;

	GIE = 1;

	while(1);
	
}