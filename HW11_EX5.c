#include <pic18.h>

unsigned int A2D_Read(unsigned char c) {
	unsigned int result;
	unsigned char i;
	c = c & 0x0F;
	ADCON0 = (c << 2) + 0x01;
	for (i = 0; i < 20; i++);
	GODONE = 1;
	while(GODONE);
	return(ADRES);
}

void D2A(unsigned int X) {
	unsigned char i;
	TRISC0 = 0;
	TRISC3 = 0;
	TRISC5 = 0;

	X = X & 0x0FFF;
	X = X + 0x3000;
	RC0 = 1;
	RC3 = 1;

	RC0 = 0;

	for(i = 0; i < 16; i++) {
		if(X & 0x8000) RC5 = 1; else RC5 = 0;
		RC3 = 0;
		X = X << 1;
		RC3 = 1;
	}
	
	RC0 = 1;
}

void main() {
	int A2D;
	unsigned int i;
	unsigned int x0, x1, x2;
	unsigned int y0, y1, y2;
	
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	TRISA = 0xFF;
	TRISE = 0x0F;
	ADCON2 = 0x85;
	ADCON1 = 0x07;
	ADCON0 = 0x01;
	i = 0;

	while(1) {
		x2 = x1;
		x1 = x0;
		x0 = A2D_Read(0);

		y2 = y1;
		y1 = y0;
		y0 = 1.9384*y1- 0.9608*y2+ 0.293 * (x1 - x2);
		D2A(y0); 

		Wait_ms(10);
	}
}