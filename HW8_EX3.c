#include <pic18.h>
#include "lcd_portd.c"

unsigned int TIME;
unsigned int RUN;

void interrupt IntServe() {
	if(TMR2IF) {
		if(RUN) TIME += 1;
		TMR2IP = 0;
	}
}

void main() {
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	LCD_Init();
	LCD_Inst(1);

	T2CON = 0x4D;
	PR2 = 249;
	TMR2ON = 1;
	TMR2IP = 1;
	TMR2IP = 1;
	PEIE = 1;

	GIE = 1;

	unsigned int N;
	RUN = 0;

	while(1) {
		if(RB0) {
			N = rand() % 5 + 3;
			Wait_ms(N*1000);
			PORTA = 0xFF;
			TIME = 0;
			RUN = 1;
			while(RUN) {
				LCD_Move(0,0); LCD_Out(TIME, 6, 3);
			}
		}
	}
	
}