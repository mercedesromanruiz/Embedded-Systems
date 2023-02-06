; --- TEST_1 ---
; This program turns the PIC processor into a random count-down timer

#include <p18f4620.inc>

; --- Variables ---
CNT0 equ 1
CNT1 equ 2
CNT2 equ 3

; --- Program ---
	org 0x800
	call Init

L1:
	btfss PORTB, 0
	goto L1

L2:
	btfss PORTB, 0
	goto L3
	incf PORTC
	movlw 12
	cpfsgt PORTC
	goto L2
	movlw 1
	movwf PORTC
	goto L2

L3:
	call Wait
	decf PORTC
	movlw 0
	cpfseq PORTC
	goto L3
	goto L1

; --- Subprograms ---
Init:	movlw 0xFF
	movwf TRISB
	clrf TRISC
	clrf TRISD
	movlw 0x0F
	movwf ADCON1
	return

Wait:	; 250 ms --> 2,500,000 clocks
	movlw 25
	movwf CNT2
W2:
	movlw 100
	movwf CNT1
W1:
	movlw 100
	movwf CNT0
W0:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz CNT0, F
	goto W0
	decfsz CNT1, F
	goto W1
	decfsz CNT2, F
	goto W2
	
	return

end