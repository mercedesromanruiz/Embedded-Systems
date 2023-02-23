#include <pic18.h>
#include "LCD_PortD.c"

const unsigned char MSG0[20] = "Combination Lock";
const unsigned char MSG1[20] = "      Wrong!    ";
const unsigned char MSG2[20] = "     Correct!   ";
const unsigned char MSG3[20] = "                ";
unsigned char TABLE[4] = {1, 2, 4, 8};

unsigned int A2D_Read(unsigned char c) {
	unsigned int result;
	unsigned char i;
	c = c & 0x0F;
	ADCON0 = (c << 2) + 0x01; // set Channel Select
	for (i=0; i<10; i++); // wait 2.4us (approx)
	GODONE = 1; // start the A/D conversion
	while(GODONE); // wait until complete (approx 8us)
	return(ADRES);
}  

void main(void) {
	unsigned int i;
	unsigned int X, A2D, N;
	unsigned int A, B, C, D;
	unsigned int a = 1, b = 2, c = 3, d = 4; // combination lock code
	unsigned int REF, STEP;

	TRISA = 0;
	TRISB = 0xFF;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;
	ADCON1 = 0x0F;

	TRISA = 0xFF;
	TRISE = 0x0F;
	ADCON2 = 0x95;
	ADCON1 = 0x07;
	ADCON0 = 0x01;

	LCD_Init();
	TRISD = 0;

	LCD_Move(0,0); for (i=0; i<20; i++) LCD_Write(MSG0[i]);

	A = 0;
	B = 0;
	C = 0;
	D = 0;
	N = 0;

	STEP = 0;
	REF = 0;
	

	LCD_Move(1,1); LCD_Out(A, 2, 0);
	LCD_Move(1,4); LCD_Out(B, 2, 0);
	LCD_Move(1,7); LCD_Out(C, 2, 0);
	LCD_Move(1,10); LCD_Out(D, 2, 0);

	while(1) {
		A2D = A2D_Read(0);
		X = A2D/50; // Numbers between 0 and 20
		if(RB1) {N = (N+1)%4; Wait_ms(100); }

		if(N == 0) A = X;
		if(N == 1) B = X;
		if(N == 2) C = X;
		if(N == 3) D = X;

		LCD_Move(1,1); LCD_Out(A, 2, 0);
		LCD_Move(1,4); LCD_Out(B, 2, 0);
		LCD_Move(1,7); LCD_Out(C, 2, 0);
		LCD_Move(1,10); LCD_Out(D, 2, 0);

		if(RB0) {
			if(A == a && B == b && C == c && D == d) {
				LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG2[i]);
				REF = 100;
				while(STEP < REF) {
					STEP = STEP + 1;
					PORTC = TABLE[STEP%4];
					Wait_ms(100);
				}

				Wait_ms(1000);

				REF = 0;
				while(STEP > REF) {
					STEP = STEP - 1;
					PORTC = TABLE[STEP%4];
					Wait_ms(100);
				}

				A = 0;
				B = 0;
				C = 0;
				D = 0;
				N = 0;
				
				LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG2[i]);
				
			}
			else {
				A = 0;
				B = 0;
				C = 0;
				D = 0;
				N = 0;
				LCD_Move(1,0); for(i=0; i<20;i++) LCD_Write(MSG1[i]);
				Wait_ms(2000);
				LCD_Move(1,0); for(i=0; i<20; i++) LCD_Write(MSG3[i]);
			}
		}

	}
}