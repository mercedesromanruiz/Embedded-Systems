#include <pic18.h>

void NeoPixel_Display(unsigned char RED, unsigned char GREEN, unsigned char BLUE) {
	PIXEL = GREEN;	asm("  call Pixel_8 ");
   	PIXEL = RED;	asm("  call Pixel_8 ");
   	PIXEL = BLUE;	asm("  call Pixel_8 ");
	
	 asm("    return");

	#asm
	Pixel_8:
   		call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	call	Pixel_1
    	return

	Pixel_1:
		bsf		((c:3971)),0	; PORTD,0
    	nop
		btfss   ((c:0000)),7
		bcf		((c:3971)),0
		rlncf   ((c:0000)),F
   		nop
   		nop
    	bcf		((c:3971)),0
    	return
	#endasm
}

void main(void) {

	unsigned char RED, GREEN, BLUE;

	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	
	TRISA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;

	ADCON1 = 0x0F;
	
	RED = 20;
	GREEN = 0;
	BLUE = 10;

	while(1) {
		TEMP = ReadKey();
		
		if (TEMP < 10) X = (X*10) + TEMP;
		
		if (TEMP == 10) {
			RED = X;
			GREEN = X;
			BLUE = X;
		}
		
		if (TEMP == 11) {
			X = X / 10;
		}

		LCD_Move(1,5); LCD_Out(X, 5, 0);

		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
		NeoPixel_Display(RED, GREEN, BLUE);
	}
}