const unsigned char MSG0[10] = "Balance: $" ;
const unsigned char MSG1[4] = "Bet:";
const unsigned char MSG2[6] = "Wheel:";
unsigned int BET, COUNT, PRESS;

#include <pic18.h>
#include "LCD_PortD.c"

void Beep() {
	unsigned int i, j;
	j = 100;
	while (j>0) {
		RC0 = !RC0;
		for (i=0; i<1561; i++);
		j--;
	}
}

void CheckButton() {
	if(RB0) {BET = 0; PRESS = 1;}
	if(RB1) {BET = 1; PRESS = 1;}
	if(RB2) {BET = 2; PRESS = 1;}
	if(RB3) {BET = 3; PRESS = 1;}
	if(RB4) {BET = 4; PRESS = 1;}
	if(RB5) {BET = 5; PRESS = 1;}
	if(RB6) {BET = 6; PRESS = 1;}
	if(RB7) {BET = 7; PRESS = 1;}
}

void Count_Mod8(unsigned int N) {
	unsigned int i;
	for(i = 0; i < 40 + N; i++) {
		COUNT = (COUNT + 1) % 8;
		LCD_Move(1,14); LCD_Out(COUNT, 1, 0);
		Beep();
		Wait_ms(100);
	}
}

void main(void) {
	unsigned int i,j;

	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;	

	LCD_Init();
	unsigned int BANK;
	BANK = 10;

	LCD_Move(0,0);  for (i=0; i<10; i++) LCD_Write(MSG0[i]); 
	LCD_Move(0,10); LCD_Out(BANK, 5, 0);

	unsigned int N;
	LCD_Move(1,0); for (i=0; i < 4; i++) LCD_Write(MSG1[i]);
	LCD_Move(1,8); for (i=0; i < 6; i++) LCD_Write(MSG2[i]);
	
	while(1) {
		CheckButton();
		if(PRESS == 1) {
			N = rand() % 8;
			LCD_Move(1,4); LCD_Out(BET, 1, 0);
			Count_Mod8(N);
			if(BET == COUNT) BANK = BANK + 8;
			if(BET != COUNT) BANK = BANK - 1;
			LCD_Move(0,10); LCD_Out(BANK, 5, 0);
			PRESS = 0;
		}
	}
}