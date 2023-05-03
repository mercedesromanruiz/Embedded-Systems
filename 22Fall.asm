#include <p18f4620.inc>

CNT0 equ 0
CNT1 equ 1
CNT2 equ 2

	org 0x800
	call Init
L1:
	clrf PORTC
	clrf PORTD
L2:
	movlw 0
	cpfsgt PORTB
	goto L3
	goto L2
L3:
	movlw 0
	cpfseq PORTB
	goto L4
	goto L3
L4: 
	btfsc PORTB, 0
L5:
	incf PORTC, F
L6:
	btfss PORTB, 1
	goto L2
L7:
	movlw 5
	cpfseq PORTC
	goto L1
L8:
	movlw 255
	movwf PORTD
	
	call Wait
	
	goto L1

Init:
	movlw 0xFF
	movwf TRISB
	clrf TRISC
	clrf TRISD
	return

Wait:
	movlw 250
	movwf CNT2
	nop
	nop
W2:
	movlw 110
	movwf CNT1
	nop
	nop
	nop
W1:
	movlw 100
	movwf CNT0
	nop
	nop
	nop
	nop
W0:
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