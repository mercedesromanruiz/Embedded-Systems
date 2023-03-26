#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[20] = "HW7_EX1.c        ";

unsigned int A2D_Read(unsigned char c) {
	unsigned int result;
	unsigned char i;
	c = c & 0x0F;
	ADCON0 = (c << 2 ) + 0x01;
	for (i = 0; i < 20; i++);
	GODONE = 1;
	while(GODONE);
	return(ADRES);
}

void main(void) {
	int A2D;
	int VOLT;
	
	unsigned int i, j;
	
	TRISA = 0;
	TRISB = 0x0F;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;
	
	LCD_Init();
	LCD_Move(0,0); for (i = 0; i < 20; i++) LCD_Write(MSG0[i]);

	TRISA = 0xFF;
	TRISE = 0x0F;
	ADCON2 = 0x85;
	ADCON1 = 0x07;
	ADCON0 = 0x01;
	i = 0;

	TRISC = TRISC | 0xC0;
	TXIE = 0;
	RCIE = 0;
	BRGH = 0;
	BRG16 = 1;
	SYNC = 0;
	SPBRG = 255;
	TXSTA = 0x22;
	RCSTA = 0x90;	

	while(1) {
		
		PORTC = 1;

		for (i = 0; i < 40; i++) {
			A2D = A2D_Read(0);
			VOLT = 0.488 * A2D;
			LCD_Move(1,0); LCD_Out(VOLT, 5, 2);
			SCI_Out(VOLT, 5, 2);
			SCI_CRLF();
			Wait_ms(100);
		}

		PORTC = 0;

		for (i = 0; i < 80; i++) {
			A2D = A2D_Read(0);
			VOLT = 0.488 * A2D;
			LCD_Move(1,0); LCD_Out(VOLT, 5, 2);
			SCI_Out(VOLT, 5, 2);
			SCI_CRLF();
			Wait_ms(100);
		}
	}
}