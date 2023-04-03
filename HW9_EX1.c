#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[21] = "HW9_EX1.c           ";
const unsigned char MSG1[21] = "                    ";
unsigned long int TIME = 0;

void interrupt IntServe() {
	if (TMR0IF) {
		TIME = TIME + 0x10000;
		TMR0IF  = 0;
	}
}

void main() {
	unsigned char i;
	unsigned int TStart, TEnd;

	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	LCD_Init();
	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG1[i]);
	Wait_ms(1000);
	LCD_Inst(1);	

  	T0CS = 0;
    T0CON = 0x88;
    TMR0ON = 1;
    TMR0IE = 1;
    TMR0IP = 1;
    PEIE = 1;
	
	GIE = 1;
	
	TStart = TIME + TMR0;
	for(i=0; i<10; i++) {
		while(!RB0);
		while(RB0);
	}
	TEnd = TIME + TMR0;
	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); LCD_Out(TEnd - TStart, 10, 7);
	while(1);
	
}