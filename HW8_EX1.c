#include <pic18.h>
#include "lcd_portd.c"

const unsigned char MSG0[21] = "HW8_EX1.c         ";
const unsigned char MSG1[21] = "1ms Interrupt     ";

unsigned int TIME;

unsigned int BUTTON;
unsigned int RUN;

void CheckButton() {
	if(RB0) TIME = 5000;
	if(RB1) TIME = 10000;
	if(RB2) TIME = 15000;
	if(RB3) TIME = 20000;
}

void interrupt IntServe(void) {
	if (TMR2IF) {
		RA1 = !RA1;
		if (TIME != 0) TIME = TIME - 1;
		TMR2IF = 0;
	}
}

void main() {
	unsigned char i;
	unsigned int j;
	
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	
	ADCON1 = 0x0F;

	LCD_Init();

	LCD_Move(0,0); for(i = 0; i < 20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); for(i = 0; i < 20; i++) LCD_Write(MSG1[i]);

	Wait_ms(1000);
	LCD_Inst(1);

	T2CON = 0x4D;
	PR2 = 249;
	TMR2ON = 1;
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;

	GIE = 1;
	TIME = 0;

	while(1) {
		CheckButton();
		LCD_Move(0, 0); LCD_Out(TIME, 6, 3);
	}
}