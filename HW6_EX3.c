#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[20] = "Win:            ";
const unsigned char MSG1[20] = "Loose:          ";


void main(void) {
	unsigned int i;
	unsigned int DIE, WIN, LOOSE, BET;
	
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	LCD_Init();
	LOOSE = 0;
	WIN = 0;

	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);
	LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG1[i]);

	while(1) {
		while(!RB0 && !RB1 && !RB2 && !RB3);
		while(RB0 || RB1 || RB2 || RB3) {
			if(RB0) BET = 0;
			if(RB1) BET = 1;
			if(RB2) BET = 2;
			if(RB3) BET = 3;
	
			DIE = (DIE + 1) % 4;
		}

		if(BET == DIE) WIN += 1;
		if(BET != DIE) LOOSE += 1;

		LCD_Move(0,9); LCD_Out(WIN, 3, 0);
		LCD_Move(1,9); LCD_Out(LOOSE, 3, 0);
	}
}