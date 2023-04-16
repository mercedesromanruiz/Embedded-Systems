#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[20] = "FinalProject.c      ";

void interrupt IntServe() {
	if(TMR2IF) {
		if(RB0) RC0 = !RC0;
		else RC0 = 0;
		TMR2IP = 0;
	}
}

// Read Analog Signal --> 0 ... 1023
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

void main() {
	int A2D;
	unsigned int i;	
	unsigned int N, FREQ;

	// Initialize Ports
	TRISA = 0xFF;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	// Initialize Analog Input
	TRISA = 0xFF;
	TRISE = 0x0F;
	ADCON2 = 0x85;
	ADCON1 = 0x07;
	ADCON0 = 0x01;
	i = 0;

	// Initialize Serial Output
	TRISC = TRISC | 0xC0;
	TXIE = 0;
	RCIE = 0;
	BRGH = 0;
	BRG16 = 1;
	SYNC = 0;
	SPBRG = 255;
	TXSTA = 0x22;
	RCSTA = 0x90;

	
	// Initialize Timer2 --> A = 16, C = 16,
	T2CON = 0xFF;
	PR2 = 236;
	TMR2ON = 1;
	TMR2IE = 1;
	TMR2IP = 1;
	PEIE = 1;
	
	GIE = 1;

	LCD_Init();
	LCD_Move(0,0); for(i = 0; i < 20; i++) LCD_Write(MSG0[i]);

	while(1) {
		A2D = A2D_Read(0);
		PR2 = 0.25 * A2D; // PR2 --> 0...256
		N = 16 * 16 * PR2;
		FREQ = 10000000 / (2 * N);
		SCI_Out(PR2, 5, 2);
		SCI_CRLF();
		LCD_Move(1,0); LCD_Out(FREQ, 5, 2);
	}
}