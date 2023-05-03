#include <pic18.h>
#include "LCD_PortD.c"

void main(void) {

TRISA = 0;
TRISB = 0xFF;
TRISC = 0;
TRISD = 0;
TRISE = 0;
ADCON1 = 0x0F;

unsigned int DIE, X;

LCD_Init();

	while(1) {
		while(!RB0);
		while(RB0) {
			DIE = (DIE + 1) % 6;
			X = (X + 1) % 101;
		}
		DIE += 1;
		if (X < 15) DIE = 6;
		LCD_Move(1,0); LCD_Out(DIE, 1, 0);	
	}
}