const unsigned char MSG0[20] = "RGB Color:      ";
unsigned char PIXEL @ 0x000;

#include <pic18.h>
#include "LCD_PortD.c"

void NeoPixel_Display(unsigned char RED, 
		unsigned char GREEN, unsigned char BLUE)
{
   PIXEL = GREEN;	asm("  call Pixel_8 ");
   PIXEL = RED;		asm("  call Pixel_8 ");
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

char GetKey(void) {
   int i;
   unsigned char RESULT;
   TRISC = 0xF8;
   RESULT = 0xFF;
   PORTC = 4;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 1;
   if (RC5) RESULT = 4;
   if (RC4) RESULT = 7;
   if (RC3) RESULT = 10;
   PORTC = 2;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 2;
   if (RC5) RESULT = 5;
   if (RC4) RESULT = 8;
   if (RC3) RESULT = 0;
   PORTC = 1;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 3;
   if (RC5) RESULT = 6;
   if (RC4) RESULT = 9;
   if (RC3) RESULT = 11;
   PORTC = 0;
   return(RESULT);
}
      
char ReadKey(void) {
   char X, Y;
   do {
      X = GetKey();
      }   while(X > 20);
   do {
      Y= GetKey();
      }   while(Y < 20);
   Wait_ms(100);  // debounce
   return(X);
}

void main(void) {
	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0xFF;
	TRISD = 0;
	TRISE = 0;
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	ADCON1 = 0x0F;	
	
	unsigned int i;
	LCD_Init();
	TRISD = 0;
	LCD_Move(0,0); for(i=0; i<20; i++) LCD_Write(MSG0[i]);


	unsigned int TEMP, X;
	unsigned char RED, GREEN, BLUE, COLOR;
	unsigned int DONE;

	X = 0;
	RED = 0;
	GREEN = 0;
	BLUE = 0;
	DONE = 0;

	while(1) {
		TEMP = ReadKey();
		if(TEMP < 10) X = (X*10) + TEMP;
		if(X > 255) X = 0;
		if(TEMP == 10) {
			COLOR = X;
			X = 0;
			DONE = 1;
		}
		if (TEMP == 11) X = X/10;
	
		while(DONE) {
			if(RB0) {RED = COLOR, DONE = 0;}
			if(RB1) {GREEN = COLOR, DONE = 0;}
			if(RB2) {BLUE = COLOR, DONE = 0;}
		}
	
		LCD_Move(0,11); LCD_Out(X, 3, 0);
		LCD_Move(1,1); LCD_Out(RED, 3, 0);
		LCD_Move(1,5); LCD_Out(GREEN, 3, 0);
		LCD_Move(1,9); LCD_Out(BLUE, 3, 0);

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


