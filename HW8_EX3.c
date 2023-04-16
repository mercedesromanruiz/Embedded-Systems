#include <pic18.h>
#include "lcd_portd.c"

unsigned int TIME;
unsigned int RUN;

void interrupt IntServe(void) {
	if(TMR2IF) {
		if(RUN) TIME = TIME + 1;
		TMR2IF = 0;
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
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;

	GIE = 1;

	TRISC = TRISC | 0xC0;
	TXIE = 0;
	RCIE = 0;
	BRGH = 0;
	BRG16 = 1;
	SYNC = 0;
	SPBRG = 255;
	TXSTA = 0x22;
	RCSTA = 0x90;	

	unsigned int N;
	RUN = 0;

	while(1) {
		if(RB0) {
			TIME = 0;
			N = rand()%5 + 3;
			Wait_ms(N * 1000);
			PORTA = 0xFF;
			RUN = 1;
		}
		while(RUN) {
			LCD_Move(0,0); LCD_Out(TIME, 6, 3);
			if(RB0){
				SCI_Out(TIME, 6, 3);
				SCI_CRLF();
				RUN = 0;
				PORTA = 0;
			}
		}
		
	}
	
}